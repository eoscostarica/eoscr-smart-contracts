#include <producerjson.hpp>

ACTION producerjson_contract::set(name owner, string json) {
  require_auth(owner);

  // Check producer info table. Owner should exist (has called regproducer) and be activated.
  // Init the _producerjson table
  check( is_blockproducer(owner), "user is not an active producer" );

  producerjson_table _producerjson(_self, _self.value);
  // Quick check to remind the user the payload must be json.
  check(json[0] == '{',             "payload must be json");
  check(json[json.size()-1] == '}', "payload must be json");

  // If entry exists, update it.
  auto target_itr = _producerjson.find(owner.value);
  if (target_itr != _producerjson.end()) {
    _producerjson.modify(target_itr, owner, [&](auto& row) {
      row.owner = owner;
      row.json  = json;
    });
  } else {  // Otherwise, create a new entry for them.
    _producerjson.emplace(owner, [&](auto& row) {
      row.owner = owner;
      row.json  = json;
    });
  }
}

ACTION producerjson_contract::del(name owner) {
  require_auth(owner);

  producerjson_table _producerjson(_self, _self.value);
  auto target_itr = _producerjson.find(owner.value);
  _producerjson.erase(target_itr);
}
