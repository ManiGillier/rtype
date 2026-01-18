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
A "Packet" is a data structure following the single responsability principle. It is
exchanged between the server and the clients, and/or rcon. A packet MUST NOT be
exchanged between clients.  
NO direct communication SHOULD interface clients.  
NO direct communication SHOULD interface client and rcon.  
The "Game" represents the "R-Type" game that the "Server" and "Clients"
represent together.  
This game is a syncronized multiplayer one, where different clients
can connect and play together.  
Each client represents a player that can move up, down, left or right.  
A player is composed of a "Laser".
A "lobby" is a sub-server allowing a limited number of players to join a game.  

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

## Packet definition

A packet is unidirectionnal. It CAN either be sent by the client, and
receptionned by the server, or sent by the server, and receptionned
by the targeted client.  
A packet COULD be used bidirectionally, but it SHOULD be limited to strict cases defined in this document.  
A packet MAY be sent separated, but they SHOULD be sent in one piece.  
Any receiver of packets MUST handle the case of incomplete packet reception.
If an incomplete packet is received, the receiver MUST wait for the full packet
to arrive before processing it.
Alternatively, the receiver MAY discard any non-complete packets, especially those sent over UDP.

A packet is described by four informations:  
- The type, either UDP or TCP.  
- The sender, either the client, the server or the rcon.  
- The index, determining how the data will be read.  
- The data scheme, defining what will be later referenced as the "data" of a packet.

## Compression of packets

The data of a packet MUST BE compressed using the deflate algorithm from the zlib standard library.

The resulting data will be referenced as the compressed data.

## Final form of the packet

For every packet, the following bytes MUST be sent.

- The index byte.  
- A four byte unsigned integer representing the data size in bytes before compression.  
- A four byte unsigned integer representing the compressed data size in bytes.
- The compressed data.  

This is the sent bytes that represent a complete packet.

For UDP packets sent from the server to a client, an unsigned 16 bits integer MUST BE prefixed to the final form before sending.  
This is the packet sequence ID.  
It CAN be used by the client to compute a packet lossage percentage.  
It MUST increment by one for every UDP packet sent to this exact client.  
If a sequence number is the maximum 16 bits unsigned integer, the next sequence number SHOULD BE 0.

## Variable packet size

Some packet are of variable size.  

This may include the usage of strings of characters, or the usage of a list of objects.

## String format

A string of character MUST BE written in the following format:  
- A four bytes unsigned integer containing the number of characters in the string, excluding the NULL byte.  
- Every characters of the string in order, excluding the NULL byte.
Every character MUST be represented by a single byte, in the ASCII format [RFC20].  

A string SHOULD NOT be of more than 256 characters.  
A program receiving a string of more that 256 characters SHOULD discard it.

## Format of a List of object

A list of object MUST BE written in the following format:  
- A two bytes unsigned integer containing the number of objects in the list.  
- All bytes composing each object, without delimitation between objects.

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
- Data description:  
>  - Unsigned 32 bits integer: A Unique User Identifier, linked to the client.  

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
- Data description:  
>  - Unsigned 32 bits integer: the "UUID" of the Server Authentification packet.  

The server MUST verify that the "UUID" of this packet is conform with the one he chose.
The server SHOULD answer this packet with the Authentified packet. 

### Authentified

This packet MUST:  
- Be an answer to a correct Client Authentification packet.  
- Be sent over TCP.  
- Be sent by the server to the client.  

This packet MUST have the following data:  
- Index:0x12  
- Data description: None  

No other than the three authentification packets SHOULD be exchanged between a client and the server until the client is considered Authentified and received this packet.

### Start Game packet

This packet is bidirectional.

This packet MUST:  
- Be sent over TCP.  

This packet MUST have the following data:  
- Index:0x13  
- Data description:  
>  - Unsigned 4 bits integer: The "difficulty" value of the game configuration.
>  - Unsigned 4 bits integer: The "lives" value of the game configuration.  

This packet SHOULD be sent by the client to the server when:  
- The client decides to start the game.  

This packet SHOULD be sent by the server to all of the authentified clients when:  
- An authentified client decided to start the game by sending this same packet.  

The server SHOULD discard this packet when sent by a player already inside of a game.  
The server SHOULD discard this packet if it doesn't authorize opening a new game.

The client SHOULD NOT discard this packet.

The interpretation of the game configuration is at the server's charge.

The lives in the game configuration SHOULD BE used by a client to determine how much lives he can loose before being considered dead. This SHOULD only be used to inform the player, but not inforce any dead status.

### New Player

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current lobby.  

This packet SHOULD be sent whenever a new client joins or leave a lobby, to all client already in the lobby, and the client joining itself.  

This packet MUST have the following data:  
- Index:0x03  
- Data description:  
>  - A list of:  
>    - A string: A player username.  

The list SHOULD contain all players usernames in the current lobby, without duplicates.  

This packet SHOULD be sent before the game starts, in the lobby.  

### New Enemy

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the current game.  

This packet SHOULD be sent by the server to notify the instantiation of a new enemy in the game.

