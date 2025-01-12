#ifndef BETTING_STREET_H
#define BETTING_STREET_H

#include "State.h"
#include "../Shared/Enums.h"

using Street = Enums::Street;

class Winner;

class BettingStreet : public State {
private:
    Street street;
    void executeStreet();
    void handleBlindActions();

public:
    BettingStreet(GameData& gd, GameController& ctrl) : State(gd, ctrl), street(Street::PRE_FLOP) {}
    void execute() override;
    void transition() override;
};

#endif