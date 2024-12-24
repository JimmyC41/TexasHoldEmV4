#include "../include/Utils/HandRankUtil.h"

void HandRankUtil::computeBitwiseForHand(HandInfo& handInfo) {
    handInfo.bitwise = BitwiseUtil::computeBitwiseHand(handInfo.hand);
}

void HandRankUtil::sortHand(HandInfo& handInfo) {
    sort(handInfo.hand.begin(), handInfo.hand.end(),
        [](const Card& a, const Card& b) {
            return a.getValue() > b.getValue();
        });
}

void HandRankUtil::evaluateHandInfo(HandInfo& hand) {
    if (hand.handSize < MIN_HAND_SIZE) {
        hand.category = HandCategory::NONE;
        hand.bestFiveCards = hand.hand;
        return;
    }
    else if (isRoyalFlush(hand)) return;
    else if (isStraightFlush(hand)) return;
    else if (isNOfAKind(hand, 4)) return;
    else if (isFullHouse(hand)) return;
    else if (isFlush(hand)) return;
    else if (isStraight(hand)) return;
    else if (isNOfAKind(hand, 3)) return;
    else if (isTwoPair(hand)) return;
    else if (isNOfAKind(hand, 2)) return;
    else if (isHighCard(hand)) return;
}

bool HandRankUtil::isRoyalFlush(HandInfo& hand) {
    for (int suit = static_cast<int>(Suit::HEARTS); suit <= static_cast<int>(Suit::SPADES); ++suit) {
        uint64_t suitMask = BitwiseUtil::getSuitMask(hand.bitwise, static_cast<Suit>(suit));
        if ((suitMask & BITMASK_ACE_STRAIGHT) == BITMASK_ACE_STRAIGHT) {
            hand.category = HandCategory::ROYAL_FLUSH;
            findStraight(hand, Value::ACE, true, static_cast<Suit>(suit));
            return true;
        }
    }
    return false;
}

bool HandRankUtil::isStraightFlush(HandInfo& hand) {
    for (int suit = static_cast<int>(Suit::HEARTS); suit <= static_cast<int>(Suit::SPADES); ++suit) {
        uint64_t suitMask = BitwiseUtil::getSuitMask(hand.bitwise, static_cast<Suit>(suit));
        for (const uint64_t mask : straightMasks) {
            if ((suitMask & mask) == mask) {
                hand.category = HandCategory::STRAIGHT_FLUSH;
                findStraight(hand, BitwiseUtil::straightMaskToHighCard(mask), true, static_cast<Suit>(suit));
                return true;
            }
        }
    }
    return false;
}

bool HandRankUtil::isFullHouse(HandInfo& hand) {
    Value trips = static_cast<Value>(-1);
    Value pair = static_cast<Value>(-1);

    for (int value = static_cast<int>(Value::TWO); value <= static_cast<int>(Value::ACE); value++) {
        if (BitwiseUtil::countBitsForValue(hand.bitwise, static_cast<Value>(value)) == 3) trips = static_cast<Value>(value);
        else if (BitwiseUtil::countBitsForValue(hand.bitwise, static_cast<Value>(value)) == 2) pair = static_cast<Value>(value);
    }

    if (trips != static_cast<Value>(-1) && pair != static_cast<Value>(-1)) {
        hand.category = HandCategory::FULL_HOUSE;
        findFullHouse(hand, trips, pair);
        return true;
    } else {
        return false;
    }
}

bool HandRankUtil::isFlush(HandInfo& hand) {
    for (int suit = static_cast<int>(Suit::HEARTS); suit <= static_cast<int>(Suit::SPADES); ++suit) {
        uint64_t suitMask = BitwiseUtil::getSuitMask(hand.bitwise, static_cast<Suit>(suit));
        if (BitwiseUtil::countSetBits(suitMask) >= MIN_HAND_SIZE) {
            hand.category = HandCategory::FLUSH;
            findFlush(hand, static_cast<Suit>(suit));
            return true;
        }
    }
    return false;
}
bool HandRankUtil::isStraight(HandInfo& hand) {
    uint64_t handNoSuits = BitwiseUtil::getAllSuitsMask(hand.bitwise);
    for (const uint64_t mask : straightMasks) {
        if ((handNoSuits & mask) == mask) {
            hand.category = HandCategory::STRAIGHT;
            findStraight(hand, BitwiseUtil::straightMaskToHighCard(mask), false, Suit::HEARTS);
            return true;
        }
    }
    return false;
}

bool HandRankUtil::isNOfAKind(HandInfo& hand, int n) {
    for (int value = static_cast<int>(Value::TWO); value <= static_cast<int>(Value::ACE); value++) {
        if (BitwiseUtil::countBitsForValue(hand.bitwise, static_cast<Value>(value)) == n) {
            switch (n) {
                case 2:
                    hand.category = HandCategory::ONE_PAIR;
                    findOnePair(hand, static_cast<Value>(value));
                    break;
                case 3:
                    hand.category = HandCategory::THREE_OF_A_KIND;
                    findThreeOfAKind(hand, static_cast<Value>(value));
                    break;
                case 4:
                    hand.category = HandCategory::FOUR_OF_A_KIND;
                    findFourOfAKind(hand, static_cast<Value>(value));
                    break;
            }
            return true;
        }
    }
    return false;
}