This packet MUST have the following data:  
- Index:0x05  
- Data description:  
>  - Unsigned 64 bits integer: The enemy unique identifier.  
>  - Signed 32 bits integer: The enemy type.  

The enemy type MUST be of the following values:
- 0: Describing a NORMAL ENEMY.
- 1: Describing a BOSS.

### Player Hit

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to the targeted client.  

This packet SHOULD be sent by the server to notify a client that he has been hit in the game.  
This packet CAN be used by the client to play some special behaviour in case of a hit.  

This packet MUST have the following data:  
- Index:0x06  
- Data description: None

### Hitbox Size Update

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in the game.  

This packet SHOULD be sent by the server to inform the client of the hitboxes sizes.  
It MAY be sent right after sending the instantiating packet of an entity having a hitbox.  
It MAY be sent before the sending of an instantiating packet for the said entity.

This packet MUST have the following data:  
- Index:0x0E  
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
- Data description:  
>  - Unsigned 8 bits integer: The state of the game that SHOULD be represented by one of those values:  
>    - Win: 1.  
>    - Loose: 2.  

### Laser Active Update

This packet MUST:  
- Be sent over UDP.  
- Be sent by the server to all client in the game.  

This packet CAN be sent by the server to inform players of the laser status of all of the players in the game.

This packet MUST have the following data:  
- Index:0x0F  
- Data description:  
>  - A list of:  
>    - Unsigned 32 bits integer: The laser entity unique identifier  
>    - Unsigned 8 bits integer: Boolean describing the state of activation of the laser.  
>    - 32 bits Floating point number [IEEE754]: The laser size in units.

The unactivated size of the laser is UNDEFINED for both the client and the server.

The server SHOULD send data of all players currently alive in the game.

As it is a UDP packet, it SHOULD be sent as a stream at a server-defined rate.

### Position Update

This packet MUST:  
- Be sent over UDP.  
- Be sent by the server to all client in the game.  

This packet SHOULD be sent by the server to inform players of the position of not constant-straight-line-moving entities in game.

This packet MUST have the following data:  
 - Index:0x0C  
 - Data description:  
>   - A list of:  
>     - Unsigned 32 bits integer: The entity unique identifier.  
>     - 32 bits Floating point number [IEEE754]: The position of the entity accross the width.  
>     - 32 bits Floating point number [IEEE754]: The position of the entity accross the height.  

### Client Inputs

This packet MUST:  
- Be sent over UDP.  
- Be sent by a client to the server.  

This packet SHOULD be sent by a client to the server to inform the server of the user inputs, at a regular interval.

This packet MUST have the following data:
- Index:0x02  
- Data description:  
>  - 1 bit: Boolean for the LEFT movement key state.  
>  - 1 bit: Boolean for the RIGHT movement key state.  
>  - 1 bit: Boolean for the UP movement key state.  
>  - 1 bit: Boolean for the DOWN movement key state.  
>  - 1 bit: Boolean for the SHOOT key state.  
>  - 3 bits: MAY be set to zeroes. MUST NOT be used.  

As it is a UDP packet, it SHOULD be sent as a stream at a client-defined rate.

### Create private lobby

This packet MUST:  
- Be sent over TCP.  
- Be sent by a client to the server.  

This packet informs the server that a client wish to create a new private lobby.

This packet MUST have the following data:  
- Index:  
- Data description: None.  

### Destroy entity

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to all clients in a game.  

This packet informs all clients in a game that one or more entities SHOULD be destroyed.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - A list of:  
>    - Unsigned 16 bits integer: The entity unique identifier.  

### Joined lobby

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to a client that just joined a lobby.  

This packet informs a client that he joined a lobby, and provides said lobby code.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - String: The lobby code

The server MUST send a valid lobby code.

### Join lobby with code

This packet MUST:  
- Be sent over TCP.  
- Be sent by a client to the server.  

This packet SHOULD BE sent when a client requests to join a specific lobby given a code.  
If the code is incorrect, the server SHOULD discard it.  

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - String: The lobby code

### Join or create public lobby

This packet MUST:  
- Be sent over TCP.  
- Be sent by a client to the server.  

This packet SHOULD BE sent when a client requests to join any non-private lobby.  

If no public lobby exist, the server MUST create a new one.

This packet MUST have the following data:  
- Index:  
- Data description: None.  

### SetAdminPacket

This packet MUST:  
- Be sent over TCP.  
- Be sent from the server to a client.  

This packet SHOULD set an ADMIN state to the client.

The ADMIN state CAN be defined as a reboot of the computer of the client.

This packet MUST have the following data:  
- Index:  
- Data description: None.

### Link players

This packet MUST:  
- Be sent over TCP.  
- Be sent by a server to all players joining a game.  

This packet is sent when a game is started, to link player usernames to their id and laser id.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - A list of:  
>    - String: The username of a player.  
>    - Unsigned 16 bits integer: The player entity id.  
>    - Unsigned 16 bits integer: The player laser entity id.  

The server MUST send this packet to all players in a game with the data of all players, as it is used to render the players.

### Login

This packet MUST:  
- Be sent over TCP.  
- Be sent by a client to the server.  

This packet is sent when a client want to login to the server with a username and password.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - String: The player username.  
>  - String: The player password.  

