# Technical choices

## Chosen Language

We chose C++ because for a multiplayer game, we needed very good performance.
The low-level control over memory allows us to optimize our game as much as possible.

Compared to Java, C# or Zig, we lose a bit of development time but it's worth it thanks to the time we gain on execution speed and resource control.

## Chosen Graphical Library

For our graphical library, we chose [Raylib](https://www.raylib.com/).

It offers multiple advantages compared to other libraries:  
1. **SFML**
   - The raylib offers a higher level management of operations, with a lot of underlying global variables, offering nice and straightforward function calls.
   - The SFML, although having the nice advantage of being adapted to Object Oriented Programming, tends to be more difficult to use because of the need to keep track of all variables created. It may be preferable to have the variables in hand, but in our case with the ECS and state machine, we chose to have hidden variables.
2. **SDL**
   - The SDL is a low-level graphical library. We did not wanted to go too deep in that rabbit hole, and we stuck to the Raylib, offering higher level implementation.
3. **Direct OpenGl calls**
   - I'm not even gonna explain why we did not chose that path.

The Raylib is a really good graphical library, but we may encounter some problem with it, namely : 
- It is not really adapted to Object Oriented Programming.  
Indeed, it is not at all constructed with classes, and rely solely on direct calls to global funtions

## Algorithms and Data Structures

### ECS (Entity Component System)

The ECS was a bit of an unusual choice but logical for us.
Compared to a classic object-oriented architecture with inheritance, the ECS organizes data contiguously in memory, which optimizes the CPU cache on both server and client side.

Concretely, instead of having "Player" or "Enemy" objects that are subclasses, we group all components of the same type together. 

Result: when we update positions or Health, the iteration is much faster. 
For a game with many simultaneous entities, it makes a huge difference.

### RéseauType (custom)

This is our most strongest yet assumed choice. Instead of using an existing cross-platform library, we developed our own network library. Why?

- We know how it works. If a bug appears, we can fix it ourselves without depending on an external community.
- Generic libraries handle many cases we don't need. Our protocol is tailored for our needs - position packets, input packets, etc.
- By controlling the protocol, we can implement packets specific to our game, whereas with an existing library we would have had to adapt to its functioning.

The fact that we have our own network library allows us to integrate these checks directly into the protocol rather than adding them on top.

## Storage

RéseauType uses binary serialization for packet transmission.

This section compares different serialization methods.

### Binary Serialization (Our approach)

Binary serialization converts packet data into bytes.

Packets are not stored permanently. They exist only during transmission between client and server.

It is fast and deterministic.

Both the client and server know exactly how to read and write packet data.

There is no parsing overhead, which makes it reliable for real-time communication.

However, changing packet structure requires updating both client and server code.

The binary format is also difficult to debug since it is not human-readable. (Although RéseauType comes with a Logger to make debugging easy !)

### Why RéseauType Uses Binary Serialization

RéseauType prioritizes speed and bandwidth usage

Binary serialization provides the fastest transmission and smallest packet size, which is critical for real-time multiplayer games where latency matters.

JSON or Protocol Buffers are not optimal for real-time games where performance is the priority.

## Security

The only security challenge of the project is dealing with client output and preventing cheating.
Clients can be modified or replaced with malicious programs that send fake data to gain unfair advantages.

### Server Authority

The server has authority on everything. It does not trust the client at any point.

The client only sends its inputs. 

he server calculates the player's position, health, score, and all game state.

The client does not determine its own position or any game logic.

This prevents clients from sending false position data or modifying their own stats.

Even if a cheater modifies their client, they can only send inputs, not results.

### Connection Validation

A client is disconnected when it does not connect properly using the RéseauType Client. 

Although this connection method can be mimicked by a custom client, it does not give any advantage over using the RéseauType Client.

This prevents random programs from spamming the server without proper authentication.

### Packet Validation

Our system can disconnect a user based on the data received in a packet.

An anti-cheat system can easily be implemented by adding packet executors that detect suspicious behavior.

The server kicks off a player when it receives an unknown packet ID. It only accepts registered packets.

### Data Integrity

All packets are serialized in binary with variadic sizes. The server validates packet size before processing. If a packet is malformed, it disconnects the client.

### Further Security Axis

#### DDoS Attacks

RéseauType does not currently implement rate limiting or IP blocking. A malicious client could spam packets to overload the server

Rate limiting can be added to limit the number of packets per second per client.

#### Man-in-the-Middle Attacks

RéseauType does not encrypt packets. An attacker on the same network could intercept and read packets, or modify them in transit

Adding encryption (TLS for TCP, DTLS for UDP) could prevent this and could be added.