bool HandRankUtil::isTwoPair(HandInfo& hand) {
    Value pairOne = static_cast<Value>(-1);
    Value pairTwo = static_cast<Value>(-1);

    for (int value = static_cast<int>(Value::TWO); value <= static_cast<int>(Value::ACE); value++) {
        if (BitwiseUtil::countBitsForValue(hand.bitwise, static_cast<Value>(value)) == 2) {
            if (pairOne == static_cast<Value>(-1)) pairOne = static_cast<Value>(value);
            else pairTwo = static_cast<Value>(value);
        }
    }
    
    if (pairOne != static_cast<Value>(-1) && pairTwo != static_cast<Value>(-1)) {
        hand.category = HandCategory::TWO_PAIR;
        findTwoPair(hand, pairOne, pairTwo);
        return true;
    } else {
        return false;
    }
}


bool HandRankUtil::isHighCard(HandInfo& hand) {
    hand.category = HandCategory::HIGH_CARD;
    findHighCard(hand);
    return true;
}

void HandRankUtil::findStraight(HandInfo& hand, Value highCard, bool isFlush, Suit flushSuit) {
    bool isFiveHighStraight = false;

    // Start from the high card of the straight and move to the end
    Value curVal = highCard;
    Value endVal = static_cast<Value>(static_cast<int>(highCard) - 4);

    // For the 5-high straight, add the {5, 4, 3, 2} part of the straight, then the A
    if (highCard == Value::FIVE) {
        isFiveHighStraight = true;
        endVal = Value::TWO;
    }

    // Iterate through the hand and add the straight cards in decreasing order
    for (const Card& card : hand.hand) {
        if ((!isFlush && card.getValue() == static_cast<Value>(curVal)) ||
            (isFlush && card.getValue() == static_cast<Value>(curVal) && card.getSuit() == flushSuit)) {
            
            hand.bestFiveCards.push_back(card);

            // When we find the last card of the straight, exit early
            if (curVal == endVal) break;

            // Decrement the current value we are looking for
            curVal = static_cast<Value>(static_cast<int>(curVal) - 1);
        }
    }

    // Edge case for the 5-high straight where we need to find the A and append it to the end
    if (isFiveHighStraight) {
        for (const Card& card : hand.hand) {
            if ((!isFlush && card.getValue() == Value::ACE) ||
                (isFlush && card.getValue() == Value::ACE && card.getSuit() == flushSuit)) {
                    hand.bestFiveCards.push_back(card);
                    break;
                }
        }
    }
}

void HandRankUtil::findFourOfAKind(HandInfo& hand, Value quads) {
    // First, find the four of a kind
    for (const Card& card : hand.hand) {
        if (card.getValue() == quads) hand.bestFiveCards.push_back(card);
    }

    // Then, find the high card kicker
    for (const Card& card : hand.hand) {
        if (card.getValue() != quads) {
            hand.bestFiveCards.push_back(card);
            break;
        }
    }
}

void HandRankUtil::findFullHouse(HandInfo& hand, Value trips, Value pair) {
    // First, find the three of a kind
    for (const Card& card : hand.hand) {
        if (card.getValue() == trips) hand.bestFiveCards.push_back(card);
    }

    // Then, find the pair
    for (const Card& card : hand.hand) {
        if (card.getValue() == pair) hand.bestFiveCards.push_back(card);
    }
}

void HandRankUtil::findFlush(HandInfo& hand, Suit suit) {
    // Iterate through the hand and add the first 5 cards
    for (const Card& card : hand.hand) {
        if (card.getSuit() == suit) hand.bestFiveCards.push_back(card);
        if (hand.bestFiveCards.size() == 5) break;
    }
}

void HandRankUtil::findThreeOfAKind(HandInfo& hand, Value trips) {
    // First, find the three of a kind
    for (const Card& card : hand.hand) {
        if (card.getValue() == trips) hand.bestFiveCards.push_back(card);
    }

    // Then, add the high card kickers
    int numKickers = 0;
    for (const Card& card : hand.hand) {
        if (card.getValue() != trips) {
            hand.bestFiveCards.push_back(card);
            numKickers++;
            if (numKickers == 2) break;
        }
    }
}

void HandRankUtil::findTwoPair(HandInfo& hand, Value pairOne, Value pairTwo) {
    // First, find pairTwo
    for (const Card& card : hand.hand) {
        if (card.getValue() == pairTwo) hand.bestFiveCards.push_back(card);
    }

    // Then, find pairOne
    for (const Card& card : hand.hand) {
        if (card.getValue() == pairOne) hand.bestFiveCards.push_back(card);
    }

    // Then, add the high card kicker
    for (const Card& card : hand.hand) {
        if (card.getValue() != pairOne && card.getValue() != pairTwo) {
            hand.bestFiveCards.push_back(card);
            break;
        }
    }
}

void HandRankUtil::findOnePair(HandInfo& hand, Value pair) {
    // First, find the pair
    for (const Card& card : hand.hand) {
        if (card.getValue() == pair) hand.bestFiveCards.push_back(card);
    }

    // Then, add the high card kickers
    int numKickers = 0;
    for (const Card& card : hand.hand) {
        if (card.getValue() != pair) {
            hand.bestFiveCards.push_back(card);
            numKickers++;
            if (numKickers == 3) break;
        }
    }
}

void HandRankUtil::findHighCard(HandInfo& hand) {
    // Add the first 5 high cards from the hand
    int numCards = 0;
    for (const Card& card : hand.hand) {
        hand.bestFiveCards.push_back(card);
        numCards++;
        if (numCards == 5) break;
    }
}