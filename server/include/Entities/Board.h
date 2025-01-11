#ifndef BOARD_H
#define BOARD_H

#include "Card.h"
#include <vector>
#include <string>
using namespace std;

class Board {
private:
    vector<Card> communityCards;
public:
    Board();
    void addCommunityCard(const Card& card);
    void resetBoard();
    const vector<Card>& getCommunityCards() const;
    int getBoardSize() const;
};

#endif