#ifndef CARD_H
#define CARD_H

#include "../Shared/Enums.h"
#include "../Utils/BitwiseUtil.h"
#include <stdexcept>
#include <string>

using namespace std;
using Suit = Enums::Suit;
using Value = Enums::Value;

class Card {
private:
    Suit suit;
    Value value;
    uint64_t bitwise;

public:
    Card();
    explicit Card(Suit suit, Value value);
    
    Suit getSuit() const;
    Value getValue() const;
    uint64_t getBitwise() const;
    
    bool operator==(const Card& other) const;
    bool operator<(const Card& other) const;
    string toString() const;
};

#endif