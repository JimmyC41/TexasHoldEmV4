#include "../../include/Utils/TestUtil.h"
#include "../../include/Entities/Board.h"

void TestUtil::manualSetStreet(GameData& GameData, Street newStreet) {
    GameData.setCurStreet(newStreet);
}

void TestUtil::manualClearActionTimeline(GameData& gameData) {
    gameData.clearActionTimeline();
}

void TestUtil::manualClearPots(GameData& gameData) {
    gameData.clearAllPots();
}

bool TestUtil::isCardsUnique(const vector<Card>& cards) {
    set<Card> uniqueCards(cards.begin(), cards.end());
    return uniqueCards.size() == cards.size();
}

vector<Card> TestUtil::aggregateDealtCards(GameData& gameData, DealerManager& dealer) {
    vector<Card> cards;
    Board board = dealer.getBoard();

    for (auto& player : gameData.getPlayers()) {
        cards.insert(cards.end(), player->getHand().begin(), player->getHand().end());
    }
    cards.insert(cards.end(), board.getCommunityCards().begin(), board.getCommunityCards().end());

    return cards;
}

void TestUtil::dealCardsToPlayers(GameData& gameData, vector<string> idOrNames, vector<pair<Suit, Value>>& cards) {
    for (const auto& card : cards) {
        for (const auto& idOrName : idOrNames) {
            Card newCard = Card(card.first, card.second);
            auto player = GameUtil::getPlayer(gameData, idOrName);
            player->addHoleCard(newCard);
        }
    }
}

void TestUtil::manualAddPlayers(GameData& gameData, PlayerManager& playerManager, PositionManager& positionManager,
    vector<pair<string, size_t>> players) {

        playerManager.addNewPlayers(players);
        positionManager.allocatePositions();
        PrintUtil::printPlayers(gameData);
}

void TestUtil::manualSetPossibleAction(GameData& gameData, vector<shared_ptr<PossibleAction>> possible) {
    gameData.setPossibleActions(possible);
}

vector<Card> TestUtil::strToVectorOfCards(const string& stringOfCards) {
    vector<Card> hand;
    for (size_t i = 0; i < stringOfCards.size(); i += 2) {
        Value value = CardUtil::charToValue(stringOfCards[i]);
        Suit suit = CardUtil::charToSuit(stringOfCards[i + 1]);
        hand.emplace_back(Card(suit, value));
    }
    return hand;
}

vector<tuple<string, ActionType, size_t>> TestUtil::getActionTimelineVector(GameData& gameData) {
    vector<tuple<string, ActionType, size_t>> result;
    auto actionTimeline = gameData.getActionTimeline();
    for (const auto& action : actionTimeline) {
        auto name = GameUtil::getPlayerNameFromId(gameData, action->getPlayerId());
        result.push_back({name, action->getActionType(), action->getAmount()});
    }
    return result;
}

vector<tuple<ActionType, PossibleAmounts>> TestUtil::getPossibleActionsVector(GameData& gameData) {
    vector<tuple<ActionType, PossibleAmounts>> result;

    auto possibleActions = gameData.getPossibleActions();
    for (const auto& action : possibleActions) {
        auto type = action->getActionType();
        switch(type) {
            case ActionType::CHECK:
            case ActionType::FOLD:
                result.push_back({type, monostate{}}); break;
            case ActionType::ALL_IN_BET:
            case ActionType::ALL_IN_CALL:
            case ActionType::ALL_IN_RAISE:
            case ActionType::CALL:
                result.push_back({type, action->getPrimaryAmount()});
                break;
            case ActionType::BET:
            case ActionType::RAISE:
                result.push_back({type, make_tuple
                                            (action->getPrimaryAmount(),
                                            action->getSecondaryAmount())});
                break;
            default:
                break;
        }
    }
    return result;
}

vector<pair<size_t, vector<string>>> TestUtil::getPotsChipsAndNames(GameData& gameData) {
    vector<pair<size_t, vector<string>>> chipsInPots;
    auto pots = gameData.getPots();
    for (auto& pot : pots) {
        chipsInPots.push_back({
            pot->getChips(), 
            GameUtil::getNamesFromIds(gameData, pot->getContributorIds())
        });
    }
    return chipsInPots;
}

// Deals players, calls hand evaluator to rank players and returns the ranked names
vector<string> TestUtil::evaluateHandsAndGetRankedNames(GameData& gameData, HandRankManager& handRankManager, vector<pair<Suit, Value>> cards) {
    // Create a vector of player names e.g. {"P1", "P2", "P3"}
    vector<string> playerNames;
    int numPlayers = (cards.size() - 5) / 2;
    for (int i = 1; i <= numPlayers; ++i) playerNames.push_back("P" + to_string(i));
        
    // Deal the board cards to each player
    vector<pair<Suit, Value>> board = TestUtil::getSubset(cards, 0, 5);
    TestUtil::dealCardsToPlayers(gameData, playerNames, board);

    // Deal each player's hole cards
    size_t offset = 5;
    for (int i = 0; i < numPlayers; ++i) {
        vector<pair<Suit, Value>> holeCards = TestUtil::getSubset(cards, offset, offset + 2);
        TestUtil::dealCardsToPlayers(gameData, {playerNames[i]}, holeCards);
        offset += 2;
    }

    handRankManager.evaluateRankedIds();
    return GameUtil::getRankedNames(gameData);
}