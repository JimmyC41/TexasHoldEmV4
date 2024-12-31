#include "../../include/Services/PotManager.h"

PotManager::PotManager(GameData& gameData) : 
    gameData(gameData),
    playerBets()
{}

void PotManager::populatePlayerBets() { 
    playerBets = PotUtil::getPlayerRecentBets(gameData);
    // PrintUtil::printPlayerBetsInPotManager(playerBets);
}

size_t PotManager::getMinBetInPlayerBets() {
    size_t minBet = numeric_limits<size_t>::max();
    for (auto [player, bet, status] : playerBets) { 
        if (bet == 0 || status == PlayerStatus::FOLDED) continue;
        if (bet < minBet) minBet = bet;
    }
    return minBet;
}

bool PotManager::allBetsAllocatedToPots() {
    for (auto& [player, bet, status] : playerBets) {
        // Return false if there is an outstanding recent bet
        // that has not been processed for a player that is still
        // in the hand!
        if (bet != 0 && status != PlayerStatus::FOLDED) return false;
    }
    return true;
}

void PotManager::calculatePots() {
    cout << "(+) Pot Manager: Calculating pots based on bets made for the current street.\n" << endl;
    // Fetch recent bets at the end of the Street
    populatePlayerBets();
    if (GameUtil::getNumPots(gameData) == 0) gameData.addNewPot(make_shared<Pot>());

    // Add each player's contribution to the current pot
    // Add dead money to the current pot
    // Create side pot(s) and repeat as needed
    int numFolds = 0;
    while (!allBetsAllocatedToPots()) {
        size_t minContribution = getMinBetInPlayerBets();
        for (auto& [id, bet, status] : playerBets) {
            if (bet == 0) continue;

            // Initially, chips contributed by a player that has folded is
            // counted as dead chips, before being allocated to the pot below
            if (status == PlayerStatus::FOLDED) {
                gameData.addDeadChips(bet);
                numFolds++;
                continue;
            }

            if (!GameUtil::isIdInCurPot(gameData, id)) gameData.addIdToCurPot(id);
            
            // Add current player chips to to the pot
            bet -= minContribution;
            gameData.addChipsToCurPot(minContribution);
        }

        // Add the maximum amount of dead chips to the pot
        // Each folded player can only contribute up to the
        // minimum contribution of their dead chips to the pot!
        size_t deadChipsToAdd = min((minContribution * numFolds), gameData.getDeadChips());
        gameData.addChipsToCurPot(deadChipsToAdd);
        gameData.lessDeadChips(deadChipsToAdd);

        // Create a side pot if there is are unprocessed bets from players
        // that exceed the minContribution
        if (!allBetsAllocatedToPots()) gameData.addNewPot(make_shared<Pot>());
    }

    // Clear all player's recent bets (for the next Street)
    GameUtil::resetPlayerRecentBets(gameData);
}

void PotManager::awardPots() {
    auto rankedIds = gameData.getRankedIds();
    auto pots = gameData.getPots();

    // For each pot, find the highest ranking player that is eligible
    // and increment their chip count by the amount in the pot

    // For a player to be eligible, they must have contributed to the pot
    // and still be in the hand
    for (auto& pot : pots) {
        for (auto& id : rankedIds) {
            auto player = GameUtil::getPlayer(gameData, id);
            auto status = player->getPlayerStatus();
            if (pot->isIdAContributor(id) && status != PlayerStatus::FOLDED) {
                player->addChips(pot->getChips());
                cout << "(+) Pot Manager: Awarded " << pot->getChips() << " to " << player->getName() << " chip count!\n" << endl;
                break;
            }
        }
    }

    // Since some player's chip counts may have changed, update their
    // "initialChips" attribute for the next betting street
    GameUtil::setPlayerInitialToCurChips(gameData);
    gameData.clearAllPots();
}
