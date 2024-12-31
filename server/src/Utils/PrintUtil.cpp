#include "../../include/Utils/PrintUtil.h"

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
    if (gameData.getBoardCards().size() > 0) {
        cout << "(*) Displaying the board\n";
        cout << "    " << printVectorCards(gameData.getBoardCards()) << "\n"; 
    }

    cout << "(*) Displaying player's hole cards\n";
    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        cout    << "    "
                << player->getName() << ": "
                << printVectorCards(player->getHand()) << endl;
    }
    cout << endl;
}


void PrintUtil::printPlayers(GameData& gameData) {
    cout << "(*) Displaying Players:" << '\n';

    auto players = gameData.getPlayers();
    for (const auto& player : players) {
        cout    << "    "
                << "name: " << player->getName() << " | "
                << "chips: " << player->getCurChips() << " | "
                << "recent bet: " << player->getRecentBet() << " | "
                << "initial chips: " << player->getInitialChips() << " | "
                << "status: " << playerStatusToString(player->getPlayerStatus()) << " | "
                << "position: " << positionToString(player->getPosition()) << '\n';
    }

    if (gameData.getSmallBlindPlayer() != nullptr)
        cout << "    SB: " << GameUtil::getPlayerNameFromId(gameData, gameData.getSmallBlindPlayer()->getId()) << '\n';
    if (gameData.getBigBlindPlayer() != nullptr)
        cout << "    BB: " << GameUtil::getPlayerNameFromId(gameData, gameData.getBigBlindPlayer()->getId()) << '\n';
    if (gameData.getButtonPlayer() != nullptr)
        cout << "    Button: " << GameUtil::getPlayerNameFromId(gameData, gameData.getButtonPlayer()->getId()) << endl;
}

void PrintUtil::printPots(GameData& gameData) {
    cout << "(*) Displaying Pots: " << '\n';

    if (GameUtil::getNumPots(gameData) == 0) {
        cout    << "   "
                << "No pots to display\n" << endl;
        return;
    }

    auto pots = gameData.getPots();
    for (auto& pot : pots) {
        cout    << "    "
                << "Chips in Pot: " << pot->getChips() << " | "
                << "Eligible Players: "
                << printVectorString(GameUtil::getNamesFromIds(gameData, pot->getContributorIds())) << endl;
    }

    cout << endl;
}

void PrintUtil::printPossibleActionsForCurPlayer(GameData& gameData) {
    auto id = gameData.getCurPlayer()->getId();
    auto name = gameData.getCurPlayer()->getName();
    auto toAct = gameData.getCurPlayer();
    auto possibleActions = gameData.getPossibleActions();

    cout << "   (*) " << name << " has options: \n";
    for (const auto& action : possibleActions) {
        cout    << "        "
                << actionTypeToString(action->getActionType());

        if (action->getSecondaryAmount() != 0) {
            cout << " [" << action->getPrimaryAmount() << ", " << action->getSecondaryAmount() << "]";
        }
        else if (action->getPrimaryAmount() != 0) {
            cout << " " << action->getPrimaryAmount();
        }
        cout << "\n";
    }
    cout << endl;
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

string PrintUtil::streetToString(Street& street) {
    switch (street) {
        case Street::PRE_FLOP: return "Pre Flop";
        case Street::FLOP: return "Flop";
        case Street::TURN: return "Turn";
        case Street::RIVER: return "River";
        default: return "Unknown Street";
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