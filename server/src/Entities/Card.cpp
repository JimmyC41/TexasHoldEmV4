#include "../../include/Entities/Card.h"

Card::Card() : suit(Suit::HEARTS), value(Value::TWO), bitwise(computeBitwise(Suit::HEARTS, Value::TWO)) {}

Card::Card(Suit suit, Value value) : suit(suit), value(value), bitwise(computeBitwise(suit, value)) {}

Suit Card::getSuit() const { return suit; }

Value Card::getValue() const { return value; }

uint64_t Card::getBitwise() const { return bitwise; }

bool Card::operator<(const Card& other) const {
    if (value != other.value) return value < other.value;
    return suit < other.suit;
}

bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}

string Card::toString() const {
    std::string valueStr;
    switch (value) {
        case Value::TWO: valueStr = "2"; break;
        case Value::THREE: valueStr = "3"; break;
        case Value::FOUR: valueStr = "4"; break;
        case Value::FIVE: valueStr = "5"; break;
        case Value::SIX: valueStr = "6"; break;
        case Value::SEVEN: valueStr = "7"; break;
        case Value::EIGHT: valueStr = "8"; break;
        case Value::NINE: valueStr = "9"; break;
        case Value::TEN: valueStr = "10"; break;
        case Value::JACK: valueStr = "Jack"; break;
        case Value::QUEEN: valueStr = "Queen"; break;
        case Value::KING: valueStr = "King"; break;
        case Value::ACE: valueStr = "Ace"; break;
    }

    std::string suitStr;
    switch (suit) {
        case Suit::HEARTS: suitStr = "Hearts"; break;
        case Suit::DIAMONDS: suitStr = "Diamonds"; break;
        case Suit::CLUBS: suitStr = "Clubs"; break;
        case Suit::SPADES: suitStr = "Spades"; break;
    }

    return valueStr + " of " + suitStr;
}