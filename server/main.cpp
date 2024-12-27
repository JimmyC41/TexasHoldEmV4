#include "GameController.h"

int main() {
    GameController controller;
    controller.beginGameSetup();
    for (size_t i = 0; i < 50; ++i) controller.moveToNextState();
    return 0;
}