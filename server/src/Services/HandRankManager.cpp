#include "../../include/Services/HandRankManager.h"

void HandRankManager::populateHandsInfo(GameData& gameData) {
    // For each player in the game
    auto players = gameData.getRawPlayers();

    for (auto& player : players) {
        // Fetch the hand and get the relevant handInfo object
        const auto& hand = player->getHand();
        HandInfo& handInfo = handsInfo[player->getId()];
        
        // Evaluate the hand in the handInfo reference
        handInfo.setHand(hand);
        handInfo.setHandSize(hand.size());
        HandRankUtil::sortHand(handInfo);
        HandRankUtil::computeBitwiseForHand(handInfo);
        HandRankUtil::evaluateHandInfo(handInfo);

        // GameData updates
        player->setBestFiveCards(handInfo.getBestFiveCards());
        player->setHandCategory(handInfo.getCategory());
    }
}

bool HandRankManager::compareHands(const HandInfo& handA, const HandInfo& handB) {
    auto handACategory = handA.getCategory();
    auto handBCategory = handB.getCategory();
    auto handAFive = handA.getBestFiveCards();
    auto handBFive = handB.getBestFiveCards();

    // Compare by hand category first (higher is stronger)
    if (handACategory != handBCategory) {
        return handACategory > handBCategory;
    }

    // Compare best five cards lexicographically
    for (uint32_t i = 0; i < handA.getBestFiveCards().size(); ++i) {
        if (handAFive[i].getValue() != handBFive[i].getValue()) {
            return handAFive[i].getValue() > handBFive[i].getValue();
        }
    }
    return false;
}

void HandRankManager::evaluateRankedIds() {
    // Evaluate Hand Info for players:
    populateHandsInfo(gameData);

    // Rank players by the strength of their Hands Info
    auto sortedPlayers = gameData.getRawPlayers();
    sort
    (
        sortedPlayers.begin(),
        sortedPlayers.end(),
        [this] (const Player* a, const Player* b)
        {
            return compareHands(handsInfo.at(a->getId()), handsInfo.at(b->getId()));
        }
    );
    
    // Update rankedPlayerIds in GameData
    vector<string> rankedIds = PlayerUtil::playerPointersToIds(sortedPlayers);
    gameData.setRankedPlayerIds(rankedIds);
}