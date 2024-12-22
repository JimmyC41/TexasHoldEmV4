#include "../../include/Services/DealerManager.h"

DealerManager::DealerManager(GameData& gameData, Deck& deck, Board& board) : gameData(gameData), deck(deck), board(board) {}

DealerManager DealerManager::createDealerManager(GameData& gameData, Deck& deck, Board& board) { 
    return DealerManager(gameData, deck, board); 
}

void DealerManager::dealGamePlayers() {
    // Start dealing from the first player AFTER the Big Blind
    for (int i = 0; i < 2; i++) {
        for (auto& player : gameData.getPreFlopOrderPlayers()) {
            Card& card = deck.dealCard();
            player->addHoleCard(card);
            cout << "   " << player->getName() << " has been dealt " << card.toString() << endl;
        }
    }
}

void DealerManager::resetDeck() { deck.resetDeck(); }

void DealerManager::resetBoard() { board.resetBoard(); }

void DealerManager::dealBoard(int num) {
    deck.burnCard();
    cout << "   Card burned..." << endl;

    for (int i = 0; i < num; ++i) {
        Card& communityCard = deck.dealCard();
        board.addCommunityCard(communityCard);
        cout << "   " << communityCard.toString() << " has been dealt to the board!" << endl;
    }
}

Board& DealerManager::getBoard() const { return board; }

int DealerManager::getBoardSize() const { return board.getBoardSize(); }

int DealerManager::getDeckSize() const { return deck.getDeckSize(); }