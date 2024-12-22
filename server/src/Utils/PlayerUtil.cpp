#include "../include/Utils/PlayerUtil.h"

string generateUUID() {
    uuid_t uuid;
    char uuidStr[37];

    uuid_generate(uuid);
    uuid_unparse(uuid, uuidStr);

    return string(uuidStr);
}