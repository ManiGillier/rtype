---
ipr: trust200902
stand_alone: true
cat: exp
submissiontype: independent
area: General
title: Really-Triumphal Yanked Protocol Esperances
abbrev: R-Type
lang: en
# date: 2025-12-17
author:
- ins: M. Gillier
  name: Mani Gillier
  email: mani.gillier@epitech.eu
- ins: R. El Janati
  name: Rayane El Janati El Idrissi
  email: rayane.el-janati-el-idrissi@epitech.eu
- ins: M. Huet
  name: Maxime Huet
  email: maxime.huet@epitech.eu
- ins: H. Poggetti
  name: Hugo Poggetti
  email: hugo.poggetti@epitech.eu
normative:
    STD7:
informative:
--- abstract

This document describes the binary network protocol used in the interpretation of the R-Type game made by the said authors.
It defines client-to-server and server-to-client communications.

--- middle

# Introduction

## Requirements Language

{::boilerplate bcp14-tagged}

## Context

At the EuroPean Institute of TECHnology (EPITECH), there is a project
called "R-Type".  
The goal is to make a multiplayer game with a greatly implemented architecture.

## Motivations

This document was created to allow precise definition for the
communication protocol used in the multiplayer game "R-Type" mentionned
in the context above.

## Protocol overview

This protocol is a binary protocol.  
It is TCP [STD7] & UDP [RFC768] based and totally asyncronous.  

# Definitions

The "Server" is a single program responsible of handling one or multiple
"Clients".  
The term "Player" MAY be used as a replacement of the term "Client", but this is context-dependant.  
The "Client" is a single program responsible of connecting to the server
in order to represent the game itself.  
A "Packet" is a short data structure of well-defined size. It is
exchanged between the server and the clients. A packet MUST NOT be
exchanged between clients.  
NO direct communication SHOULD interface clients.  
The "Game" represents the "R-Type" game that the "Server" and "Clients"
represent together.  
This game is a syncronized multiplayer one, where different clients
can connect and play together.  
Each client represents a player that can move up, down, left or right.  
A player is composed of a "Laser".

# Connection

The client MUST init the connection in order to join a game.  
The server MUST accept all connections on a given port before the game
starts.  
A client MAY disconnect at any time.

# Disconnection

The server CAN disconnect a client at any time, for any reason.  
If a client disconnects, or a client is disconnected, the server MUST aknowledge this, and react accordingly with regards to the state of the game.  
The server MUST inform all of the connected clients of the disconnection.  

# Packets

## Structure of a packet

A packet consists of:  
- A single index byte, later referenced as the "index".  
- Multiple data bytes, later referenced as the "data".  
  For integer-type data, the endianness SHOULD be determined as network-byte-order (as defined in the IP specification) [RFC791].  
  The index defines the size of the data.  
  The data is a group of multiple variables, defined and ordered solely by the index.  
  The type of the variables is also defined by the index.
A packet is unidirectionnal. It can either be sent by the client, and
receptionned by the server, or sent by the server, and receptionned
by the targeted client.  
A packet COULD be used bidirectionally, but it SHOULD be limited to strict cases defined in this document.
A packet MAY be sent separated, but they SHOULD be sent in one piece.  
Any receiver of packets MUST handle the case of incomplete packet reception.
If an incomplete packet is received, the receiver MUST wait for the full packet
to arrive before processing it.
Alternatively, the receiver MAY discard any non-complete packets, especially those sent over UDP.

## List of packets

### Server Authentification

When a client connects, it MUST open a TCP and a UDP connection to the server, and this packet SHOULD be used by the server to associate the client to those two connections.

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to the client.

This packet SHOULD be sent when:  
- A client just connected over TCP and UDP

This packet MUST have the following data:  
- Index:0x11  
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: A Unique User Identifier, linked to the client.  

The server MUST choose the UUID.
The client MUST answer to this packet with the Client Authentification packet.

### Client Authentification

This packet MUST:  
- Be an answer to a Server Authentification packet.  
  We will refer to the Unique User Identifier stored in the Server   Authentification packet as the "UUID".  
- Be sent over UDP.  
- Be sent by the client to the server.  

