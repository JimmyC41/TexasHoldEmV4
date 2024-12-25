#include "../../include/Entities/Player.h"
#include "../../include/Utils/PlayerUtil.h"

Player::Player(string name, size_t chips) :
    name(name),
    id(PlayerUtil::generateUUID()),
    position(Position::LOBBY),
    curChips(chips),
    hand(),
    playerStatus(PlayerStatus::WAITING),
    initialChips(chips),
    recentBet(0),
    handCategory(HandCategory::NONE)
{}

// SETTER METHODS

void Player::setPosition(Position newPosition) { position = newPosition; }

void Player::addChips(size_t newChips) { curChips += newChips; }

void Player::reduceChips(size_t lostChips) { curChips -= lostChips; }

void Player:: addHoleCard(const Card& card) { hand.push_back(card); }

void Player::clearHand() { hand.clear(); }

void Player::setPlayerStatus(PlayerStatus status) { playerStatus = status; }

void Player:: setInitialChips(size_t chips) { initialChips = chips; }

void Player::setRecentBet(size_t newBet) { recentBet = newBet; }

void Player::setHandCategory(HandCategory category) { handCategory = category; }

void Player::setBestFiveCards(vector<Card>& cards) { bestFiveCards = cards; }

// GETTER METHODS

const string& Player::getName() const { return name; }

const string& Player::getId() const { return id; }

Position Player:: getPosition() const { return position; }

size_t Player::getCurChips() const { return curChips; }

const vector<Card>& Player::getHand() const { return hand; }

const vector<Card>& Player::getBestFiveCards() const { return bestFiveCards; }

PlayerStatus Player::getPlayerStatus() const { return playerStatus; }

size_t Player::getInitialChips() const { return initialChips; }

size_t Player::getRecentBet() const { return recentBet; }

HandCategory Player::getHandCategory() const { return handCategory; }