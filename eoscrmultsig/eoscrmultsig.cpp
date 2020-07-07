/*
 * @file
 * @author  (C) 2020 by eoscostarica [ https://eoscostarica.io ]
 * @version 1.1.0
 *
 * @section DESCRIPTION
 *
 *   Example of Smart contract eoscrmultsig using multisignature 
 *   the main propouse of this contract is for explain how multisignature feature works
 *
 *
 *    WebSite:        https://eoscostarica.io
 *    GitHub:         https://github.com/eoscostarica
 *
 *
 *  the following accounts are required
 *  
 * eoscrmultsig: smart contract account
 * eoscrpropose : proposal creator 
 * eoscrsigner1 : signers accounts , each account must sign the proposal 
 * eoscrsigner2
 * eoscrsigner3
 *
 */
#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
#include <eosio/print.hpp>

using namespace eosio;
using namespace std;

CONTRACT eoscrmultsig : public eosio::contract {
    public:
    using contract::contract;

   /**
   *
   *  This action stores a user within the table users
   *
   * @param user_name - the user  name,
   *
   * @memo  if the require_auth(_self); authorization is used
   *        you need to include  eoscrmultsig within the proposal 
   *        on the auth structure definition 
   *        {"actor":"eoscrmultsig","permission":"active"}
   *        and an extra approval is requeried
   *        cleos  multisig approve eoscrpropose letmeadd '{"actor":"eoscrmultsig","permission":"active"}' -p eoscrmultsig@active
   *
   */
    ACTION add (name user_name) {
        //require_auth(_self);
        table_users table(_self, _self.value);
        table.emplace(_self, [&]( auto& row ) {
            row.id = table.available_primary_key();
            row.user_name = user_name;
        });
    }

   /**
   *
   *  Clear the content of the table users
   *
   */
    ACTION clean() {
        //only contract owner can erase table
        require_auth(_self);
        table_users table(_self, _self.value);
        auto table_itr = table.begin();
        while ( table_itr != table.end()) {
            table_itr = table.erase(table_itr);
        }
    }
    
    private:
    /*
    * Stores the data related with users'
    */
    TABLE users {
        uint64_t id;
        name user_name;
        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(users, (id)(user_name));
    };
    typedef eosio::multi_index<"users"_n, users > table_users;
};

EOSIO_DISPATCH(eoscrmultsig,(add)(clean));