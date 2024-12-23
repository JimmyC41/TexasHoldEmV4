#include "../include/Utils/PrintUtil.h"
#include "../include/Utils/GameUtil.h"

void PrintUtil::printPlayers(GameData& gameData) {
    cout << "(*) Displaying Players in Game Data." << '\n';
    int num = 1;
    for (auto& player : gameData.getPlayers()) {
        cout    << "    "
                << "name: " << player->getName() << " | "
                << "id: " << player->getId() << " | "
                << "chips: " << player->getCurChips() << " | "
                << "position: " << positionToString(player->getPosition()) << endl;
    }
    cout << "Small ID: " << gameData.getSmallBlindId() << '\n';
    cout << "Dealer ID: " << gameData.getButtonId() << endl;
}

string PrintUtil::positionToString(Position position) {
    switch (position) {
        case Position::LOBBY: return "Not In Game: Lobby";
        case Position::SMALL_BLIND: return "Small Blind";
        case Position::BIG_BLIND: return "Big Blind";
        case Position::UTG: return "UTG";
        case Position::UTG_1: return "UTG + 1";
        case Position::MIDDLE: return "Middle Position";
        case Position::LOJACK: return "Lojack";
        case Position::HIJACK: return "Hijack";
        case Position::CUT_OFF: return "Cutoff";
        case Position::DEALER: return "Dealer";
        default: return "Error: Unknown Position";
    }
}