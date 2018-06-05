# EOS Force


<!-- vim-markdown-toc GFM -->

* [Model](#model)
    * [User Asset](#user-asset)
    * [Block reward](#block-reward)
    * [Transaction fee](#transaction-fee)
    * [Faucet](#faucet)
* [Governance](#governance)
    * [Voting dividend](#voting-dividend)
    * [One EOS one vote](#one-eos-one-vote)
    * [23 BP](#23-bp)
    * [Set Emergency](#set-emergency)

<!-- vim-markdown-toc -->

Diving into EOSIO software for quite a while, we have found lots of factors which may result in the unstability of chain, e.g., the uncertainty of writing C++ smart contract based on WASM virtual machine, one EOS 30 votes leading to "supernode union", and so forth. If the chain is launched under EOSIO's official guideline, then promoted elections, voting, transaction, deployment of the contract, it'll be difinitely difficult to ensure user asset being safe.

Prioritizing the safety of user asset, improving continously the stability of EOSIO, we hereby start large-scale public testing to improve the safety and stability of EOS.

By adjusting cost time of producing blocks, charging transaction fees, encouraging super nodes’ dividend paying, and releasing self-deployment contract functions in different stages, EOS Force is committed to further improving the stability and security of the chain.

> How to join EOS Force testnet?

Please refer to [testnet-v0.5](https://github.com/eosforce/testnet-v0.5) for more details.

System contract used in testnet-v0.5 is also released at [eosforce/System](https://github.com/eosforce/System).

> How can users participate in ?

[Download testnet wallet](https://github.com/eosforce/wallet-desktop/releases).

You can also compile the wallet by yourself, which supports Windows, Linux and macOS.

When your wallet is ready, please join in the telegram group and get your testnet token:

- English Telegram: https://t.me/eosforce_en
- Chinese Telegram: https://t.me/eosforce01
- Testnet technical group: https://t.me/EOSForce

Welcome to join in our testnet!

## Model

### User asset

EOS Force supports register of EOS ERC20 tokens on Ethereum. The asset of EOS Force users has the following properties:

- Available balance: available for transfer, voting.
- Voting Amount: The amount invested to different nodes will be locked, reducing the amount of redemption after voting.
- Redemption Amount: The amount of the cancelled ballot, which has a 3-day freeze period, can be extracted into available balance after 3 days.
- To receive dividends: The user occupies part of the node's reward pool based on the contribution to the node's election currency and time, and becomes available after extraction.

### Block reward

EOSIO's default 0.5s block producing speed has not been verified in global distributed networks, and network delay is likely to cause blockchain fork and stuck. Therefore, EOS Force sets the block producing time as 3 seconds in the start-up stage. Each node only produces one block at a time, and it can get 9 EOS as reward. When the chain is running stably, EOS Force will recover the block producing time to be 0.5 seconds, improving the performance of the chain.

### Transaction fee

EOSIO requires the users mortgage their tokens to obtain resources, use the blockchain competitively and then achieve the purpose of “free transaction fee”. The "free transaction fee" is actually self-deceiving, and the super node can receive a 1% annual reward, which essentially transfers the transaction fee to the 1% annual inflation that the user must bear.

In order to protect the chain from DDOS attacks, EOS Force resumed the transaction fee and billed by the type of transaction execution. The user did not need to set the amount of fee, and the system will automatically deduct the balance from the transaction initiator. If it is lack of balance ,transaction will be failed.

### Faucet

EOS public and private keys can be generated off the chain, but EOS users need to create a user name before they can operate on the chain. So activated users are needed to send on-chain transactions to new users in order to help them create accounts. By default users need to find Tripartite help. EOS Force's wallet has built-in nodes to open taps, and these nodes are responsible for creating a chain of fees for the account, providing a seamless experience for new users.

## Governance

### Voting dividend

If the users won’t get dividends, their willingness to vote will be reduced, which results in low voting willingness of private users and low voting rate of the chain. Several large holders may join together to manipulate the voting process, influence elections, and carry out fork attacks. Therefore, we encourage super nodes to pay dividends to users who vote for them, in this way we can fully activate the users participation.

EOS Force has approximately 90 million EOS awards each year. Super nodes can set their own commission ratios, such as 1%. After the node is elected and out of the block, it can take away 1% of each block reward, and the remaining 99% will enter the reward pool of each node. According to the voting amount and time of each user, the node derives the “ticket age” of the user. Then according to the “total ticket age” of all the users of the node, the percentage of dividends per user in the reward pool is calculated, and the users who vote for the node are available at any time. Dividends can be drawn from the pool of rewards.

If only EOS Force’s 300 million EOS will participate in the voting, all these voting users will receive 90 million EOS awards. The annualized interest rate is about RMB 100 million/300 million, or 30%. The user's annualized interest rate decreases as the voting participation rate increases. As the total amount of coins rises, the proportion of annual rewards will decline year by year.

In order to reduce the amount of computing resources consumed by automatic distribution, EOS Force’s voting bonus needs to be manually collected by the user. The speed of collection does not affect the amount of dividends, and the dividends paid will immediately become available balances.

Every time the user extracts dividends, the "ticket age" at the node will be zeroed and accumulated again.

Changing the voting amount of a node will automatically receive the dividend payable for the previous voting, and will be recalculated after the dividend is cleared.

### One EOS one vote

EOS Force implements a vote-for-vote user voting mechanism. One EOS can only be voted for a certain node, but one user can give different numbers of coins to multiple nodes.

Assume that a user has 1000 EOS, the commission rate of node A is 1%, the user gives A 300 EOS, the commission ratio of node B is 1.5%, and the user gives B 100 EOS, the available balance of the user is left With 600 EOSs, users can finally obtain corresponding voting dividends from these two nodes.

EOS Force allows users to adjust the number of votes, that is, increase or decrease the number of votes. If you increase the vote, you will automatically receive a dividend and deduct the available balance. If you reduce the number of votes, you will automatically receive a dividend once again. At the same time, there will be a three-day freeze period for the reduced amount of money. After 3 days, the user needs to manually perform the “freeze-free” operation to change the voting amount into the available balance.

### 23 BP

21, multiples of 3, is not technically suitable for BFT algorithm. If it is a node of 21 and just happens to have a 14-vote agreement and a 7-vote situation, it will not be able to pass more than two-thirds of the pass, nor will it be able to reach a veto greater than one-third, and governance will be deadlocked. If it is 23 nodes, which is not an integer multiple of 3, then there will eventually be a 15-vote agreement, 8 votes against the veto decision, or 16 votes in favor. With 7 votes in opposition, the decision will not result in a stalemate.

### Set emergency

EOS chain still cannot fully confirm the stability. If the chain has unexpected BUGs, then it is necessary to set the emergency state so that the chain can enter the super node governance state. Once an emergency is entered, operations such as transfer, voting, and dividends that may affect the security of the user's assets are immediately stopped, and only node-related operations are allowed. Only the registering node can open and close the emergency state. If 16 out of 23 working nodes agree to open, the emergency state starts. After the problem is resolved, the super node can choose to close the emergency state. When the number of emergency state nodes is greater than 8, the full functionality of the chain is restored.
