#ifndef WINNER_H
#define WINNER_H

#include "State.h"

class GameSetup;

class Winner : public State {
public:
    Winner(GameData& gd, GameController& ctrl, StateManager& sm) : State(gd, ctrl, sm) {}

    void execute() override;
    void transition() override;
};

#endif