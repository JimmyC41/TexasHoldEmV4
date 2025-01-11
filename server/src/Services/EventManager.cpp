#include "../../include/Services/EventManager.h"
#include "../../include/Entities/Player.h"
#include "../../include/gRPC/ProtoUtil.h"
#include "../../include/Utils/GameUtil.h"

#include <google/protobuf/util/json_util.h>
#include <iostream>

using ProtoPossibleAction = PlayerToActInfo_ProtoPossibleAction;
using ProtoAction = PlayerActionInfo_ProtoAction;

EventManager::EventManager(GameData& gameData) : gameData(gameData) {}

void EventManager::addSubscriber(grpc::ServerWriter<GameStreamRes>* writer) {
    lock_guard<mutex> lock(subscriberMutex);

    cout << "(+) Event Manager: Adding a new subscriber!\n" << endl;
    subscribers.insert(writer);
}

void EventManager::removeSubscriber(grpc::ServerWriter<GameStreamRes>* writer) {
    lock_guard<mutex> lock(subscriberMutex);

    cout << "(+) Event Manager: Removing an existing subscriber!\n" << endl;
    subscribers.erase(writer);
}

bool EventManager::allPlayersSubscribed() {
    return (subscribers.size() == gameData.getNumPlayers());
}

int EventManager::getNumSubs() {
    return subscribers.size();
}

void EventManager::publishEvent(const GameStreamRes& event) {
    lock_guard<mutex> lock(subscriberMutex);

    // cout << "(+) Event Manager: Publishing an event to " << subscribers.size() << "subscribers.\n" << endl;
    for (auto it = subscribers.begin(); it != subscribers.end(); ) {
        if (!(*it)->Write(event)) it = subscribers.erase(it);
        else ++it;
    }

    // For debugging, log JSON-ified output
    logJsonOutput(event);
}