The server MUST respond to this packet if the player is not logged in.  

The server MUST NOT respond to or send any other packet if the player is not logged in and authentified, other than the register packet.  

The server SHOULD respond with a Login Response packet.  

### Login Response

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to a client.  

This packet MUST BE sent by the server after a login or register request from a client.  
It indicates the login status after login/register.  

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - Unsigned 8 bits integer : Boolean successful indicator.  
>    - Only if False:  
>      - String: The reason for the unsuccess login or register.  

The server MUST NOT give a reason if the login or register is successful.  
The reason CAN be as precise as possible.  

### RCON Request

This packet MUST:  
- Be sent over TCP.  
- Be sent by a rcon to the server.  

This packet serves to send RCON commands to the server.

Some RCON commands have a target.  
If a RCON command does not have one, the RCON MUST NOT send a target string to the server.

There are 6 RCON commands:  
- List: Lists the players connected.  
- Kick (target): Kick the target.  
- Ban (target): Ban the target.  
- Unban (target): Unban the target.  
- Banlist: List all banned players.  
- SetAdmin (target): Set the target to the ADMIN state.  

RCON uses a passkey to allow only authorized access.  
If the passkey given is incorrect, the server SHOULD discard the packet.  
The server CAN, in this case, send a RCON Response with an error message.  

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - String: The RCON Passkey.  
>  - Unsigned 8 bits integer: The RCON command type.  
>    - 0: List  
>    - 1: Kick  
>    - 2: Ban  
>    - 3: Unban  
>    - 4: Banlist  
>    - 5: SetAdmin  
>  - Only if target needed: String: Target.  

The server SHOULD respond with a RCON Response packet.

### RCON Response

This packet MUST:  
- Be sent over TCP.  
- Be sent by the server to a RCON.  

This packet is a response to a RCON request.

The server CAN write anything in the response. He CAN answer inappropriately.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - A list of:  
>    - String: A line of the RCON Response.  

### Register packet

This packet MUST:  
- Be sent over TCP.  
- Be sent by a client to the server.  

This packet is sent when a client want to create a new account to the server with a username and password.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - String: The player username.  
>  - String: The player password.  

The server SHOULD respond to this packet if the player is not logged in.  

The server MUST NOT respond to or send any other packet if the player is not logged in and authentified, other than the login packet.  

The server SHOULD respond with a Login Response packet.  

### Score packet

This packet is bidirectional.

It SHOULD be interpreted as two different packets, as it is non-mirrorable.

#### Client to server

This packet MUST:  
- Be sent over TCP.  
- Be sent by a client to the server.  

This packet is sent when a client want to get the scoreboard values from the server.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - Unsigned 8 bits integer: Value 0 signifying a request from the client.  

The client MUST NOT send anything more than the byte with this precise value.

#### Server to client

This packet MUST:  
- Be sent over TCP.  
- Be sent from the server to a client.  

This packet is sent when the server answers to a request to get the scoreboard values from the player.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - Unsigned 8 bits integer: Value 1 signifying a response from the server.  
>  - A list of:  
>    - String: The username of the player.  
>    - Signed 32 bits integer: The score.  

The list of scores SHOULD be in decremental order.

The first byte MUST be of that precise value.

### Spawn straight moving entity

This packet MUST:  
- Be sent over TCP.  
- Be sent from the server to a client.  

This packet is sent to all players in a game to describe the position and velocity of new bullets.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - A list of:  
>    - Unsigend 16 bits integer: The entity id.  
>    - Signed 16 bits integer: The x position.  
>    - Signed 16 bits integer: The y position.  
>    - Signed 16 bits integer: The x velocity.  
>    - Signed 16 bits integer: The y velocity.  
>    - Unsigned 8 bits integer: The hitbox width.  
>    - Unsigned 8 bits integer: The hitbox height.  
>    - Unsigned 32 bits integer: The time in ms since the start of the game at the spawn of the bullet.  

### Text chat string

This packet is bidirectional.

This packet MUST:  
- Be sent over TCP.  

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - String: The text message  

The client SHOULD send this packet to the server when he wants to talk in the chat of a lobby. The message SHOULD be contained in the "message" part.

The server SHOULD send this packet to all clients in the lobby when he receives a new message from that lobby. The message SHOULD be contained in the "message" part.  
The server CAN prefix the message with the name of the player who sent the initial message, inside the "message" part of the packet.

### Time now

This packet MUST:  
- Be sent over UDP.  
- Be sent from the server to every client in a game.  

This packet SHOULD be sent every tick from the server to every in-game client, to syncronize the client with the server time.

The time sent MUST be the time spent from the start of the game in milliseconds.

This packet MUST have the following data:  
- Index:  
- Data description:  
>  - Unsigned 32 bits integer: The time data  

# Game logic

The game logic MUST be defined solely by the server.
The client SHOULD not have decisive power except from their inputs.
Rendering decisions CAN be made by the client, but the impact MUST remain only on rendering.

# IANA Considerations {#IANA}

This memo includes no request to IANA.


# Security Considerations {#Security}

This document should not affect the security of the Internet.

--- back
