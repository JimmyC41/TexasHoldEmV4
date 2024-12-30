#include "../../include/Utils/PlayerUtil.h"
#include "boost/uuid.hpp"
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>

namespace uuids = boost::uuids;

string PlayerUtil::generateUUID() {
    static uuids::random_generator generator;
    uuids::uuid uuid = generator();
    return to_string(uuid);
}

vector<string> PlayerUtil::playerPointersToIds(vector<shared_ptr<Player>>& players) {
    vector<string> ids;
    for (const auto& player : players) ids.push_back(player->getId());
    return ids;
}