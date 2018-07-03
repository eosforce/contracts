# System Contract

<!-- vim-markdown-toc GFM -->

* [Command Reference](#command-reference)
    * [Table](#table)
        * [eosio](#eosio)
            * [accounts](#accounts)
            * [votes](#votes)
            * [bps](#bps)
            * [chainstatus](#chainstatus)
            * [schedules](#schedules)
        * [eosio.token](#eosiotoken)
            * [accounts](#accounts-1)
            * [stat](#stat)
    * [Action](#action)
        * [eosio](#eosio-1)
            * [create account](#create-account)
            * [transfer](#transfer)
            * [updatebp](#updatebp)
            * [vote](#vote)
            * [unfreeeze](#unfreeeze)
            * [claim](#claim)
            * [setemergency](#setemergency)
        * [eosio.token](#eosiotoken-1)
            * [create](#create)
            * [issue](#issue)
            * [transfer](#transfer-1)

<!-- vim-markdown-toc -->
## api

https://documenter.getpostman.com/view/4394576/RWEnobze

## Command Reference

### Table

For the tables below, you could apply `-k` or `--key` flag to specify a certain row if you do not want to receive all the records in the table.

#### eosio

##### accounts

```bash
$ cleos get table eosio eosio accounts

# Get coin balance
$ cleos get table eosio eosio accounts --key account_name
```

<details>
<summary>Example</summary>

```bash
$ cleos get table eosio eosio accounts
{
  "rows": [{
      "name": "eosio",
      "available": "119.5000 EOS"
    },{
      "name": "prozjb",
      "available": "200.0512 EOS"
    },{
      "name": "prozjc",
      "available": "200.2024 EOS"
    },{
      "name": "prozjd",
      "available": "0.0000 EOS"
    },{
      "name": "twryy4swtrj3",
      "available": "99179.5000 EOS"
    },{
      "name": "user1",
      "available": "352.3819 EOS"
    },{
      "name": "user2",
      "available": "202.5277 EOS"
    }
  ],
  "more": false
}
```

</details>

##### votes

```bash
$ cleos get table eosio account_name votes

$ cleos get table eosio account_name votes --key bpname
```

<details>
<summary>Example</summary>

```bash
$ cleos get table eosio user1 votes
{
  "rows": [{
      "bpname": "biosbpa",
      "staked": "100.0000 EOS",
      "stake_time": "2018-06-04T05:12:42",
      "unstaking": "0.0000 EOS",
      "unstake_time": "2018-06-04T05:12:42"
    }
  ],
  "more": false
}
```

</details>

##### bps

```bash
$ cleos get table eosio eosio bps

$ cleos get table eosio eosio bps --key name
```

<details>
<summary>Example</summary>

```bash
$ cleos get table eosio eosio bps
{
  "rows": [{
      "name": "biosbpa",
      "block_signing_key": "EOS7xTPgP8HxZZSUvuoyKaw4dNGGQPHbpGYzLCYKh6evSqBNxHsWr",
      "commission_rate": 0,
      "total_staked": "102.0000 EOS",
      "rewards_pool": "6948.3000 EOS",
      "total_voteage": 180510000,
      "voteage_update_time": "2018-06-04T05:12:42",
      "emergency": 0
    },{
      "name": "biosbpb",
      "block_signing_key": "EOS5Ubn1UUACaFLZBA3eEoYtMWFZ5ae3TL8Hmavvv958Nha5cu9h5",
      "commission_rate": 10000,
      "total_staked": "3.0000 EOS",
      "rewards_pool": "0.4928 EOS",
      "total_voteage": 18750000,
      "voteage_update_time": "2018-06-04T03:00:30",
      "emergency": 0
    },{
      "name": "biosbpc",
      "block_signing_key": "EOS8msJkLJLw1wJxqp6xtdjSyzEnc7rbEvPquPVYDzZTS6CE5ASy7",
      "commission_rate": 5000,
      "total_staked": "2.0000 EOS",
      "rewards_pool": "3474.2000 EOS",
      "total_voteage": 20100000,
      "voteage_update_time": "2018-06-04T03:00:30",
      "emergency": 0
    },{
      "name": "biosbpd",
      "block_signing_key": "EOS7v1i8AN4pnpyCk4gUqQSatW2kQStswWj2pp6oWjUX5sQMbrWnP",
      "commission_rate": 3333,
      "total_staked": "2.0000 EOS",
      "rewards_pool": "4632.6316 EOS",
      "total_voteage": 19200000,
      "voteage_update_time": "2018-06-04T03:00:33",
      "emergency": 0
    },{
      "name": "biosbpe",
      "block_signing_key": "EOS5YdYtb8SdAqMYCqMwHN5pYp1sEo8im3WoBoE4WD1caCYJf4jz5",
      "commission_rate": 2500,
      "total_staked": "1.0000 EOS",
      "rewards_pool": "117.8764 EOS",
      "total_voteage": 2130000,
      "voteage_update_time": "2018-06-04T03:04:09",
      "emergency": 0
    },{
      "name": "biosbpf",
      "block_signing_key": "EOS7mJ5NVErooVzzpExneJ2U5thBs45W622qjk88Bnw8KXWUwQ7xG",
      "commission_rate": 2000,
      "total_staked": "2.0000 EOS",
      "rewards_pool": "5551.7000 EOS",
      "total_voteage": 17280000,
      "voteage_update_time": "2018-06-04T03:00:39",
      "emergency": 0
    },{
      "name": "biosbpg",
      "block_signing_key": "EOS5gGS2w2va7ffUGtTYTSTtc55bdrELGrFfYyGPbBfEyjv2UH9yK",
      "commission_rate": 1666,
      "total_staked": "2.0000 EOS",
      "rewards_pool": "870.1696 EOS",
      "total_voteage": 19740000,
      "voteage_update_time": "2018-06-04T03:00:42",
      "emergency": 0
    },{
      "name": "biosbph",
      "block_signing_key": "EOS6sPazd4A8nJE9Spv1qiBvxMZRBLB3XEhdUCaiGApJ9V6CKXgRD",
      "commission_rate": 1428,
      "total_staked": "2.0000 EOS",
      "rewards_pool": "895.0168 EOS",
      "total_voteage": 18840000,
      "voteage_update_time": "2018-06-04T03:00:48",
      "emergency": 0
    },{
      "name": "biosbpi",
      "block_signing_key": "EOS6s1sVkWpNds1Go4ieXmgffF3XEfvr2HKYjmD3NYh3HZBXSMp7P",
      "commission_rate": 1250,
      "total_staked": "2.0000 EOS",
      "rewards_pool": "913.9000 EOS",
      "total_voteage": 19110000,
      "voteage_update_time": "2018-06-04T03:00:48",
      "emergency": 0
    }
  ],
  "more": true
}
```

</details>

##### chainstatus

```bash
$ cleos get table eosio eosio chainstatus

$ cleos get table eosio eosio chainstatus --key name
```

<details>
<summary>Example</summary>

```bash
$ cleos get table eosio eosio chainstatus
{
  "rows": [{
      "name": "chainstatus",
      "emergency": 0
    }
  ],
  "more": false
}
```

</details>

##### schedules

```bash
$ cleos get table eosio eosio schedules

$ cleos get table eosio eosio schedules -k version_num
```

<details>
<summary>Example</summary>
$ cleos get table eosio eosio schedules
{
  "rows": [{
      "version": 0,
      "block_height": 2,
      "producers": [{
          "bpname": "biosbpa",
          "amount": 3
        },{
          "bpname": "biosbpb",
          "amount": 3
        },{
          "bpname": "biosbpc",
          "amount": 3
        },{
          "bpname": "biosbpd",
          "amount": 3
        },{
          "bpname": "biosbpe",
          "amount": 3
        },{
          "bpname": "biosbpf",
          "amount": 3
        },{
          "bpname": "biosbpg",
          "amount": 3
        },{
          "bpname": "biosbph",
          "amount": 2
        },{
          "bpname": "biosbpi",
          "amount": 2
        },{
          "bpname": "biosbpj",
          "amount": 2
        },{
          "bpname": "biosbpk",
          "amount": 2
        },{
          "bpname": "biosbpl",
          "amount": 2
        },{
          "bpname": "biosbpm",
          "amount": 2
        },{
          "bpname": "biosbpn",
          "amount": 2
        },{
          "bpname": "biosbpo",
          "amount": 2
        },{
          "bpname": "biosbpp",
          "amount": 2
        },{
          "bpname": "biosbpq",
          "amount": 2
        },{
          "bpname": "biosbpr",
          "amount": 2
        },{
          "bpname": "biosbps",
          "amount": 2
        },{
          "bpname": "biosbpt",
          "amount": 2
        },{
          "bpname": "biosbpu",
          "amount": 3
        },{
          "bpname": "biosbpv",
          "amount": 3
        },{
          "bpname": "biosbpw",
          "amount": 3
        }
      ]
    }
  ],
  "more": false
}

</details>

#### eosio.token

##### accounts

```bash
# get token balance
$ cleos get table eosio.token account_name accounts
```

<details>
<summary>Example</summary>

```bash
$ cleos get table eosio.token user1 accounts
{
  "rows": [{
      "balance": "5.0000 PP"
    }
  ],
  "more": false
}
```
</details>

##### stat

```bash
$ cleos get table eosio.token token_name stat
```

<details>
<summary>Example</summary>

```bash
# given that a token called EOP has been created
$ cleos get table eosio.token EOP stat
{
  "rows": [{
      "supply": "5.0000 EOP",
      "max_supply": "100.0000 EOP",
      "issuer": "user1"
    }
  ],
  "more": false
}
```
</details>

### Action

Each action has a cost:

Contract           | Action       | Transaction Fee (EOS)
:----:             | :----:       | :----:
eosio              | newaccount   | 0.1
eosio              | updatebp     | 100
eosio              | vote         | 0.05
eosio              | unfreeze     | 0.01
eosio              | claim        | 0.03
eosio              | setemergency | 10
eosio, eosio.token | transfer     | 0.01
eosio.token        | create       | 10
eosio.token        | issue        | 0.01

#### eosio

##### create account

parameters:

- `creator`
- `new_account`
- `pub_key`
- `pub_key`

```bash
$ cleos create account creator new_account pub_key pub_key
```

<details>
<summary>Example</summary>

```bash
$ cleos create account cindydaily laoma EOS5MFoVFWAkeZgjxMCBTDjhrxmNefFKSGZUbewH35tJGSqzaFRpU EOS5MFoVFWAkeZgjxMCBTDjhrxmNefFKSGZUbewH35tJGSqzaFRpU
executed transaction: 70e2b9cb9ea977e42a70ea9a5f82bd68b420a777015d4624c558cd0a42a9225a  216 bytes  1132 us
#         eosio <= eosio::newaccount            "00808fce249fa643000000000023a989010000000100023cc6babc9f5c042daf20052a2e9b74ca79de359085e4bb0748f67...
warning: transaction executed locally, but may not be confirmed by the network yet
```
</details>

##### transfer

parameters:

- `from`
- `to`
- `quantity`
- `memo`

```bash
$ cleos push action eosio transfer '{"from":"from","to":"to","quantity":"quantity","memo":"memo"}' -p from
```

<details>
<summary>Example</summary>

```bash
$ cleos   push action eosio transfer '{"from":"eosforce","to":"user1","quantity":"10.0000 EOS","memo":"my first transfer"}' -p eosforce
executed transaction: 34dbe8bb08d0f7c3d5a4453d1e068e35f03c96f25d200c4e2a795e6aec472d60  160 bytes  6782 us
#         eosio <= eosio::transfer              {"from":"eosforce","to":"user1","quantity":"10.0000 EOS","memo":"my first transfer"}
warning: transaction executed locally, but may not be confirmed by the network yet
```

</details>

##### updatebp

parameters:

- `bpname`: bp name
- `block_signing_key`: EOS public key
- `commission_rate`: the valid range is 0~10000, meaning 0%~100%
- `url`: BP's website, e.g., `https://eosforce.io`

```bash
$ cleos push action eosio updatebp '{"bpname":"bpname","block_signing_key":"block_signing_key","commission_rate":"commission_rate","url":"https://eosforce.io"}' -p bpname
```

<details>
<summary>Example</summary>

```bash
$ cleos push action eosio updatebp '{"bpname":"biosbpa","block_signing_key":"EOS7xTPgP8HxZZSUvuoyKaw4dNGGQPHbpGYzLCYKh6evSqBNxHsWr","commission_rate":"100","url":"http://eosforce.io"}' -p biosbpa
executed transaction: b3607a39c71cfe9a5926aae3cc0492bf76644c9bc55a02a5f16da549d0e1a208  160 bytes  4669 us
#         eosio <= eosio::updatebp              {"bpname":"biosbpa","block_signing_key":"EOS7xTPgP8HxZZSUvuoyKaw4dNGGQPHbpGYzLCYKh6evSqBNxHsWr","com...
warning: transaction executed locally, but may not be confirmed by the network yet
```

</details>


##### vote

parameters:

- `voter`: account name
- `bpname`: bp name
- `stake`: amount `voter` wants to vote `bpname`

```bash
$ cleos push action eosio vote '{"voter":"voter","bpname":"bpname","stake":"stake"}' -p voter
```

<details>
<summary>Example</summary>

```bash
$ cleos push action eosio vote '{"voter":"biosbpb","bpname":"biosbpa","stake":"10.0000 EOS"}' -p biosbpb
executed transaction: f91df3ed914d06953190bf0c5186c0519383af5eb76fbdd3248499afd41afe20  144 bytes  6820 us
#         eosio <= eosio::vote                  {"voter":"biosbpb","bpname":"biosbpa","stake":"10.0000 EOS"}
warning: transaction executed locally, but may not be confirmed by the network yet
$ cleos get table eosio biosbpb votes
{
  "rows": [{
      "bpname": "biosbpa",
      "staked": "10.0000 EOS",
      "voteage": "125700000000",
      "voteage_update_time": "2018-06-06T10:18:39",
      "unstaking": "99999990.0000 EOS",
      "unstake_time": "2018-06-06T10:18:39"
    }
  ],
  "more": false
}
```

</details>

##### unfreeeze

parameters:

- `voter`: account name
- `bpname`: bp name

```bash
$ cleos  push action eosio unfreeze '{"voter":"voter","bpname":"bpname"}' -p voter
```

<details>
<summary>Example</summary>

```bash
$ cleos get table eosio user1 votes
{
  "rows": [{
      "bpname": "biosbpa",
      "staked": "90.0000 EOS",
      "stake_time": "2018-06-04T05:22:06",
      "unstaking": "10.0000 EOS",
      "unstake_time": "2018-06-04T05:22:06"
    }
  ],
  "more": false
}
$ cleos  push action eosio unfreeze '{"voter":"user1","bpname":"biosbpa"}' -p user1
executed transaction: 337057640aafeba1306c44f9222a32e2b290e72cd56f828c07d7f73aed54fc76  128 bytes  5772 us
#         eosio <= eosio::unfreeze              {"voter":"user1","bpname":"biosbpa"}
warning: transaction executed locally, but may not be confirmed by the network yet
$ cleos get table eosio user1 votes
{
  "rows": [{
      "bpname": "biosbpa",
      "staked": "90.0000 EOS",
      "stake_time": "2018-06-04T05:22:06",
      "unstaking": "0.0000 EOS",
      "unstake_time": "2018-06-04T05:22:06"
    }
  ],
  "more": false
}
```

</details>

##### claim

parameters:

- `voter`: account name
- `bpname`: bp name

```bash
$ cleos push action eosio claim '{"voter":"voter","bpname":"bpname"}' -p voter
```

<details>
<summary>Example</summary>

```bash
$ cleos get table eosio eosio accounts -k user1
{
  "rows": [{
      "name": "user1",
      "available": "6151.6714 EOS"
    }
  ],
  "more": false
}
$ cleos get table eosio eosio bps -k biosbpa
{
  "rows": [{
      "name": "biosbpa",
      "block_signing_key": "EOS7xTPgP8HxZZSUvuoyKaw4dNGGQPHbpGYzLCYKh6evSqBNxHsWr",
      "commission_rate": 100,
      "total_staked": "92.0000 EOS",
      "rewards_pool": "1823.6986 EOS",
      "total_voteage": 191790000,
      "voteage_update_time": "2018-06-04T05:22:06",
      "emergency": 0
    }
  ],
  "more": false
}
$ cleos  push action eosio claim '{"voter":"user1","bpname":"biosbpa"}' -p user1
executed transaction: dcb920962e75e4fd8bd7de62782d4156bfdbf98944704682cebcd568074d60b4  128 bytes  5834 us
#         eosio <= eosio::claim                 {"voter":"user1","bpname":"biosbpa"}
>> --claim--reward----1115.6995 EOS
warning: transaction executed locally, but may not be confirmed by the network yet
$ ./cleos get table eosio eosio bps -k biosbpa
{
  "rows": [{
      "name": "biosbpa",
      "block_signing_key": "EOS7xTPgP8HxZZSUvuoyKaw4dNGGQPHbpGYzLCYKh6evSqBNxHsWr",
      "commission_rate": 100,
      "total_staked": "92.0000 EOS",
      "rewards_pool": "707.9991 EOS",
      "total_voteage": 198750000,
      "voteage_update_time": "2018-06-04T05:27:54",
      "emergency": 0
    }
  ],
  "more": false
}
$ cleos get table eosio eosio accounts -k user1
{
  "rows": [{
      "name": "user1",
      "available": "7267.2709 EOS"
    }
  ],
  "more": false
}
```

</details>

##### setemergency

parameters:

- `bpname`: account name
- `emergency`: `true` or `false`

```bash
$ cleos push action eosio setemergency '{"bpname":"bpname","emergency":emergency}' -p bpname
```

<details>
<summary>Example</summary>

```bash
$ cleos push action eosio setemergency '{"bpname":"biosbpa","emergency":true}' -p biosbpa
executed transaction: 5d4bbcc4e04e0ed1107d1a75b564f3b4d612a30e531853266c79ebf7dd7bd756  120 bytes  14806 us
#         eosio <= eosio::setemergency          {"bpname":"biosbpa","emergency":1}
warning: transaction executed locally, but may not be confirmed by the network yet

$ cleos get table eosio eosio bps -k biosbpa
{
  "rows": [{
      "name": "biosbpa",
      "block_signing_key": "EOS7xTPgP8HxZZSUvuoyKaw4dNGGQPHbpGYzLCYKh6evSqBNxHsWr",
      "commission_rate": 100,
      "total_staked": "92.0000 EOS",
      "rewards_pool": "725.8191 EOS",
      "total_voteage": 198750000,
      "voteage_update_time": "2018-06-04T05:27:54",
      "emergency": 1
    }
  ],
  "more": false
}
```

</details>

#### eosio.token

##### create

parameters:

- `creator`: account_name
- `token`:

```bash
$ cleos push action eosio.token create '["creator","max_supply token_symbol"]' -p creator
```

<details>
<summary>Example</summary>

```bash
$ cleos push action eosio.token create '["user1","100.0000 EOP"]' -p biosbpa
executed transaction: b73d9a923c156828273109b2e1754c201ce01d7987ae4eca789e1580fcf64d14  136 bytes  2455 us
#   eosio.token <= eosio.token::create          {"issuer":"user1","maximum_supply":"100.0000 EOP"}

$ cleos get table eosio.token EOP stat
{
  "rows": [{
      "supply": "0.0000 EOP",
      "max_supply": "100.0000 EOP",
      "issuer": "user1"
    }
  ],
  "more": false
}
```
</details>

##### issue

parameters:

- `to`
- `quantity`
- `memo`

```bash
$ cleos push action eosio.token issue '["to", "quantity", "memo"]' -p token
```

<details>
<summary>Example</summary>

```bash
$ cleos push action eosio.token issue '["user1","5.0000 EOP","issue to user1"]' -p user1
executed transaction: e0d956a867ca4adb1d02455cf50b5f95b1ea02d32a538ee1fb110bbbe7bcbcdd  136 bytes  3048 us
#   eosio.token <= eosio.token::issue           {"to":"user1","quantity":"5.0000 EOP","memo":"issue to user1"}

$ cleos get table eosio.token user1 accounts
{
  "rows": [{
      "balance": "5.0000 EOP"
    }
  ],
  "more": false
}
```
</details>

##### transfer

parameters:

- `from`
- `to`
- `quantity`
- `memo`

```bash
$ cleos push action eosio transfer '["from", "to", "quantity", "memo"]' -p from
```

<details>
<summary>Example</summary>

```bash
$ cleos push action eosio.token transfer '["user1","user2","2.0000 EOP","memo"]' -p user1
executed transaction: b0f47409fad8f44ff31a1632bf90fda529d0e3e1e5396eef85d7fedf74999ffa  144 bytes  2706 us
#   eosio.token <= eosio.token::transfer        {"from":"user1","to":"user2","quantity":"2.0000 EOP","memo":"memo"}
#         user1 <= eosio.token::transfer        {"from":"user1","to":"user2","quantity":"2.0000 EOP","memo":"memo"}
#         user2 <= eosio.token::transfer        {"from":"user1","to":"user2","quantity":"2.0000 EOP","memo":"memo"}
```
</details>
