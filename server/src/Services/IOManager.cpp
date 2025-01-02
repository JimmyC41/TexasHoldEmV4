#include "../../include/Services/IOManager.h"

IOManager::IOManager(GameData& gameData) : gameData(gameData) {}

void IOManager::displayPlayers() {
    cout << "(+) I/O Manager: Displaying players!\n" << endl;
    PrintUtil::printPlayers(gameData);
}

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

void IOManager::displayActionTimeline() {
    cout << "(+) I/O Manager: Displaying action timeline!\n" << endl;
    PrintUtil::printActionTimeline(gameData);
}

void IOManager::displaySubscribers() {
    cout << "(+) I/O Manager: Displaying game subscribers!\n" << endl;
}

vector<pair<string, uint32_t>> IOManager::addPlayersStdIn() {
    vector<pair<string, uint32_t>> newPlayers;
    while (true) {
        cout << "(+) I/O Manager: Would you like to add a new player? ";
        if (!IOUtil::getYesOrNo()) break;

        string name = IOUtil::getPlayerName();
        uint32_t chips = IOUtil::getPlayerChips(gameData.getBigBlind());
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

pair<ActionType, uint32_t> IOManager::getPlayerActionStdIn() {
    cout << "(+) I/O Manager Please input an action. E.g. ('bet 50' or 'fold'): ";
    auto possibleActions = gameData.getPossibleActions();
    ActionType type = IOUtil::getActionType(possibleActions);
    uint32_t amount = IOUtil::getActionAmount(possibleActions, type);
    cout << endl;
    return {type, amount};
}