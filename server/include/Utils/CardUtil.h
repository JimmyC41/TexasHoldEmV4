#ifndef CARD_UTIL_H
#define CARD_UTIL_H

#include "../Entities/Card.h"
#include "../Shared/Enums.h"

using Value = Enums::Value;
using Suit = Enums::Suit;

class CardUtil {
public:
    static Value charToValue(const char& valueChar);
    static Suit charToSuit(const char& suitChar);
};

#endif