# System Contract

<!-- vim-markdown-toc GFM -->

* [Command Reference](#command-reference)
    * [Table](#table)
        * [accounts](#accounts)
        * [votes](#votes)
        * [bps](#bps)
        * [chainstatus](#chainstatus)
    * [Action](#action)
        * [transfer](#transfer)
        * [updatebp](#updatebp)
        * [vote](#vote)
        * [unfreeeze](#unfreeeze)
        * [claim](#claim)
        * [setemergency](#setemergency)
* [License](#license)

<!-- vim-markdown-toc -->

## Command Reference

### Table

#### accounts

```bash
$ cleos get table eosio eosio accounts --key account_name
```

#### votes

```bash
$ cleos get table eosio user1 votes
```

#### bps

```bash
$ cleos get table eosio eosio bps
```

#### chainstatus

```bash
$ cleos get table eosio eosio chainstatus
```

### Action

#### transfer

```bash
$ cleos push action eosio transfer '["twryy4swtrj3","eosio","20.0000 EOS","my first transfer"]' -p twryy4swtrj3
```

#### updatebp

```bash
$ cleos push action eosio updatebp '{"bpname":"prozjb","block_signing_key":"EOS8DNUjdm25rZsCcnhxqyJJTdP2kQkRPuBpeFZykXCWbUt41RNf5","commission_rate":"1"}' -p prozjb
```

#### vote

```bash
$ cleos push action eosio vote '{"voter":"user1","bpname":"prozjb","change":"10.0000 EOS"}' -p user1
```

#### unfreeeze

```bash
$ cleos  push action eosio unfreeze  '{"voter":"user1","bpname":"prozjb"}' -p user1
```

#### claim

```bash
$ cleos  push action eosio claim  '{"voter":"user1","bpname":"prozjb"}' -p user1
```

#### setemergency

```bash
$ cleos push action eosio setemergency '{"bpname":"biosbpp","emergency":true}' -p biosbpp
```
