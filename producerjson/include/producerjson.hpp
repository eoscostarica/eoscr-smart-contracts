#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
#include <eosio/permission.hpp>
// #include <eosio.system/eosio.system.hpp>

using namespace std;
using namespace eosio;
using eosio::public_key;

namespace eosio {
  constexpr name system_account{"eosio"_n};

  /*
  * EOSIO producer_info table
  */
  struct producer_info {
      name                  owner;
      double                total_votes = 0;
      eosio::public_key     producer_key; /// a packed public key object
      bool                  is_active = true;
      std::string           url;
      uint32_t              unpaid_blocks = 0;
      time_point            last_claim_time;
      uint16_t              location = 0;

      uint64_t primary_key()const { return owner.value;                             }
      double   by_votes()const    { return is_active ? -total_votes : total_votes;  }
      bool     active()const      { return is_active;                               }
      void     deactivate()       { producer_key = public_key(); is_active = false; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( producer_info, (owner)(total_votes)(producer_key)(is_active)(url)
                      (unpaid_blocks)(last_claim_time)(location) )
  };
  typedef eosio::multi_index< "producers"_n, producer_info,
                          indexed_by<"prototalvote"_n, const_mem_fun<producer_info, double, &producer_info::by_votes>>
                          > producers_table;

  /**
  *
  *  Verify is an account is a block producer
  *
  * @param bp_name - Contains the name of the account that we want to verify as bp
  *
  * @return true is the account is a block producer, otherwise returns false
  */                        
  bool is_blockproducer(name bp_name){
      producers_table bp(system_account, system_account.value);
      auto it = bp.find(bp_name.value);
      if (it==bp.end()) {
          return false;
      }
      return it->is_active && it->total_votes > 0.0;
  }
}

CONTRACT producerjson_contract : public contract {
  public:
    using contract::contract;

    ACTION set(name owner, string json);
    ACTION del(name owner);

  private:
    TABLE producerjson {
      name      owner;
      string    json;
      auto primary_key() const {  return owner.value;  }
    };
    typedef multi_index<name("producerjson"), producerjson> producerjson_table;
};