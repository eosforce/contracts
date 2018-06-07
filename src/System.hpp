/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/dispatcher.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/producer_schedule.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/chain.h>

namespace eosiosystem {

using eosio::asset;
using eosio::print;
using eosio::bytes;
using eosio::block_timestamp;
using std::string;


static constexpr uint64_t SYMBOL = S(4, EOS);
static constexpr time freezen_delay = 60; //3*24*3600;
static constexpr int num_of_top_bps = 23;
static constexpr int block_rewards = 3*30000; //9.0000 EOS
static constexpr int top_bps_update_cycle = 10; //every 1000 blocks update

class system_contract : private eosio::contract {
public:
  using eosio::contract::contract;

private:
  struct account_info {
    account_name name;
    asset        available = asset(0,SYMBOL);

    uint64_t primary_key()const { return name; }
    EOSLIB_SERIALIZE( account_info, (name) (available) )
  };

  struct vote_info {
    account_name   bpname;
    asset          staked = asset(0,SYMBOL);
    time           voteage_update_time = now();
    int64_t        voteage = 0; // asset.amount * time.seconds
    asset          unstaking = asset(0,SYMBOL);
    time           unstake_time = now();

    uint64_t        primary_key() const { return bpname; }
    EOSLIB_SERIALIZE( vote_info, (bpname) (staked) (voteage) (voteage_update_time) (unstaking) (unstake_time) )
  };

  struct bp_info {
    account_name    name;
    public_key      block_signing_key;
    uint32_t        commission_rate = 0; // 0 - 10000 for 0% - 100%
    asset           total_staked = asset(0,SYMBOL);
    asset           rewards_pool = asset(0,SYMBOL);
    int64_t         total_voteage = 0; // asset.amount * time.seconds
    time            voteage_update_time = now();
    bool            emergency = false;

    uint64_t primary_key() const { return name; }
    void update (public_key key, uint32_t rate) { block_signing_key = key; commission_rate = rate; }

    EOSLIB_SERIALIZE( bp_info, (name) (block_signing_key) (commission_rate) (total_staked)
    (rewards_pool) (total_voteage) (voteage_update_time) (emergency) )
  };

  struct chain_status {
    account_name  name = N(chainstatus);
    bool          emergency = false;

    uint64_t primary_key() const { return name; }
    EOSLIB_SERIALIZE( chain_status, (name) (emergency) )
  };

  typedef eosio::multi_index<N(accounts), account_info> accounts_table;
  typedef eosio::multi_index<N(votes), vote_info> votes_table;
  typedef eosio::multi_index<N(bps), bp_info> bps_table;
  typedef eosio::multi_index<N(chainstatus), chain_status> cstatus_table;

  inline uint32_t endian_reverse_u32( uint32_t x ) {
    return (((x >> 0x18) & 0xFF)        )
           | (((x >> 0x10) & 0xFF) << 0x08)
           | (((x >> 0x08) & 0xFF) << 0x10)
           | (((x        ) & 0xFF) << 0x18)
    ;
  }

  void update_elected_bps();

public:
  // @abi action
  void transfer(const account_name from, const account_name to, const asset quantity, const string /*memo*/);

  // @abi action
  void updatebp(const account_name bpname, const public_key producer_key, const uint32_t commission_rate);

  // @abi action
  void vote(const account_name voter, const account_name bpname, const asset stake);

  // @abi action
  void unfreeze(const account_name voter, const account_name bpname);

  // @abi action
  void claim( const account_name voter, const account_name bpname);

  // @abi action
  void onblock(const block_timestamp, const account_name bpname, const uint16_t, const block_id_type previous);

  // @abi action
  void onfee(const account_name actor, const asset fee, const account_name bpname);

  // @abi action
  void setemergency(const account_name bpname, const bool emergency);

};

  EOSIO_ABI(system_contract,
            //System.cpp
            (transfer)(updatebp)(vote)(unfreeze)(claim)(onblock)(onfee)(setemergency)
  )
} /// eosiosystem
