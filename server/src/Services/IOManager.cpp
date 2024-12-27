#include "../../include/Services/IOManager.h"

IOManager::IOManager(GameData& gameData) : gameData(gameData) {}

void IOManager::displayGameStateStdOut() {
    cout << "(I/O Manager) Displaying the Current Game State" << endl;
    PrintUtil::printPlayers(gameData);
    PrintUtil::printAllCards(gameData);
    PrintUtil::printPots(gameData);
}

void IOManager::displayPossibleActionsStdOut() {
    cout << "(I/O Manager) Displaying Possible Client Actions" << endl;
    PrintUtil::printPossibleActionsForCurPlayer(gameData);
}

vector<pair<string, size_t>> IOManager::addPlayersStdIn() {
    vector<pair<string, size_t>> newPlayers;
    cout << "(I/O Manager) Would you like to add a new player? Reply with 'Y' or 'N'" << endl;
    while (IOUtil::getYesOrNo()) {
        string name = IOUtil::getPlayerName();
        size_t chips = IOUtil::getPlayerChips(gameData.getBigBlind());
        newPlayers.push_back({name, chips});
        cout << "(I/O Manager) Would you like to add another player? Reply with 'Y' or 'N'" << endl;
    }
    return newPlayers;
}

vector<string> IOManager::removePlayersStdIn() {
    vector<string> playersToRemove;
    cout << "(I/O Manager) Would you like to remove existing player(s)? Reply with 'Y' or 'N'" << endl;
    while (IOUtil::getYesOrNo()) {
        string name = IOUtil::getPlayerName();
        if (GameUtil::isPlayerExists(gameData, name)) playersToRemove.push_back(name);
        else cout << "(I/O Manager): " << name << " does not exist in the game!";
        cout << "(I/O Manager) Would you like to remove another player? Reply with 'Y' or 'N'" << endl;
    }
    return playersToRemove;
}

pair<ActionType, size_t> IOManager::getPlayerAction() {
    cout << "(I/O Manager) Please input an action. E.g. 'bet 50' or 'fold'" << endl;
    auto possibleActions = gameData.getPossibleActions();
    ActionType type = IOUtil::getActionType(possibleActions);
    size_t amount = IOUtil::getActionAmount(possibleActions, type);
    return {type, amount};
}