## Compile

```
cd contracts/consentforms
eosio-cpp -abigen ./src/consentforms.cpp -o consentforms.wasm -I ./include/ -R ./ricardian
```

### Deploy local

#### consentforms

```
cleos wallet create -n consentforms --to-console

Creating wallet: lifebankcode
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"YYY"
```

```
cleos wallet import -n consentforms --private-key XXX
imported private key for: EOS8SGFWbhTao1dnVRt9H5SkaKVtvpKiF6oG45SjybVzdASwpZRCN
```

```
cleos wallet unlock -n consentforms --password YYY
```

```
cleos -u https://jungle.eosio.cr set contract consentforms ./ consentforms.wasm consentforms.abi -p consentforms@active
```
