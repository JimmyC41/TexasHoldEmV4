#ifndef BITWISE_UTIL
#define BITWISE_UTIL

#include "../Shared/Enums.h"
#include "../Entities/Card.h"
#include <string>
#include <vector>

using Suit = Enums::Suit;
using Value = Enums::Value;
using namespace std;

class Card;

constexpr int NUM_VALUES = 13;
constexpr uint64_t BITMASK_13_BITS = 0x1FFF;
constexpr uint64_t BITMASK_ACE_STRAIGHT = 0x1F00;

constexpr uint64_t straightMasks[] = {
    0x1F00, // A-high
    0xF80,  // K-high
    0x7C0,  // Q-high
    0x3E0,  // J-high
    0x1F0,  // 10-high
    0xF8,   // 9-high
    0x7C,   // 8-high
    0x3E,   // 7-high
    0x1F,   // 6-high
    0x100F  // 5-high
};

class BitwiseUtil {
public:
    static uint64_t computeBitwise(Suit suit, Value value);

    static uint64_t computeBitwiseHand(const vector<Card>& hand);

    // Aggregates values regardless of suit into a 13-bit
    static uint64_t getAllSuitsMask(uint64_t hand);

    // Selects for the 13-bit component of specified suit
    static uint64_t getSuitMask(uint64_t hand, Suit suit);

    // Counts occurences of a given value in the hand
    static int countBitsForValue(uint64_t hand, Value value);
    
    static int countSetBits(uint64_t mask);
    static Value straightMaskToHighCard(uint64_t straightMask);
};

#endif