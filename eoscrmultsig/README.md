# Multisignatures example
Example of Smart contract eoscrmultsig using multisignature,the main propouse of this contract is to explain how multisignature feature works

# Requeriments:

  You need the private key pair for
  
- EOS5Rc8VJCyNCYPdE4gQhqPMTetFXkJPagkq4dicPCPGTAr5d4qu8

  The following accounts are required
   
  - eoscrmultsig: smart contract account
  - eoscrpropose : proposal creator 
  - eoscrsigner1 : signers accounts , each account must sign the proposal 
  - eoscrsigner2
  - eoscrsigner3

# how to compile
  type the follow command within the folder  eoscrmultsig
  - eosio-cpp eoscrmultsig.cpp -R ricardian -o eoscrmultsig.wasm -abigen

# how to publish
- cleos -u http://jungle2.cryptolions.io:80 set contract eoscrmultsig . -p eoscrmultsig@active

# Description

# Step 1: Create **letmeadd** proposal

![image info](./images/msig_step1.png)

> cleos -u http://jungle2.cryptolions.io:80 multisig propose letmeadd '[{"actor":"eoscrsigner1","permission":"active"},
>                                                                      {"actor":"eoscrsigner2","permission":"active"},
>                                                                      {"actor":"eoscrsigner3","permission":"active"}]' 
>                                                                       '[{"actor":"eoscrsigner1","permission":"active"},
>                                                                         {"actor":"eoscrsigner2","permission":"active"},
>                                                                         {"actor":"eoscrsigner3","permission":"active"}]' 
>                                                                          eoscrmultsig add '{"user_name":"msigned data"}' eoscrpropose 1 -p eoscrpropose@active
