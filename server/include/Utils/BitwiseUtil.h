#ifndef BITWISE_UTIL
#define BITWISE_UTIL

#include "../Shared/Enums.h"
#include <string>

using Suit = Enums::Suit;
using Value = Enums::Value;

const int NUM_VALUES = 13;

uint64_t computeBitwise(Suit suit, Value value);

#endif