#include "../../include/Utils/CardUtil.h"

Value CardUtil::charToValue(const char& valueChar) {
    Value value;
    switch (valueChar) {
        case '2': value = Value::TWO; break;
        case '3': value = Value::THREE; break;
        case '4': value = Value::FOUR; break;
        case '5': value = Value::FIVE; break;
        case '6': value = Value::SIX; break;
        case '7': value = Value::SEVEN; break;
        case '8': value = Value::EIGHT; break;
        case '9': value = Value::NINE; break;
        case 'T': value = Value::TEN; break;
        case 'J': value = Value::JACK; break;
        case 'Q': value = Value::QUEEN; break;
        case 'K': value = Value::KING; break;
        case 'A': value = Value::ACE; break;
        default: value = Value::TWO; break;
    }
    return value;
}

Suit CardUtil::charToSuit(const char& suitChar) { 
    Suit suit;
    switch (suitChar) {
        case 'h': suit = Suit::HEARTS; break;
        case 'd': suit = Suit::DIAMONDS; break;
        case 'c': suit = Suit::CLUBS; break;
        case 's': suit = Suit::SPADES; break;
        default: suit = Suit::HEARTS; break;
    }
    return suit;
}