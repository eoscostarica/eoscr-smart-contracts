#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

using namespace std;
using namespace eosio;

CONTRACT proxyinfo: public contract {
  public:
    using contract::contract;

    ACTION create(const name& proxy, const string& name, const string& slogan, const string& philosophy, const string& background, const string& website, const string& logo_256, const string& telegram, const string& steemit, const string& twitter, const string& wechat);

    ACTION remove(const name& proxy);

    TABLE proxy {
      name owner;
      string name;
      string website;
      string slogan;
      string philosophy;
      string background;
      string logo_256;
      string telegram;
      string steemit;
      string twitter;
      string wechat;

      auto primary_key() const { return owner.value; }
      EOSLIB_SERIALIZE(proxy, (owner)(name)(website)(slogan)(philosophy)(background)(logo_256)(telegram)(steemit)(twitter)(wechat))
    };

    typedef multi_index<name("proxies"), proxy> proxies_table;
  private:
};