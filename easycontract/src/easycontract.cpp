#include <easycontract.hpp>

ACTION easycontract::save(
  name sender,
  uint64_t tx_id,
  string date,
  string filename,
  string path
)
{
  require_auth(get_self());
}

EOSIO_DISPATCH(easycontract, (save))