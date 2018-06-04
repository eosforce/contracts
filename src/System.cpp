#include "System.hpp"

namespace eosiosystem {

void system_contract::update_elected_bps() {
  bps_table bps_tbl(_self, _self);

  std::vector<eosio::producer_key> vote_schedule;
  std::vector<int64_t> sorts(num_of_top_bps,0);

  for (auto it = bps_tbl.cbegin(); it != bps_tbl.cend(); ++it) {
    for (int i = 0; i < num_of_top_bps ; ++i) {
      if (sorts[size_t(i)] <= it->total_staked.amount) {
        eosio::producer_key key;
        key.producer_name = it->name;
        key.block_signing_key = it->block_signing_key;
        vote_schedule.insert(vote_schedule.begin() + i, key);
        sorts.insert(sorts.begin() + i, it->total_staked.amount);
        break;
      }
    }
  }

  if (vote_schedule.size() > num_of_top_bps) {
    vote_schedule.resize(num_of_top_bps);
  }

  bytes packed_schedule = pack(vote_schedule);
  set_proposed_producers(packed_schedule.data(), packed_schedule.size());
}

void system_contract::transfer(const account_name from, const account_name to, const asset quantity, const string /*memo*/) {
  //check emergency
  eosio_assert(check_emergency() == false,"chain is in emergency now !");

  //assert from
  require_auth(from);
  accounts_table acnts_tbl(_self, _self);
  const auto &from_act = acnts_tbl.get(from, "from account is not found in accounts table");

  //assert to
  const auto &to_act = acnts_tbl.get(to, "to account is not found in accounts table");

  //assert quantity
  eosio_assert(quantity.symbol == SYMBOL, "only support EOS");
  //from_act.available is already handling fee
  eosio_assert(0 <= quantity.amount && quantity.amount <= from_act.available.amount, "0 < need < available balance");

  acnts_tbl.modify(from_act, 0, [&](account_info & a) {
    a.available -= quantity;
  });

  acnts_tbl.modify(to_act, 0, [&](account_info & a){
    a.available += quantity;
  });
}

void system_contract::updatebp(const account_name bpname, const public_key block_signing_key, const uint32_t commission_rate) {
  //check emergency
  eosio_assert(check_emergency() == false,"chain is in emergency now !");

  //assert bpname
  require_auth(bpname);

  //assert commission_rate
  eosio_assert(commission_rate >= 1 && commission_rate <= 10000, "need 1 <= commission_rate <= 10000");

  bps_table bps_tbl(_self, _self);
  auto bp = bps_tbl.find(bpname);
  if (bp == bps_tbl.end()) {
    bps_tbl.emplace(bpname, [&](bp_info & b) {
      b.name = bpname;
      b.update(block_signing_key,commission_rate);
    });
  } else {
    bps_tbl.modify(bp, 0, [&](bp_info & b) {
      b.update(block_signing_key,commission_rate);
    });
  }
}

void system_contract::vote(const account_name voter, const account_name bpname, const asset change) {
  //check emergency
  eosio_assert(check_emergency() == false,"chain is in emergency now !");

  //assert voter
  require_auth(voter);
  accounts_table acnts_tbl(_self, _self);
  const auto & act = acnts_tbl.get(voter, "voter is not found in accounts table");

  //assert bpname
  bps_table bps_tbl(_self, _self);
  const auto & bp  = bps_tbl.get(bpname, "bpname is not registered");

  //assert change
  eosio_assert(change.symbol == SYMBOL, "only support EOS");
  eosio_assert(change.amount != 0, "need change != 0");
  //act.available is already handling fee
  eosio_assert(change.amount <= act.available.amount,"need < your available balance");

  asset reward = asset(0,SYMBOL);
  votes_table votes_tbl(_self, voter);
  auto vts = votes_tbl.find(bpname);
  if((vts == votes_tbl.end())){
    eosio_assert(change.amount > 0,"need change > 0");

    bps_tbl.modify(bp, 0, [&](bp_info &b) {
      b.total_voteage += b.total_staked.amount * (now() - b.voteage_update_time);
      b.voteage_update_time = now();
      b.total_staked += change;
    });

    votes_tbl.emplace(voter,[&](vote_info & v) {
      v.bpname = bpname;
      v.staked.set_amount(change.amount);
    });
  } else {
    eosio_assert(change.amount >= -vts->staked.amount,"need >= -(your staked balance)");

    //calculate reward
    int64_t vote_age = vts->staked.amount * (now() - vts->stake_time);
    int64_t delta_age = bp.total_staked.amount * (now() - bp.voteage_update_time);
    if(bp.total_voteage + delta_age > 0){
      reward.set_amount(bp.rewards_pool.amount * vote_age / (bp.total_voteage + delta_age));
    }

    //update bps_tbl
    bps_tbl.modify(bp, 0, [&](bp_info & b) {
      b.rewards_pool -= reward;
      b.total_voteage += delta_age - vote_age;
      b.voteage_update_time = now();
      b.total_staked += change;
    });

    votes_tbl.modify(vts, 0, [&](vote_info & v) {
      v.staked += change;
      v.stake_time = now();
      //unstake
      if(change.amount < 0){
        v.unstaking -= change;
        v.unstake_time = now();
      }
    });
  }

  if(change.amount > 0){
    acnts_tbl.modify(act, 0, [&](account_info & a) {
      a.available += reward - change;
    });
  } else {
    acnts_tbl.modify(act, 0, [&](account_info & a) {
      a.available += reward;
    });
  }
}

void system_contract::unfreeze(const account_name voter, const account_name bpname){
  //check emergency
  eosio_assert(check_emergency() == false,"chain is in emergency now !");

  //assert voter
  require_auth(voter);
  accounts_table acnts_tbl(_self, _self);
  const auto & act = acnts_tbl.get(voter, "voter is not found in accounts table");

  //assert vote
  votes_table votes_tbl(_self, voter);
  const auto & vts = votes_tbl.get(bpname,"voter have not add votes to the the producer yet ");

  eosio_assert(vts.unstake_time  + freezen_delay <= now(), "unfreeze is not available yet");
  eosio_assert(0 < vts.unstaking.amount , "need unstaking.amount > 0");

  acnts_tbl.modify(act, 0, [&](account_info & a) {
    a.available += vts.unstaking;
  });

  //update voters_tbl
  votes_tbl.modify(vts, 0, [&](vote_info & v) {
    v.unstaking.set_amount(0);
  });
}

void system_contract::claim(const account_name voter, const account_name bpname){
  //check emergency
  eosio_assert(check_emergency() == false,"chain is in emergency now !");

  //assert voter
  require_auth(voter);
  accounts_table acnts_tbl(_self, _self);
  const auto & act = acnts_tbl.get(voter, "voter is not found in accounts table");

  //assert bpname
  bps_table bps_tbl(_self, _self);
  const auto & bp = bps_tbl.get(bpname, "bpname is not registered");

  //assert vote
  votes_table votes_tbl(_self, voter);
  const auto & vts = votes_tbl.get(bpname, "voter have not add votes to the the producer yet");

  //calculate reward
  int64_t vote_age = vts.staked.amount * (now() - vts.stake_time);
  int64_t delta_age = bp.total_staked.amount * (now() - bp.voteage_update_time);
  eosio_assert(bp.total_voteage + delta_age > 0, "claim is not available yet");
  asset reward = asset(static_cast<int64_t>(bp.rewards_pool.amount * vote_age / (bp.total_voteage + delta_age)),SYMBOL);

  //add reward to balance
  acnts_tbl.modify(act, 0, [&](account_info & a) {
    print("--claim--reward----",reward,"\n");
    a.available += reward;
  });

  //update votes_tbl
  votes_tbl.modify(vts, 0, [&](vote_info & v) {
    v.stake_time = now();
  });

  //update bps_tbl
  bps_tbl.modify(bp, 0, [&](bp_info & b) {
    b.rewards_pool -= reward;
    b.total_voteage += delta_age - vote_age;
    b.voteage_update_time = now();
  });

}

void system_contract::onblock(const block_timestamp, const account_name bpname, const uint16_t, const block_id_type previous) {
  //calculate current block number
  uint32_t _hash0 ;
  memcpy(&_hash0,&previous,8);
  uint32_t blocknum = endian_reverse_u32(_hash0)+1;

  //assert bpname
  bps_table bps_tbl(_self, _self);
  accounts_table acnts_tbl(_self, _self);
  const auto & bp = bps_tbl.get(bpname,"bpname is not registered");
  const auto & act = acnts_tbl.get(bpname, "bpname is not found in accounts table");

  //calculate reward
  auto reward = asset(block_rewards,SYMBOL);
  asset commission = asset(static_cast<int64_t >(reward.amount * bp.commission_rate / 10000),SYMBOL);

  //update bps_tbl
  bps_tbl.modify(bp, 0, [&](bp_info & b) {
    b.rewards_pool += reward - commission;
  });

  //update acnts_tbl
  acnts_tbl.modify(act, 0, [&](account_info & a) {
    a.available += commission ;
  });

  //update active block producer
  if(blocknum % top_bps_update_cycle == 0){
    update_elected_bps();
  }
}

void system_contract::onfee(const account_name actor, const asset fee, const account_name bpname) {
  print("-----onfee-----",eosio::name{.value=actor},"-----",fee,"\n");

  //assert actor
  accounts_table acnts_tbl(_self, _self);
  const auto & act = acnts_tbl.get(actor, "account is not found in accounts table");
  eosio_assert(fee.amount <= act.available.amount,"overdrawn available balance");

  //assert bpname
  bps_table bps_tbl(_self, _self);
  const auto & bp = bps_tbl.get(bpname,"bpname is not registered");

  //update acnts_tbl
  acnts_tbl.modify(act, 0, [&](account_info & a) {
    a.available -= fee ;
  });

  //update bps_tbl
  bps_tbl.modify(bp, 0, [&](bp_info & b) {
    b.rewards_pool += fee;
  });
}

void system_contract::setemergency(const account_name bpname, const bool emergency){
  //assert bpname
  require_auth(bpname);
  bps_table bps_tbl(_self, _self);
  const auto & bp = bps_tbl.get(bpname,"bpname is not registered");

  //assert chainstatus
  cstatus_table cstatus_tbl(_self, _self);
  const auto & cstatus = cstatus_tbl.get(N(chainstatus),"get chainstatus fatal");

  //update bps_tbl
  bps_tbl.modify(bp, 0, [&](bp_info & b) {
    b.emergency = emergency;
  });

  //get active bps
  account_name block_producers[num_of_top_bps] = {};
  get_active_producers(block_producers, sizeof(account_name) * num_of_top_bps);

  //get proposal
  int proposal = 0;
  for (auto name : block_producers){
    const auto & b = bps_tbl.get(name,"setemergency: bpname is not registered");
    proposal += b.emergency ? 1 : 0;
  }

  //update chainstatus
  cstatus_tbl.modify(cstatus, 0, [&](chain_status & cs) {
    cs.emergency = proposal > num_of_top_bps * 2 / 3;
  });

}

bool system_contract::check_emergency() {
  //assert chainstatus
  cstatus_table cstatus_tbl(_self, _self);
  const auto & cstatus = cstatus_tbl.get(N(chainstatus),"get chainstatus fatal");

  return cstatus.emergency;
}

}
