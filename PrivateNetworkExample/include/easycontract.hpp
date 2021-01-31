#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT easycontract : public contract
{
public:
  using contract::contract;

  ACTION save(
    name sender,
    uint64_t tx_id,
    string date,
    string filename,
    string path
  );
private:
};