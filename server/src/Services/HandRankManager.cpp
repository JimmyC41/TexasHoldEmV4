#include "../../include/Services/HandRankManager.h"

void HandRankManager::populateHandsInfo(GameData& gameData) {
    // For each player in the game
    auto players = gameData.getPlayers();
    for (auto& player : players) {
        // Fetch the hand and get the relevant handInfo object
        const auto& hand = player->getHand();
        HandInfo& handInfo = handsInfo[player->getId()];
        
        // Evaluate the hand in the handInfo reference
        handInfo.hand = hand;
        handInfo.handSize = hand.size();
        HandRankUtil::sortHand(handInfo);
        HandRankUtil::computeBitwiseForHand(handInfo);
        HandRankUtil::evaluateHandInfo(handInfo);

        // GameData updates
        player->setBestFiveCards(handInfo.bestFiveCards);
        player->setHandCategory(handInfo.category);
    }
}

bool HandRankManager::compareHands(const HandInfo& handA, const HandInfo& handB) {
    // Compare by hand category first (higher is stronger)
    if (handA.category != handB.category) {
        return handA.category > handB.category;
    }

    // Compare best five cards lexicographically
    for (size_t i = 0; i < handA.bestFiveCards.size(); ++i) {
        if (handA.bestFiveCards[i].getValue() != handB.bestFiveCards[i].getValue()) {
            return handA.bestFiveCards[i].getValue() > handB.bestFiveCards[i].getValue();
        }
    }
    return false;
}

void HandRankManager::evaluateRankedIds() {
    // Evaluate Hand Info for players:
    populateHandsInfo(gameData);

    // Rank players by the strength of their Hands Info
    vector<shared_ptr<Player>> rankedPlayers = gameData.getPlayers();
    sort(rankedPlayers.begin(), rankedPlayers.end(),
        [this](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
            return compareHands(handsInfo.at(a->getId()), handsInfo.at(b->getId()));
        });
    
    // Update rankedPlayerIds in GameData
    vector<string> rankedIds = PlayerUtil::playerPointersToIds(rankedPlayers);
    gameData.setRankedPlayerIds(rankedIds);
}