#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include "../../include/Entities/Player.h"
#include "../../include/Entities/Board.h"
#include "../../include/Entities/Card.h"
#include "../../include/Services/DealerManager.h"
#include <string>
#include <memory>
#include <set>
using namespace std;

void createPlayersInGameData(GameData& gameData, vector<tuple<string, size_t, Position>> playersInfo);

void clearPlayerHands(GameData& gameData);

bool isCardsUnique(const vector<Card>& cards);

vector<Card> aggregateDealtCards(GameData& gameData, DealerManager& dealer);


#endif