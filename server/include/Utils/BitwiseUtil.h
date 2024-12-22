#ifndef BITWISE_UTIL
#define BITWISE_UTIL

#include "../Shared/Enums.h"
#include <string>

using Suit = Enums::Suit;
using Value = Enums::Value;

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
};

#endif