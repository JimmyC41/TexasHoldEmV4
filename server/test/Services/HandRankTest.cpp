#include <gtest/gtest.h>
#include "../../include/Services/DealerManager.h"
#include "../../include/Services/HandRankManager.h"
#include "../../include/Utils/TestUtil.h"
#include "../../include/Utils/GameUtil.h"

class DealTest : public ::testing::Test {
protected:
    Deck deck;
    Board board;
    DealerManager dealer;
    GameData game
};