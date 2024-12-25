#include "../include/Utils/PrintUtil.h"
#include "../include/Utils/GameUtil.h"

void PrintUtil::printActionTimeline(GameData& gameData) {
    cout << "(*) Displaying the Action Timeline." << '\n';
    for (auto& action : gameData.getActionTimeline()) {
        cout    << "   "
                << "player: " << GameUtil::getPlayerNameFromId(gameData, action->getPlayerId()) << " | "
                << "type: " << actionTypeToString(action->getActionType()) << " | "
                << "amount: " << action->getAmount() << endl;
    }

    cout    << "(*) Active Action Type is: " 
            << actionTypeToString(GameUtil::getActiveActionType(gameData)) << endl;
}

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

string PrintUtil::printVectorCards(const vector<Card>& cards) {
    string aggregate { "" };
    for (const auto& card : cards) {
        aggregate += card.toString();
        aggregate += ", ";
    }
    aggregate.resize(aggregate.size() - 2);
    return aggregate;
}

string PrintUtil::positionToString(Position position) {
    switch (position) {
        case Position::LOBBY: return "In Lobby";
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

string PrintUtil::categoryToString(HandCategory category) {
    switch(category) {
        case HandCategory::NONE: return "No Hand Category";
        case HandCategory::ONE_PAIR: return "One Pair";
        case HandCategory::TWO_PAIR: return "Two Pair";
        case HandCategory::THREE_OF_A_KIND: return "Three of a Kind";
        case HandCategory::STRAIGHT: return "Straight";
        case HandCategory::FLUSH: return "Flush";
        case HandCategory::FULL_HOUSE: return "Full House";
        case HandCategory::FOUR_OF_A_KIND: return "Four of a Kind";
        case HandCategory::STRAIGHT_FLUSH: return "Straight Flush";
        case HandCategory::ROYAL_FLUSH: return "Royal Flush";
        default: return "Unknown Hand Category";
    }
}

string PrintUtil::actionTypeToString(ActionType type) {
    switch(type) {
        case ActionType::NONE: return "None";
        case ActionType::POST_BIG: return "Big";
        case ActionType::POST_SMALL: return "Small";
        case ActionType::CHECK: return "Check";
        case ActionType::BET: return "Bet";
        case ActionType::CALL: return "Call";
        case ActionType::RAISE: return "Raise";
        case ActionType::FOLD: return "Fold";
        case ActionType::ALL_IN_BET: return "All In Bet";
        case ActionType::ALL_IN_CALL: return "All In Call";
        default: return "Unknown Action Type";
    }
}