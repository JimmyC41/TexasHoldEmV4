#include "../../include/Services/IOManager.h"

IOManager::IOManager(GameData& gameData) : gameData(gameData) {}

void IOManager::displayGameStateStdOut() {
    cout << "(+) I/O Manager: Displaying the current game state!\n" << endl;
    PrintUtil::printPlayers(gameData);
    PrintUtil::printAllCards(gameData);
    PrintUtil::printPots(gameData);
}

void IOManager::displayPossibleActionsStdOut() {
    cout << "(+) I/O Manager: Displaying possible actions!\n" << endl;
    PrintUtil::printPossibleActionsForCurPlayer(gameData);
}

vector<pair<string, size_t>> IOManager::addPlayersStdIn() {
    vector<pair<string, size_t>> newPlayers;
    while (true) {
        cout << "(+) I/O Manager: Would you like to add a new player? ";
        if (!IOUtil::getYesOrNo()) break;

        string name = IOUtil::getPlayerName();
        size_t chips = IOUtil::getPlayerChips(gameData.getBigBlind());
        newPlayers.push_back({name, chips});
    }
    cout << endl;
    return newPlayers;
}

vector<string> IOManager::removePlayersStdIn() {
    vector<string> playersToRemove;
    while (true) {
        cout << "(+) I/O Manager: Would you like to remove existing player(s)? ";
        if (!IOUtil::getYesOrNo()) break;

        string name = IOUtil::getPlayerName();
        if (GameUtil::isPlayerExists(gameData, name)) playersToRemove.push_back(name);
        else cout << "(+) I/O Manager: " << name << " does not exist in the game!" << endl;
    }
    return playersToRemove;
}

pair<ActionType, size_t> IOManager::getPlayerActionStdIn() {
    cout << "(+) I/O Manager Please input an action. E.g. ('bet 50' or 'fold'): ";
    auto possibleActions = gameData.getPossibleActions();
    ActionType type = IOUtil::getActionType(possibleActions);
    size_t amount = IOUtil::getActionAmount(possibleActions, type);
    cout << endl;
    return {type, amount};
}