This packet MUST have the following data:  
- Index:0x10  
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: the "UUID" of the Server Authentification packet.  

The server MUST verify that the "UUID" of this packet is conform with the one he chose.
The server SHOULD answer this packet with the Authentified packet. 

### Authentified

This packet MUST:  
- Be an answer to a correct Client Authentification packet.  
- Be sent over TCP.  
- Be sent by the server to the client.  

This packet MUST have the following data:  
- Index:0x12  
- Data size: 0 bytes  
- Data description: None  

No other than the three authentification packets SHOULD be exchanged between a client and the server until the client is considered Authentified and received this packet.

### Start Game packet

This packet is bidirectional.

This packet MUST:  
- Be sent over TCP.  

This packet MUST have the following data:  
- Index:0x13  
- Data size: 0 bytes  
- Data description: None  

This packet SHOULD be sent by the client to the server when:  
- The client decides to start the game.  

This packet SHOULD be sent by the server to all of the authentified clients when:  
- An authentified client decided to start the game by sending this same packet.  

The server SHOULD discard this packet when sent by a player already inside of a game.  
The server SHOULD discard this packet if it doesn't authorize opening a new game.

The client SHOULD NOT discard this packet.

### New Player

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current game.  

This packet SHOULD be sent whenever a new client joins a game, to all client already in the game, and the client joining itself.  
When a new client joins, this packet SHOULD be sent to this client to signify already present players.  
All players MAY join the game at the same time if the server choose to not allow joining already started games.

This packet MUST have the following data:  
- Index:0x03  
- Data size: 16 bytes  
- Data description:  
>  - Unsigned 64 bits integer: A unique identifier representing the player.  
>  - Unsigned 64 bits integer: A unique identifier representing the player's   laser.  

The identifiers SHOULD be determined by the server only.

A client receiving this packet SHOULD instantiate data to allow rendering of the new player mentionned.

### Player Id

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to a specific client.  

This packet SHOULD be used to notify a client of his own player identifier.  
This packet MAY be used by the client to change it's behaviour by knowing that a specific player represents himself.

This packet MUST have the following data:  
- Index:0x01
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The player unique identifier.  

### New Enemy

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current game.  

This packet SHOULD be sent by the server to notify the instantiation of a new enemy in the game.

This packet MUST have the following data:  
- Index:0x05  
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The enemy unique identifier.  

### New Bullet

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current game.  

This packet SHOULD be sent by the server to notify the instantiation of a new bullet in the game.

This packet MUST have the following data:  
- Index:0x04  
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The bullet unique identifier.  

### Enemy Died

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current game.  

This packet MAY be sent by the server to notify the death of an enemy.  
This packet MAY be used by the client to remove an enemy from his internal datas.  

This packet MUST have the following data:  
- Index:0x0A  
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The enemy unique identifier.  

### Player Died

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current game.  

This packet MAY be sent by the server to notify the death of a player.  
This packet MAY be used by the client to remove an enemy from his internal datas, or to show a ghost of the ancient player.  

This packet MUST have the following data:  
- Index:0x07  
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The player unique identifier.  

### Despawn Bullet

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current game.  

This packet MAY be sent by the server to notify the disappearance of a bullet.  
This packet CAN be sent by the server to notify the disappearance of any entity via his unique identifier, but it is not a good practice.  
This packet MAY be used by the client to remove the bullet from his datas.

This packet MUST have the following data:  
- Index:0x09  
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The bullet unique identifier.  

### Despawn Player

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current game.  

This packet MUST be sent by the server to notify the disconnection of a player.
This packet MAY be used by the client to remove the bullet from his datas.

This packet MUST have the following data:  
- Index:0x08  
- Data size: 8 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The player unique identifier.  

### Player Hit

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to the targeted client.  

This packet SHOULD be sent by the server to notify a client that he has been hit in the game.  
This packet CAN be used by the client to play some special behaviour in case of a hit.  
In case of a general hit (meaning that the player was hit without having it caused by an entity), the server SHOULD set the hit entity unique identifier to be equal to the player unique identifier.  

This packet MUST have the following data:  
- Index:0x06  
- Data size: 16 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The player unique identifier.  
>  - Unsigned 64 bits integer: The entity (that hit) unique identifier.  

