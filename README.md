# Multiplayer Texas Hold'Em Poker Game
TexasHoldEmV4 is a C++/gRPC/React full-stack implementation of No Limit Texas Hold'Em, designed to run in a local environment. See a demonstration of the game [here](https://www.youtube.com/watch?v=gVX44eQESlI).

### Project Goals
1. Apply OOP and the C++ STL to a non-trivial C++ Application.
2. Use C++ development tools such as CMake, GTest, Conan.
3. Serialise data with Protocol Buffers and implement server-client streaming with gRPC.

## System Design
A high-level overview of the explanation is provided below.

### C++ Backend
* **GameController:** Is the game coordinator. Delegates all poker-related logic such as the calculation of pots or evaluation of player hands to various 'Service' classes: ActionManager, PotManager and HandRankManager to name a few.
* **GameData:** The single source of truth for the game state, and serves as the 'in-memory' database. Services will pull and push updates to GameData.
* **Services** handle poker-related game logic.
  * **Action Manager** processes actions and determines valid actions (e.g. if player A bets, what can player B do?).
  * **PotManager** manages the pot sizes and distributes winnings. PositionManager manages player's positions and movements between rounds.
  * **HandRankManager** evaluates relative hand strengths and provides a player ranking.
  * **StateManager** manages transitions between states (see below), which houses the game flow for a specific state (e.g. a betting street).
  * **DealerManager** manages the deck and dealing of both player and community cards.
  * **PositionManager** manages the addition and removal of players in the game.
  * **RequestManager** (see below) keeps track of outstanding unary gRPC methods.
  * **IOManager** (deprecated) was used to display the game state to stdout and retrieve player inputs from stdin in the development stage before the React frontend was introduced.
* **States**: Represent defined states that a Poker game goes through.
  * **GameSetup:** Players are added/removed. Cards are shuffled.
  * **BettingStreet:** Hole and community cards are dealt. Betting action occurs. Pots are calculated.
  * **Winner:** Players showdown (if end of River reached). Winner(s) are awarded pots. Game state is cleared for the next round - cards are retrieved and players rotate around the table.
* **Entities**: Board, Card, Deck and Player. Exactly what they sound like.

### Server-Client Communication
* **For Unary Calls:** The client invokes a gRPC method. This request is parsed through the RequestManager in the backend. The RequestManager manages various queues for join requests, leave requests and action requests and dispatches such requests to the relevant Service when needed.
* **For Streaming Calls:** The client invokes a gRPC method to receieve game state updates. In the backend, an EventManager publishes various game events to subscribed clients, such as the dealing of cards or a new player action.
* The frontend receieves a JSON-ified version of game events and dynamically renders the game state with React's useContext and useReducer.

## Running the Application
Before running the application, ensure you have the following installed:
* Conan for managing dependencies
* Envoy Proxy installed and configured for gRPC traffic
* The Protobuf compiler (update the path to the executable in the CMake file)
* Node.js and npm

1. Build and run the backend:
```
./scripts/build-server.sh
./scripts/run-server.sh
```
2. Start Envoy to route gRPC traffic. In another terminal:
```
cd web-client
envoy -c envoy.yaml
```
3. Launch the Frontend. In another terminal:
```
cd web-client
npm install
npx webpack serve
```
4. Open your web browser and navigate to the frontend:
```
http://localhost:8080
```



