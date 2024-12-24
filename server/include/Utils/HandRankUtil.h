#ifndef RANK_HAND_UTIL_H
#define RANK_HAND_UTIL_H

#include "BitwiseUtil.h"
#include "../Shared/Types.h"
#include "../Shared/Enums.h"
#include "../Entities/Card.h"
#include "../Utils/PrintUtil.h"

#include <iostream>
#include <algorithm>

using Value = Enums::Value;
using Suit = Enums::Suit;
using HandCategory = Enums::HandCategory;
using HandInfo = Types::HandInfo;
using namespace std;

constexpr int MIN_HAND_SIZE = 5;

class HandRankUtil {
public:
    // Gets the bitwise representation of the hand
    static void computeBitwiseForHand(HandInfo& handInfo);

    // Sorts in decreasing order the hand in the HandInfo reference
    static void sortHand(HandInfo& handInfo);

    // Evaluates handCategory and bestFiveCards for a given player's hand
    static void evaluateHandInfo(HandInfo& hand);

    // Helper method to evaluate hand info using bitwise operations
    static bool isRoyalFlush(HandInfo& hand);
    static bool isStraightFlush(HandInfo& hand);
    static bool isFullHouse(HandInfo& hand);
    static bool isFlush(HandInfo& hand);
    static bool isStraight(HandInfo& hand);
    static bool isNOfAKind(HandInfo& hand, int n);
    static bool isTwoPair(HandInfo& hand);
    static bool isHighCard(HandInfo& hand);

    // Helper method to find the best 5 card combination
    static void findStraight(HandInfo& hand, Value highCard, bool isFlush, Suit flushSuit);
    static void findFourOfAKind(HandInfo& hand, Value quads);
    static void findFullHouse(HandInfo& hand, Value trips, Value pair);
    static void findFlush(HandInfo& hand, Suit suit);
    static void findThreeOfAKind(HandInfo& hand, Value trips);
    static void findTwoPair(HandInfo& hand, Value pairOne, Value pairTwo);
    static void findOnePair(HandInfo& hand, Value pair);
    static void findHighCard(HandInfo& hand);
};

#endif
