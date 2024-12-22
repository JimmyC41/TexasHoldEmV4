#include "../include/Utils/PlayerUtil.h"

string PlayerUtil::generateUUID() {
    uuid_t uuid;
    char uuidStr[37];

    uuid_generate(uuid);
    uuid_unparse(uuid, uuidStr);

    return string(uuidStr);
}

vector<string>& PlayerUtil::playerPointersToIds(vector<shared_ptr<Player>>& players) {
    vector<string> ids;
    for (const auto& player : players) ids.push_back(player->getId());
    return ids;
}