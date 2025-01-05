// Game Events

export const PLAYERS_UPDATE_EVENT = 'PLAYERS_UPDATE EVENT';
export const NEW_STREET_EVENT = 'NEW_STREET_EVENT';
export const DEAL_PLAYERS_EVENT = 'DEAL_PLAYERS_EVENT';
export const DEAL_BOARD_EVENT = 'DEAL_BOARD_EVENT';
export const NEXT_PLAYER_TO_ACT_EVENT = 'NEXT_PLAYER_TO_ACT_EVENT';
export const NEW_PLAYER_ACTION_EVENT = 'NEW_PLAYER_ACTION_EVENT';
export const POT_UPDATE_EVENT = 'POT_UPDATE_EVENT';
export const SHOWDOWN_EVENT = 'SHOWDOWN_EVENT';
export const POT_WINNER_EVENT = 'POT_WINNER_EVENT';

export const playersUpdateEvent = (playersUpdate) => ({
    type: PLAYERS_UPDATE_EVENT,
    payload: playersUpdate 
});

export const newStreetEvent = (newStreet) => ({
    type: NEW_STREET_EVENT,
    payload: newStreet
});

export const dealPlayersEvent = (dealPlayers) => ({
    type: DEAL_PLAYERS_EVENT,
    payload: dealPlayers
});

export const dealBoardEvent = (dealBoard) => ({
    type: DEAL_BOARD_EVENT,
    payload: dealBoard
});

export const nextPlayerToActEvent = (nextPlayerToAct) => ({
    type: NEXT_PLAYER_TO_ACT_EVENT,
    payload: nextPlayerToAct
});

export const newPlayerActionEvent = (newPlayerAction) => ({
    type: NEW_PLAYER_ACTION_EVENT,
    payload: newPlayerAction
});

export const potUpdateEvent = (potUpdate) => ({
    type: POT_UPDATE_EVENT,
    payload: potUpdate
});

export const showdownEvent = (showdown) => ({
    type: SHOWDOWN_EVENT,
    payload: showdown
});

export const potWinnerEvent = (potWinner) => ({
    type: POT_WINNER_EVENT,
    payload: potWinner
})