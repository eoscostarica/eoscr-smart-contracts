#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT producerjson : public contract {
  public:
    using contract::contract;

    ACTION set(name owner, string json)
    ACTION del(name owner)

  private:
    TABLE producerjson {
      name      owner;
      string    json;
      auto primary_key() const {  return owner;  }
    };
    typedef multi_index<name("producerjson"), producerjson> producerjson_table;
};