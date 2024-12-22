#ifndef STATE_H
#define STATE_H

#include <iostream>
using namespace std;

class StateManager;

class State {
public:
    virtual ~State() = default;
    virtual void enter() = 0;
    virtual void transition(StateManager& manager) = 0;
};

class GameSetup : public State {
public:
    void enter() override;
    void transition(StateManager& manager) override;
};

class RoundSetup : public State {
public:
    void enter() override;
    void transition(StateManager& manager) override;
};

class StreetSetup : public State {
public:
    void enter() override;
    void transition(StateManager& manager) override;
};

class StreetInProgress : public State {
public:
    void enter() override;
    void transition(StateManager& manager) override;
};

class StreetEnd : public State {
public:
    void enter() override;
    void transition(StateManager& manager) override;
};


class Showdown : public State {
public:
    void enter() override;
    void transition(StateManager& manager) override;
};

class AnnounceWinner : public State {
public:
    void enter() override;
    void transition(StateManager& manager) override;
};

class RoundEnd : public State {
public:
    void enter() override;
    void transition(StateManager& manager) override;
};

#endif