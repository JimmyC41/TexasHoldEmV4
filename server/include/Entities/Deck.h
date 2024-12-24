#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <iostream>
#include <array>
using namespace std;

const int DECK_SIZE = 52;

class Deck {
private:
    array<Card, DECK_SIZE> deck;
    size_t deckIndex;
    bool isShuffled;
    void shuffleDeck();
public:
    Deck();

    Card& dealCard();
    void burnCard();
    void resetDeck();
    size_t getDealtCardCount() const;

    // Test Functions
    array<Card, DECK_SIZE> getArrayOfDeckCards() const;
    size_t getDeckSize() const;
};

#endif // DECK_H