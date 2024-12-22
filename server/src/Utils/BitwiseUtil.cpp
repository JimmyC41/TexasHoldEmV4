#include "../include/Utils/BitwiseUtil.h"

uint64_t BitwiseUtil::computeBitwise(Suit suit, Value value) {
    int cardNum = (static_cast<int>(suit) * NUM_VALUES) + (static_cast<int>(value) - 2);
    return (1ULL << cardNum);
}

uint64_t BitwiseUtil::computeBitwiseHand(const vector<Card>& hand) {
    uint64_t res = 0;
    for (const auto& card : hand) {
        res |= computeBitwise(card.getSuit(), card.getValue());
    }
    return res;
}

uint64_t BitwiseUtil::getAllSuitsMask(uint64_t hand) {
    return  (hand & BITMASK_13_BITS) |
            ((hand >> 13) & BITMASK_13_BITS) |
            ((hand >> 26) & BITMASK_13_BITS) |
            ((hand >> 39) & BITMASK_13_BITS);
}

uint64_t BitwiseUtil::getSuitMask(uint64_t hand, Suit suit) {
    return (hand >> NUM_VALUES * static_cast<int>(suit)) & BITMASK_13_BITS;
}

int BitwiseUtil::countBitsForValue(uint64_t hand, Value value) {
    int valueFreq = 0;
    uint64_t valueMask = 1ULL << (static_cast<int>(value) - 2);
    for (int suit = static_cast<int>(Suit::HEARTS); suit <= static_cast<int>(Suit::SPADES); ++suit) {
        uint64_t suitMask = getSuitMask(hand, static_cast<Suit>(suit));
        if ((suitMask & valueMask) == valueMask) valueFreq++;
    }
    return valueFreq;
}

int BitwiseUtil::countSetBits(uint64_t mask) {
    int count = 0;
    while (mask) {
        mask &= (mask - 1);
        count++;
    }
    return count;
}

Value BitwiseUtil::straightMaskToHighCard(uint64_t straightMask) {
    switch (straightMask) {
        case 0x100F: return Value::FIVE;
        case 0x1F: return Value::SIX;
        case 0x3E: return Value::SEVEN;
        case 0x7C: return Value::EIGHT;
        case 0xF8: return Value::NINE;
        case 0x1F0: return Value::TEN;
        case 0x3E0: return Value::JACK;
        case 0x7C0: return Value::QUEEN;
        case 0xF80: return Value::KING;
        case 0x1F00:return Value::ACE;
        default: return Value::TWO;
    }
}