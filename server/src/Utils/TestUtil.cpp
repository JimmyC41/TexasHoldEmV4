#include "../../include/Utils/TestUtil.h"
#include "../../include/Entities/Board.h"

void TestUtil::manualSetStreet(GameData& GameData, Street newStreet) {
    GameData.setCurStreet(newStreet);
}

void TestUtil::manualClearActionTimeline(GameData& gameData) {
    gameData.clearActionTimeline();
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