### Hitbox Size Update

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the game.  

This packet SHOULD be sent by the server to inform the client of the hitboxes sizes.  
It MAY be sent right after sending the instantiating packet of an entity having a hitbox.  
It MAY be sent before the sending of an instantiating packet for the said entity.

This packet MUST have the following data:  
- Index:0x0E  
- Data size: 16 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The entity unique identifier.  
>  - 32 bits Floating point number [IEEE754]: The width of the hitbox in unit.  
>  - 32 bits Floating point number [IEEE754]: The height of the hitbox in unit.  

### Game Over

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all client in the game.  

This packet MUST be sent by the server to inform all clients that a game has ended.  
The server SHOULD provide the right state.

This packet MUST have the following data:  
- Index:0x0B  
- Data size: 1 byte  
- Data description:  
>  - Unsigned 8bits integer: The state of the game that SHOULD be represented by one of those values:  
>    - Win: 1.  
>    - Loose: 2.  

### Health Update

This packet MUST:  
- Be sent over UDP.  
- Be sent by the server to all client in the game.  

This packet CAN be sent by the server to inform players of the health status of different entities, like enemies or other players.

This packet MUST have the following data:  
- Index:0x0D  
- Data size: 16 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The entity unique identifier.  
>  - 32 bits Floating point number [IEEE754]: The current health in health units.  
>  - 32 bits Floating point number [IEEE754]: The maximum health in health units.  

As it is a UDP packet, it SHOULD be sent as a stream at a server-defined rate.
This packet SHOULD not only be triggered when a health modification occurs.
This packet COULD be triggered when a health modification occurs, as long as it is also triggered at a server-defined rate, different from zero.

### Laser Active Update

This packet MUST:  
- Be sent over UDP.  
- Be sent by the server to all client in the game.  

This packet CAN be sent by the server to inform players of the laser status of a player in the game.

This packet MUST have the following data:  
- Index:0x0F  
- Data size: 13 bytes  
- Data description:  
>  - Unsigned 64 bits integer: The entity unique identifier.  
>  - Unsigned 8 bits integer: Boolean describing the state of activation of the player laser.  
>  - 32 bits Floating point number [IEEE754]: The player laser size in units,   activated or not.  

The unactivated size of the laser is UNDEFINED for both the client and the server.

As it is a UDP packet, it SHOULD be sent as a stream at a server-defined rate.
The same principles as the Health packet applies.

### Position Update

This packet MUST:  
- Be sent over UDP.  
- Be sent by the server to all client in the game.  

This packet SHOULD be sent by the server to inform players of the position of an entity in game.

This packet MUST have the following data:  
 - Index:0x0C  
 - Data size: 16 bytes  
 - Data description:  
>    - Unsigned 64 bits integer: The entity unique identifier.  
>    - 32 bits Floating point number [IEEE754]: The position of the entity accross the width.  
>    - 32 bits Floating point number [IEEE754]: The position of the entity accross the height.  

The unactivated size of the laser is UNDEFINED for both the client and the server.

As it is a UDP packet, it SHOULD be sent as a stream at a server-defined rate.
The same principles as the Health packet applies.

### Client Inputs

This packet MUST:  
- Be sent over UDP.  
- Be sent by a client to the server  

This packet SHOULD be sent by a client to the server to inform the server of the user inputs, at a regular interval.

This packet MUST have the following data:
- Index:0x02  
- Data size: 1 bytes  
- Data description:  
>  - 1 bit: Boolean for the LEFT movement key state.  
>  - 1 bit: Boolean for the RIGHT movement key state.  
>  - 1 bit: Boolean for the UP movement key state.  
>  - 1 bit: Boolean for the DOWN movement key state.  
>  - 1 bit: Boolean for the SHOOT key state.  
>  - 3 bits: MAY be set to zeroes. MUST NOT be used.  

As it is a UDP packet, it SHOULD be sent as a stream at a client-defined rate.
The same principles as the Health packet applies.

# Game logic

The game logic MUST be defined solely by the server.
The client SHOULD not have decisive power except from their inputs.

# IANA Considerations {#IANA}

This memo includes no request to IANA.


# Security Considerations {#Security}

This document should not affect the security of the Internet.

--- back
