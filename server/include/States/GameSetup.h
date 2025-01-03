#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include "State.h"

class BettingStreet;

class GameSetup : public State {
private:
    void processPlayerQueue();

public:
    GameSetup(GameData& gd, GameController& ctrl) : State(gd, ctrl) {}

    void execute() override;
    void transition() override;
};

#endif