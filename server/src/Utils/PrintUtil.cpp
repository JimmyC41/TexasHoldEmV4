#include "../include/Utils/PrintUtil.h"

void PrintUtil::printActionTimeline(GameData& gameData) {
    cout << "(*) Displaying the Action Timeline." << '\n';
    for (const auto& action : gameData.getActionTimeline()) {
        cout    << "   "
                << "player: " << GameUtil::getPlayerNameFromId(gameData, action->getPlayerId()) << " | "
                << "type: " << actionTypeToString(action->getActionType()) << " | "
                << "amount: " << action->getAmount() << '\n';
    }

    cout    << "(*) Active Action Type is: " 
            << actionTypeToString(GameUtil::getActiveActionType(gameData)) << endl;
}

void PrintUtil::printAllCards(GameData& gameData) {
    cout << "(*) Displaying the Board: " << '\n';
    auto communityCards = gameData.getBoardCards();
    printVectorCards(communityCards);

    cout << "(*) Displaying player's hole cards" << '\n';
    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        cout    << "    "
                << player->getName() << ": "
                << printVectorCards(player->getHand()) << endl;
    }
}

void PrintUtil::printPlayers(GameData& gameData) {
    cout << "(*) Displaying Players:" << '\n';

    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        cout    << "    "
                << "name: " << player->getName() << " | "
                << "id: " << player->getId() << " | "
                << "chips: " << player->getCurChips() << " | "
                << "recent bet: " << player->getRecentBet() << " | "
                << "position: " << positionToString(player->getPosition()) << '\n';
    }

    cout << "Small Blind: " << GameUtil::getPlayerNameFromId(gameData, gameData.getSmallBlindId()) << '\n';
    cout << "Big Blind: " << GameUtil::getPlayerNameFromId(gameData, gameData.getBigBlindId()) << '\n';
    cout << "Dealer: " << GameUtil::getPlayerNameFromId(gameData, gameData.getButtonId()) << endl;
}

void PrintUtil::printPots(GameData& gameData) {
    cout << "(*) Displaying Pots: " << '\n';

    if (GameUtil::getNumPots(gameData) == 0) {
        cout    << "   "
                << "No pots to display." << endl;
        return;
    }

    auto pots = gameData.getPots();
    for (auto& pot : pots) {
        cout    << "    "
                << "Chips in Pot: " << pot->getChips() << " | "
                << "Eligible Players: "
                << printVectorString(GameUtil::getNamesFromIds(gameData, pot->getEligibleIds())) << endl;
    }
}

void PrintUtil::printPossibleActionsForCurPlayer(GameData& gameData) {
    cout << "(*) Displaying Possible Actions: " << '\n';

    auto id = gameData.getCurPlayerId();
    auto name = GameUtil::getPlayerNameFromId(gameData, id);
    auto toAct = GameUtil::getPlayer(gameData, id);
    auto possibleActions = gameData.getPossibleActions();

    cout << "   " << name << " has options: ";
    for (const auto& action : possibleActions) { 
        cout << actionTypeToString(action->getActionType());

        if (action->getSecondaryAmount() != 0) {
            cout << " | Range: [" << action->getPrimaryAmount() << ", " << action->getSecondaryAmount() << "]" << '\n';
        } else {
            cout << " | Amount: " << action->getPrimaryAmount() << '\n';
        }
    }
}

void PrintUtil::printClientAction(pair<ActionType, size_t> action) {
    auto type = actionTypeToString(action.first);
    auto amount = action.second;
    cout << "Client action is: " << type << " " << amount << endl;
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
        case ActionType::ALL_IN_RAISE: return "All In Raise";
        default: return "Unknown Action Type";
    }
}

string PrintUtil::playerStatusToString(PlayerStatus status) {
    switch(status) {
        case PlayerStatus::WAITING: return "Waiting"; 
        case PlayerStatus::IN_HAND: return "In Hand";
        case PlayerStatus::FOLDED: return "Folded";
        case PlayerStatus::ALL_IN_BET: return "All In Bet";
        case PlayerStatus::ALL_IN_CALL: return "All In Call";
        default: return "Unknown Player Status";
    }
}

string PrintUtil::printVectorString(const vector<string>& strings) {
    string result;
    for (size_t i = 0; i < strings.size(); ++i) {
        result += strings[i];
    }
    return result;
}

void PrintUtil::printPlayerBetsInPotManager(PlayerBetInfo& playerBetInfo) {
    cout << "Displaying playerBetInfo in PotManager" << endl;
    for (auto& [id, bet, status] : playerBetInfo) {
        cout    << "id: " << id << " | "
                << "bet: " << bet << " | "
                << "status: " << playerStatusToString(status) << endl;
    }
}