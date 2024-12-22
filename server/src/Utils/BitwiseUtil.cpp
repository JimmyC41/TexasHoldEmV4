#include "../include/Utils/BitwiseUtil.h"

uint64_t BitwiseUtil::computeBitwise(Suit suit, Value value) {
    int cardNum = (static_cast<int>(suit) * NUM_VALUES) + (static_cast<int>(value) - 2);
    return (1ULL << cardNum);
}