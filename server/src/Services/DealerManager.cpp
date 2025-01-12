#include "../../include/Services/DealerManager.h"

DealerManager::DealerManager(GameData& gameData) : gameData(gameData), deck() {}

void DealerManager::dealGamePlayers() {
    auto players = gameData.getPlayers();

    for (int i = 0; i < 2; i++) {
        for (auto& player : players) {
            Card& card = deck.dealCard();
            player->addHoleCard(card);
            cout << "   " << player->getName() << " has been dealt " << card.toString() << '\n';
        }
    }

    cout << endl;
}

void DealerManager::dealBoard(int num) {
    deck.burnCard();
    cout << "   Card burned..." << endl;

    for (int i = 0; i < num; ++i) {
        Card& communityCard = deck.dealCard();
        gameData.dealCommunityCard(communityCard);
        cout << "   " << communityCard.toString() << " has been dealt to the board!\n";
    }
    cout << endl;
}

void DealerManager::resetDeck() {
    deck.resetDeck();
}

void DealerManager::clearBoard() {
    gameData.clearBoard();
}

void DealerManager::clearPlayerHands() {
    GameUtil::clearPlayerHands(gameData);
}

const vector<Card>& DealerManager::getBoardCards() const { 
    return gameData.getBoardCards();
}

const Board& DealerManager::getBoard() const {
    return gameData.getBoard();
}

const Deck& DealerManager::getDeck() const {
    return deck;
}

int DealerManager::getBoardSize() const {
    return GameUtil::getBoardSize(gameData);
}

int DealerManager::getDeckSize() const {
    return deck.getDeckSize();
}