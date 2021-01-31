#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT easycontract : public contract
{
public:
  using contract::contract;

  ACTION save(
    string date,
    string filename,
    string path
  );
private:
};