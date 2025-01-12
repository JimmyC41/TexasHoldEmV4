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
    Deck deck;
public:
    DealerManager(GameData& gameData);

    /* Deals 2 hole cards to each player, starting from after the BB */
    void dealGamePlayers();

    /* Burns 1 card, then deals 'num' number of community cards to the board */
    void dealBoard(int num);

    void resetDeck();
    void clearPlayerHands();
    void clearBoard();

    // Getter Methods for the Board
    const vector<Card>& getBoardCards() const;
    const Board& getBoard() const;
    const Deck& getDeck() const;
    int getBoardSize() const;
    int getDeckSize() const;
};

#endif // DEALER_H
