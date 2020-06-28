# Multisignatures example
Example of Smart contract eoscrmultsig using multisignature,the main propouse of this contract is for explain how multisignature feature works

# Requeriments:

  The following accounts are required
   
  eoscrmultsig: smart contract account
  eoscrpropose : proposal creator 
  eoscrsigner1 : signers accounts , each account must sign the proposal 
  eoscrsigner2
  eoscrsigner3

# how to compile
  type the follow command within the folder  eoscrmultsig
  eosio-cpp eoscrmultsig.cpp -R ricardian -o eoscrmultsig.wasm -abigen

# how to publish
cleos -u http://jungle2.cryptolions.io:80 set contract eoscrmultsig . -p eoscrmultsig@active