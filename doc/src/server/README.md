# RType Server

The RType Server is the game server implementation that extends RéseauType's `Server` class.
It manages game sessions (limited to one right now), and player connections.

# Server Responsibilities

## Game State Management

The server maintains the authoritative game state.

It processes player inputs, updates entity positions, handles collisions, and manages game logic. 

Clients receive updates from the server but cannot modify the game state directly.

## Player Connection Handling

When a player connects, the server creates a new client instance and assigns them a unique UUID.

The server tracks all connected players and removes them from the game when they disconnect.

## Packet Processing:

The server uses packet executors to handle different types of packets:
- `CLIENT_INPUTS`: Processes player input and updates game state
- `GAME_START_REQUEST`: Starts a new game session
- etc..

## Entity Synchronization
The server broadcasts entity updates to all clients using packets like:

- `POSITION_UPDATE`: Sends entity positions
- `HEALTH_UPDATE`: Sends health changes
- `NEW_PLAYER`, `NEW_BULLET`, `NEW_ENEMY`: Spawns new entities
- `DESPAWN_PLAYER`, `DESPAWN_BULLET`: Removes entities
- etc..

## Server Authority

The server validates all client inputs.

Players cannot send their own positions or modify game state directly.

The server calculates everything and sends results to clients.

# What is done

Currently, the server allows launching a multiplayer game session.
Players can see each other move around and shoot at enemies.

There are two types of enemies: small enemies and big bosses. Players can shoot at them.

When there are no more enemies on the field, they respawn again. Enemies spawn from the left side of the screen.
Players have health points. When all players die, the game is over.

