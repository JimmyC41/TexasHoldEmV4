#ifndef WINNER_H
#define WINNER_H

#include "State.h"

class GameSetup;

class Winner : public State {
public:
    Winner(GameData& gd, GameController& ctrl) : State(gd, ctrl) {}
    void execute() override;
    void transition() override;
};

#endif