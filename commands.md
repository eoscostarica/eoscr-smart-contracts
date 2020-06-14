## Compile

```
cd contracts/consent2life
eosio-cpp -abigen ./src/consent2life.cpp -o consent2life.wasm -I ./include/ -R ./ricardian
```

### Deploy local

#### consent2life

```
cleos wallet create -n consent2life --to-console

Creating wallet: lifebankcode
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"YYY"
```

```
cleos wallet import -n consent2life --private-key XXX
imported private key for: EOS8SGFWbhTao1dnVRt9H5SkaKVtvpKiF6oG45SjybVzdASwpZRCN
```

```
cleos wallet unlock -n consent2life --password YYY
```

```
cleos -u https://jungle.eosio.cr set contract consent2life ./ consent2life.wasm consent2life.abi -p consent2life@active
```
