#include <easycontract.hpp>

ACTION easycontract::save(
  string date,
  string filename,
  string path
)
{
  require_auth(get_self());
}

EOSIO_DISPATCH(easycontract, (save))