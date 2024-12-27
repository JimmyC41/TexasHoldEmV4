#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include "State.h"

class BettingStreet;

class GameSetup : public State {
public:
    GameSetup(GameData& gd, GameController& ctrl, StateManager& sm) : State(gd, ctrl, sm) {}

    void execute() override;
    void transition() override;
};

#endif