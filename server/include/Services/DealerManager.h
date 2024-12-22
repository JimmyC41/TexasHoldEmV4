#ifndef DEALER_MANAGER_H
#define DEALER_MANAGER_H

#include "../Shared/GameData.h"
#include "../Entities/Deck.h"
#include "../Entities/Player.h"
#include "../Entities/Board.h"
#include "../Utils/PlayerUtil.h"
#include "../Utils/GameUtil.h"
#include <vector>

using namespace std;

class DealerManager {
private:
    GameData& gameData;
    Deck& deck;
    Board& board;

    explicit DealerManager(GameData& gameData, Deck& deck, Board& board);
    DealerManager(const DealerManager&) = delete;             // Delete copy constructor 
    DealerManager& operator=(const DealerManager&) = delete;  // Delete copy assignments

public:
    static DealerManager createDealerManager(GameData& gameData, Deck& deck, Board& board);

    void dealGamePlayers();     // Deals 2 hole cards for each player in  Game Data, starting from the next to act after the BB
    void dealBoard(int num);    // Burns 1 card, then deals 'num' number of community cards to the board

    void resetDeck();
    void resetHoleHands();
    void resetBoard();

    // Getter Methods
    Board& getBoard() const;
    int getBoardSize() const;
    int getDeckSize() const;
};

#endif // DEALER_H
