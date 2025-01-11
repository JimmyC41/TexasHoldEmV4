#include "../../include/Entities/Deck.h"
#include <algorithm>
#include <random>
#include <assert.h>
using namespace std;

Deck::Deck() : deckIndex(0), isShuffled(false) {
    // Populate and shuffle the deck
    uint32_t index = 0;
    for (int suit = 0; suit < 4; ++suit) {
        for (int value = 2; value <= 14; ++value) {
            deck[index++] = Card(static_cast<Suit>(suit), static_cast<Value>(value));
        }
    }
    shuffleDeck();
}

Card& Deck::dealCard() {
    return deck[deckIndex++];
}

uint32_t Deck::getDealtCardCount() const { return deckIndex; }

void Deck::burnCard() { deckIndex++; }

void Deck::resetDeck() {
    deckIndex = 0;
    shuffleDeck();
}

void Deck::shuffleDeck() {
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
    deckIndex = 0;
    isShuffled = true;
}

uint32_t Deck::getDeckSize() const {
    return (DECK_SIZE - deckIndex);
}

array<Card, DECK_SIZE> Deck::getArrayOfDeckCards() const {
    return deck;
}