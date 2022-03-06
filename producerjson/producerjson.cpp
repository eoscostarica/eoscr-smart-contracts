#include <producerjson.hpp>

ACTION producerjson::set(name owner, string json) {
  require_auth(owner);
    // Check producer info table. Owner should exist (has called regproducer) and be activated.
    // Init the _producerjson table
    producerjson_table _producerjson(get_self(), get_self().value);
    auto prod = _producers.get(owner,    "user is not a producer");
    check(prod.is_active == true, "user is not an active producer");
    check(prod.total_votes > 0.0, "user is not an active producer");

    // Quick check to remind the user the payload must be json.
    check(json[0] == '{',             "payload must be json");
    check(json[json.size()-1] == '}', "payload must be json");

    // If entry exists, update it.
    auto target_itr = producerjson.find(owner);
    if (target_itr != producerjson.end()) {
      producerjson.modify(target_itr, owner, [&](auto& j) {
        j.owner = owner;
        j.json  = json;
      });
    } else {  // Otherwise, create a new entry for them.
      producerjson.emplace(owner, [&](auto& j) {
        j.owner = owner;
        j.json  = json;
      });
    }
}

ACTION producerjson::del(name owner) {
  require_auth(owner);
  auto target_itr = producerjson.find(owner);
  producerjson.erase(target_itr);
}

EOSIO_DISPATCH(producerjson, (set)(del))
