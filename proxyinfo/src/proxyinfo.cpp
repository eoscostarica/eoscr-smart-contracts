#include <proxyinfo.hpp>

ACTION proxyinfo::create(const name& proxy, const string& name,  const string& slogan, const string& philosophy, const string& background, const string& website, const string& logo_256, const string& telegram, const string& steemit, const string& twitter, const string& wechat) {
  check(!name.empty(), "name required");
  check(name.length() <= 64, "name too long");
  check(slogan.length() <= 64, "slogan too long");
  check(philosophy.length() <= 1024, "philosophy too long");
  check(background.length() <= 1024, "background too long");
  check(website.length() <= 256, "website too long");

  if (!website.empty())
    check(website.substr(0, 4) == "http", "website should begin with http");

  check(logo_256.length() <= 256, "logo_256 too long");
  if (!logo_256.empty())
    check(logo_256.substr(0, 4) == "http", "logo_256 should begin with http");

  check(telegram.length() <= 64, "telegram too long");
  check(steemit.length() <= 64, "steemit too long");
  check(twitter.length() <= 64, "twitter too long");
  check(wechat.length() <= 64, "wechat too long");

  // Require auth from the proxy account
  require_auth(proxy);

  proxies_table _proxies(get_self(), get_self().value);
  // Check if exists
  auto current = _proxies.find(proxy.value);

  // Update
  if (current != _proxies.end()) {
    _proxies.modify(current, proxy, [&]( auto& i ) {
      i.owner = proxy;
      i.name = name;
      i.website = website;
      i.slogan = slogan;
      i.philosophy = philosophy;
      i.background = background;
      i.logo_256 = logo_256;
      i.telegram = telegram;
      i.steemit = steemit;
      i.twitter = twitter;
      i.wechat = wechat;
    });

  // Insert
  } else {
    _proxies.emplace(proxy, [&]( auto& i ) {
      i.owner = proxy;
      i.name = name;
      i.website = website;
      i.slogan = slogan;
      i.philosophy = philosophy;
      i.background = background;
      i.logo_256 = logo_256;
      i.telegram = telegram;
      i.steemit = steemit;
      i.twitter = twitter;
      i.wechat = wechat;
    });
  }
}

ACTION proxyinfo::remove(const name& proxy) {
  // Require auth from the proxy account
  require_auth(proxy);

  proxies_table _proxies(get_self(), get_self().value);

  // Delete record
  auto lookup = _proxies.find(proxy.value);
  if (lookup != _proxies.end()) {
    _proxies.erase(lookup);
  }
}