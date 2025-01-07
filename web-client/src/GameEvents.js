// Event Type Constants
export const PLAYERS_UPDATE_EVENT = 'PLAYERS_UPDATE_EVENT';
export const NEW_STREET_EVENT = 'NEW_STREET_EVENT';
export const DEAL_PLAYERS_EVENT = 'DEAL_PLAYERS_EVENT';
export const DEAL_BOARD_EVENT = 'DEAL_BOARD_EVENT';
export const NEXT_PLAYER_TO_ACT_EVENT = 'NEXT_PLAYER_TO_ACT_EVENT';
export const NEW_PLAYER_ACTION_EVENT = 'NEW_PLAYER_ACTION_EVENT';
export const POT_UPDATE_EVENT = 'POT_UPDATE_EVENT';
export const SHOWDOWN_EVENT = 'SHOWDOWN_EVENT';
export const POT_WINNER_EVENT = 'POT_WINNER_EVENT';

export const createEventAction = (eventType) => (payload) => ({
  	type: eventType,
  	payload,
});

// Event Creators
export const playersUpdateEvent = createEventAction(PLAYERS_UPDATE_EVENT);
export const newStreetEvent = createEventAction(NEW_STREET_EVENT);
export const dealPlayersEvent = createEventAction(DEAL_PLAYERS_EVENT);
export const dealBoardEvent = createEventAction(DEAL_BOARD_EVENT);
export const nextPlayerToActEvent = createEventAction(NEXT_PLAYER_TO_ACT_EVENT);
export const newPlayerActionEvent = createEventAction(NEW_PLAYER_ACTION_EVENT);
export const potUpdateEvent = createEventAction(POT_UPDATE_EVENT);
export const showdownEvent = createEventAction(SHOWDOWN_EVENT);
export const potWinnerEvent = createEventAction(POT_WINNER_EVENT);