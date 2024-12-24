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

    void dealGamePlayers();     // Deals 2 hole cards for each player in  Game Data, starting from the next to act after the BB
    void dealBoard(int num);    // Burns 1 card, then deals 'num' number of community cards to the board

    void resetDeck();
    void clearPlayerHands();
    void clearBoard();

    // Getter Methods
    const vector<Card>& getBoardCards() const;
    const Board& getBoard() const;
    const Deck& getDeck() const;
    int getBoardSize() const;
    int getDeckSize() const;
};

#endif // DEALER_H
