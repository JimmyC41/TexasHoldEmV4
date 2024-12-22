#include "../../include/Entities/Board.h"

Board::Board() {}

void Board::addCommunityCard(const Card& card) { communityCards.push_back(card); }

void Board::resetBoard() { communityCards.clear(); }

const vector<Card>& Board::getCommunityCards() const { return communityCards; }

int Board::getBoardSize() const { return communityCards.size(); }