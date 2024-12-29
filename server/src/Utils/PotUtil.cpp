#include "../../include/Utils/PotUtil.h"

PlayerBetInfo PotUtil::getPlayerRecentBets(GameData& gameData) {
    auto players = gameData.getPlayers();
    PlayerBetInfo playerBets;
    for (const auto& player : players) {
        playerBets.push_back(make_tuple(
            player->getId(),
            player->getRecentBet(),
            player->getPlayerStatus()
        ));
    }
    return playerBets;
}