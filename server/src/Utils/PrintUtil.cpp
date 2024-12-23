#include "../include/Utils/PrintUtil.h"
#include "../include/Utils/GameUtil.h"

void PrintUtil::printPlayers(GameData& gameData) {
    cout << "(*) Displaying Players in Game Data." << '\n';
    int num = 1;
    for (auto& player : gameData.getPlayers()) {
        cout    << "    "
                << "name: " << player->getName() << " | "
                << "id: " << player->getId() << " | "
                << "chips: " << player->getCurChips() << endl;
    }
    cout << '\n';
}