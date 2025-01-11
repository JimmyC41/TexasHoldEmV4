#include "../../include/Utils/PlayerUtil.h"
#include "boost/uuid.hpp"
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>
#include <regex>

namespace uuids = boost::uuids;

constexpr int MIN_BIG_BLINDS = 1;

string PlayerUtil::generateUUID() {
    static uuids::random_generator generator;
    uuids::uuid uuid = generator();
    return to_string(uuid);
}

vector<string> PlayerUtil::playerPointersToIds(vector<Player*> players) {
    vector<string> ids;
    for (const auto& player : players) ids.push_back(player->getId());
    return ids;
}

bool PlayerUtil::isValidName(const string& name) {
    regex namePattern("^[A-Za-z][A-Za-z0-9' -]*[A-Za-z0-9]$");
    return !name.empty() && regex_match(name, namePattern);
}

bool PlayerUtil::isMinBuyin(size_t bigBlind, const uint32_t& chips) {
    return (chips >= bigBlind * MIN_BIG_BLINDS);
}