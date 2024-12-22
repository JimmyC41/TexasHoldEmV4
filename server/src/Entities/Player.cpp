#include "../../include/Entities/Player.h"
#include "../../include/Utils/PlayerUtil.h"

Player::Player(string name, size_t chips) :
    name(name),
    id(PlayerUtil::generateUUID()),
    position(Position::LOBBY),
    curChips(chips),
    hand(),
    playerStatus(PlayerStatus::WAITING),
    isActing(false),
    initialChips(0),
    possibleActions(),
    recentBet(0)
{}

// SETTER METHODS

void Player::setPosition(Position newPosition) { position = newPosition; }

void Player::addChips(size_t newChips) { curChips += newChips; }

void Player::reduceChips(size_t lostChips) { curChips -= lostChips; }

void Player:: addHoleCard(const Card& card) { hand.push_back(card); }

void Player::clearHand() { hand.clear(); }

void Player::setPlayerStatus(PlayerStatus status) { playerStatus = status; }

void Player::setIsActing(bool act) { isActing = act; }

void Player:: setInitialChips(size_t chips) { initialChips = chips; }

void Player::setPossibleActions(const vector<shared_ptr<Action>>& actions) { possibleActions = actions; }

void Player::setRecentBet(size_t newBet) { recentBet = newBet; }

// GETTER METHODS

const string& Player::getName() const { return name; }

const string& Player::getId() const { return id; }

Position Player:: getPosition() const { return position; }

size_t Player::getCurChips() const { return curChips; }

const vector<Card>& Player::getHand() const { return hand; }

PlayerStatus Player::getPlayerStatus() const { return playerStatus; }

bool Player::getIsActing() const { return isActing; }

size_t Player::getInitialChips() const { return initialChips; }

const vector<shared_ptr<Action>>& Player::getPossibleActions() const { return possibleActions; }

size_t Player::getRecentBet() const { return recentBet; }