#ifndef BETTING_STREET_H
#define BETTING_STREET_H

#include "State.h"

class Winner;

class BettingStreet : public State {
public:
    BettingStreet(GameData& gd, GameController& ctrl, StateManager& sm) : State(gd, ctrl, sm) {}

    void execute() override;
    void transition() override;
};

#endif