void EventManager::publishPlayersUpdateEvent() {
    GameStreamRes event;
    PlayersUpdateEvent* playersUpdate = event.mutable_players_update();

    const auto& players = gameData.getPlayers();
    for (const auto& player : players) {
        ProtoPlayer* cur = playersUpdate->add_new_players();
        cur->set_name(player->getName());
        cur->set_id(player->getId());
        cur->set_chips(player->getCurChips());
        cur->set_recent_bets(player->getRecentBet());
        cur->set_status(ProtoUtil::toProtoStatus(player->getPlayerStatus()));
        cur->set_position(ProtoUtil::toProtoPosition(player->getPosition()));
    }

    publishEvent(event);
    cout << "[+] PlayersUpdateEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::publishNewStreetEvent() {
    GameStreamRes event;
    NewStreetEvent* newStreet = event.mutable_new_street();

    ProtoStreet protoStreet = ProtoUtil::toProtoStreet(gameData.getStreet());
    newStreet->set_new_street(protoStreet);

    publishEvent(event);
    cout << "[+] NewStreetEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::publishDealPlayersEvent() {
    GameStreamRes event;
    DealPlayersEvent* dealPlayers = event.mutable_deal_players();

    const auto& players = gameData.getPlayers();

    // For each player, set their id and hand
    for (const auto& player : players) {
        // Create the PlayerCard message
        PlayerCard* cur = dealPlayers->add_player_cards();

        // Set the player id
        cur->set_player_id(player->getId());
        
        // Set the hole cards
        vector<Card> cards = player->getHand();
        for (const auto& card : cards) {
            ProtoCard* protoCard = cur->add_hole_cards();
            protoCard->set_value(ProtoUtil::toProtoValue(card.getValue()));
            protoCard->set_suit(ProtoUtil::toProtoSuit(card.getSuit()));
        }
    }

    publishEvent(event);
    cout << "[+] DealPlayersEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::publishDealBoardEvent() {
    GameStreamRes event;
    DealBoardEvent* dealBoard = event.mutable_deal_board();

    vector<Card> boardCards = gameData.getBoardCards();
    for (const auto& card : boardCards) {
        ProtoCard* protoCard = dealBoard->add_community_cards();
        protoCard->set_value(ProtoUtil::toProtoValue(card.getValue()));
        protoCard->set_suit(ProtoUtil::toProtoSuit(card.getSuit()));
    }

    publishEvent(event);
    cout << "[+] DealBoardEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::publishNewPlayerToActEvent() {
    GameStreamRes event;
    NewPlayerToActEvent* newPlayerToAct = event.mutable_next_player_to_act();
    PlayerToActInfo* playerToActInfo = newPlayerToAct->mutable_player_to_act_info();

    string id = GameUtil::getCurPlayerId(gameData);
    playerToActInfo->set_player_to_act(id);

    vector<shared_ptr<PossibleAction>> possibleActions = gameData.getPossibleActions();
    for (const auto& action : possibleActions) {
        ProtoPossibleAction* cur = playerToActInfo->add_possible_actions();
        cur->set_action_type(ProtoUtil::toProtoType(action->getActionType()));
        cur->set_primary_amount(action->getPrimaryAmount());
        cur->set_secondary_amount(action->getSecondaryAmount());
    }

    publishEvent(event);
    cout << "[+] NewPlayerToActEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::publishNewPlayerActionEvent() {
    GameStreamRes event;
    NewPlayerActionEvent* newPlayerAction = event.mutable_new_player_action();
    PlayerActionInfo* playerActionInfo = newPlayerAction->mutable_player_action_info();

    // lastAction is nullptr at the end of the winner state
    shared_ptr<Action> lastAction = GameUtil::getLastAction(gameData);
    if (lastAction == nullptr) {
        // Publish an 'emtpy' lastAction
        publishEvent(event);
        return;
    }

    string id = GameUtil::getCurPlayerId(gameData);
    playerActionInfo->set_player_id(id);
    ProtoAction* action = playerActionInfo->mutable_action();
    action->set_action_type(ProtoUtil::toProtoType(lastAction->getActionType()));
    action->set_action_amount(lastAction->getAmount());
    publishEvent(event);
    cout << "[+] NewPlayerActionEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::publishPotUpdateEvent() {
    GameStreamRes event;
    PotUpdateEvent* potUpdate = event.mutable_pot_update();

    vector<shared_ptr<Pot>> pots = gameData.getPots();
    for (const auto& pot : pots) {
        ProtoPot* cur = potUpdate->add_updated_pots();
        cur->set_pot_chips(pot->getChips());

        vector<string> ids = pot->getContributorIds();
        for (const auto& id : ids) {
            cur->add_eligible_ids(id);
        }
    }

    publishEvent(event);
    cout << "[+] PotUpdateEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::publishShowdownEvent() {
    GameStreamRes event;
    ShowdownEvent* showdown = event.mutable_showdown();

    vector<Player*> playersNotFolded = GameUtil::getPlayersNotFolded(gameData);
    for (const auto& player : playersNotFolded) {
        showdown->add_players_in_hand(player->getId());
    }

    publishEvent(event);
    cout << "[+] ShowdownEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::publishPotWinnerEvent() {
    GameStreamRes event;
    PotWinnerEvent* potWinner = event.mutable_pot_winner();

    vector<pair<uint32_t, string>> winners = gameData.getPotWinners();
    for (const auto& [potAmount, winnerId] : winners) {
        PotWinner* cur = potWinner->add_pot_winners();
        cur->set_pot_chips(potAmount);
        cur->set_winner(winnerId);
    }
    
    publishEvent(event);
    cout << "[+] PotWinnerEvent published to " << subscribers.size() << " subscribers.\n" << endl;
}

void EventManager::logJsonOutput(const GameStreamRes& event) {
    string jsonString;
    (void)google::protobuf::util::MessageToJsonString(event, &jsonString);
    cout << "JSON Output: " << jsonString << endl;
}