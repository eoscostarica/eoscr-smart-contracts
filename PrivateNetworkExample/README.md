# easycontract
## Configure Local Wallet
### Create key pair
Execute `cleos create key --to-console` and save the output. (you can also use `--file filename` to save the output in a specific "filename" provided)

### Create Local Wallet
Execute `cleos wallet create -n easycontract --to-console` and save the output password (you can also use `-f easycontractpass.txt`)

### Import private key
`cleos wallet import -n easycontract --private-key YOUR_PRIVATE_KEY_HERE`

## Compile easycontract
`eosio-cpp -abigen -I include -R resource -contract easycontract -o easycontract.wasm src/easycontract.cpp`