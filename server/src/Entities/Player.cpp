#include "../../include/Entities/Player.h"
#include "../../include/Utils/PlayerUtil.h"

Player::Player(string name, uint32_t chips) :
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

void Player::addChips(uint32_t newChips) { curChips += newChips; }

void Player::reduceChips(uint32_t lostChips) { curChips -= lostChips; }

void Player:: addHoleCard(const Card& card) { hand.push_back(card); }

void Player::clearHand() { hand.clear(); }

void Player::setPlayerStatus(PlayerStatus status) { playerStatus = status; }

void Player:: setInitialChips(uint32_t chips) { initialChips = chips; }

void Player::setRecentBet(uint32_t newBet) { recentBet = newBet; }

void Player::setHandCategory(HandCategory category) { handCategory = category; }

void Player::setBestFiveCards(const vector<Card>& cards) { bestFiveCards = cards; }

// GETTER METHODS

const string& Player::getName() const { return name; }

const string& Player::getId() const { return id; }

Position Player:: getPosition() const { return position; }

uint32_t Player::getCurChips() const { return curChips; }

const vector<Card>& Player::getHand() const { return hand; }

const vector<Card>& Player::getBestFiveCards() const { return bestFiveCards; }

PlayerStatus Player::getPlayerStatus() const { return playerStatus; }

uint32_t Player::getInitialChips() const { return initialChips; }

uint32_t Player::getRecentBet() const { return recentBet; }

HandCategory Player::getHandCategory() const { return handCategory; }