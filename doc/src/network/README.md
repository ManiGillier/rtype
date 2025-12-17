Network Documentation (a.k.a RéseauType)
====

# Summary

RéseauType is the network library used by both the client and the server, written in C++.

Being developed by our own, it provides a high abstraction of common network utils, and makes communication easy and reliable.
RéseauType allows server-client communication by Packet. 
Packets are defined inside the library, and are shared by both the server and client, in order for them to be synchronised.
Developers, who wish to use this library, can add any sort of datas to packets (*).
Every sent packet is being serialised, and transmited in binary. Those packets can either be transmitted through UDP, or TCP, depending on the implemented type of packet.
RéseauType supports multi-threading, and such without having a timeout on `poll` (unnecessary loops).
RéseauType sockets are non-blocking.
RéseauType, with its own Client and Server implementation, is able to match a TCP Client to an UDP Client, and recognise them as a single entity and same entity. This demonstrate RéseauType's high network abstraction.
RéseauType comes with its own logging packet system, logging every received and sent packet. Those can be toggled by setting `Logger:shouldLog` to `true`

(*): except strings, those will be available in a future soon-to-be update.

# Architecture

RéseauType is composed of five parts:
- [Packets](#packets)
  Packets are the data being sent from the server to the clients and vice-versa. Serialised in binary, those can be sent either via TCP or UDP.
- [The Server](#the-server)  
  Creates & starts a RéseauType server (TCP/UDP) that can automatically write, receive, and execute packets.
- [The Client](#the-client)  
  Creates a client to connect to a RéseauType server (TCP/UDP). It can send, receive, and execute incoming packets from the server.
- [PollManager](#poll-manager)
  PollManager is being used by both the client and server. It is a generic part of RéseauType, which allows to accept connections, read packets, send packets, and handle disconnections.
- [Packet Executors](#packet-executors)
  RéseauType's Packet Executors allow you to run specific code when receiving a particular packet type.
  These can be added to both the `Client` or the `Server`.

## Packets

A packet is a serialisable data structure that can be sent between the client and the server using either TCP or UDP.
Each packet has an ID, is fixed sized, and withholds datas.
A packet does not have a direction, and can be sent by both the server and the client.
The server and the client needs to handle individually their own behavior on receiving a packet using [Packet Executors](#packet-executors)

### Developer's Packet Definition (How to create your own packet)

Each created packet must implement the `Packet` class.

#### ID

First and foremost, a packet needs a unique ID, which cannot exceed the length of a `uint8_t`.
This ID must be set using the herited `Packet` constructor.

```cpp
class ExamplePacket : public Packet {
public:
   ExamplePacket(uint32_t uuid=0) : Packet(PacketId::S_AUTHENTICATION_PACKET) {
        this->uuid = uuid;
    }
};
```

**/!\:** DO NOT USE A SAME ID FOR TWO PACKETS, IT IS AN UNDEFINED BEHAVIOR.
You are free to set a custom constructor for each of your packets. However, you **MUST** ensure your packet can be instantiated without any constructor arguments.

#### Serialisation & Unserialisation

A packet is supposed to send one or multiple datas as a single packet. Therefore, you **NEED** to implement the two following methods:

```cpp
void serialize() {
   /* Serialisation code goes here */
}

void unserialize() {
   /* Unerialisation code goes here */
}
```

`serialize()` is the function called to **send the packet**.
On the other hand, `unserialize` is the function being called to turn a `serialised` binary data into the original `Packet`

If the packet had to send in order:
- An integer, called `meow`.
- A double, called `woof`
- Yet another integer, called `uwu`

This is how the `serialize()` function **MUST** be implemented:

```cpp
class ExamplePacket : public Packet {
public:
   /* [...] Constructor with Packet's ID definition */

   void serialize() {
      this->write(meow);
      this->write(woof);
      this->write(uwu);
   }
private:
   int meow = 69;
   double woof = 727.420;
   int uwu = 67;
};
```
The `write` function is a pre-implemented `Packet` method and allows for data types to be easily written.
As a result, our packet upon sending, will send in order the value of `meow`, `woof`, then finally `uwu`.

However, if our packet can be sent, it still can not be converted back into our original packet as we did not implement the `unserialise()` method.

This is how the `unserialise()` function **MUST** be implemented:

```cpp
class ExamplePacket : public Packet {
public:
   /* [...] Constructor with Packet's ID definition */

   void serialize() {
      this->write(meow);
      this->write(woof);
      this->write(uwu);
   }

   void unserialize() {
      this->read(meow);
      this->read(woof);
      this->read(uwu);
   }
private:
   int meow = 69;
   double woof = 727.420;
   int uwu = 67;
};
```

The `read` function is a pre-implemented `Packet` method and allows for data types to be easily read.
As a result, our packet upon receiving, will read in order the value of `meow`, `woof`, then finally `uwu`, which **MUST** be in the same order that they were **serialized**.
`meow`, `woof` and `uwu`'s value will then be set to their corresponding received values.

#### Size

This is one of the two's biggest RéseauType's flaw, and will be updated very soon.
Each packet must declare its data size manually in a `getSize() const` function

If we had to take our previous example, its size would be `sizeof(int) + sizeof(double) + sizeof(int)` which is `sizeof(int) * 2 + sizeof(double)`

Thus, our packet `getSize()` function would have to be implemented as:

```cpp
int getSize() const {
   return (int) sizeof(int) * 2 + sizeof(double);
}
```

#### Name

This only serves for the `Logger` and as an `identifier` for the user. Each packet must specify its packet name by implementing the following method:

```cpp
const std::string getName() {
   return "ExamplePacket";
}
```

#### Mode

This indicates if the packet should be sent using `TCP` or `UDP` to the target.

```cpp
enum PacketMode getMode() const {
   return PacketMode::TCP;
}
```

or

```cpp
enum PacketMode getMode() const {
   return PacketMode::UDP;
}
```

#### Display

This is also something that needs to change and will be soon discarded.
Each packet needs to implement a `display` method and displays all of its value inside for the logger to display them.

If we had to take our `ExamplePacket`, this would be a way to implement that method:

```cpp
void display() {
   std::cout << "meow=" << this->meow << ", woof=" << this->woof << ", uwu=" << this->uwu;
}
```

which would print all of the received values.


#### Clone

This is a repetitive method that should be implemented in every packet as a way for the user to be able to clone a packet if needed.

```cpp
std::shared_ptr<Packet> clone() const {
   return make_copy(ExamplePacket);
}
```

simply return `make_copy` and use as a parameter the `class name` of the `Packet`.

### Packet's Registering

After implementing your own packet, you will need to **register** your packet.
For doing such process, you will need to add it to the `PacketManager` class.
This will register the packet in both the client and server, and will be able to be used.
On the `PacketManager`'s `registerPackets` method, simply add a line

```cpp
this->packets.push_back(std::make_shared<ExamplePacket>());
```

And our packet can now be used by the server and client easily !

## The Server

The Server is RéseauType's core component that handles both TCP and UDP connections. 
It manages client connections, receives, sends packets, and can execute packet handlers automatically.

### Server's Definition

You need to create your own server by implementing the Server class, and the three following functions:

```cpp
virtual std::shared_ptr<IPollable> createClient(int fd) = 0;
virtual void onClientConnect(std::shared_ptr<IPollable> client) = 0;
virtual void onClientDisconnect(std::shared_ptr<IPollable> client) = 0;
```

- `onClientConnect` will be invoked when a client connects to the server.
- `onClientDisconnect` will be invoked when a client disconnects from the server.
- `createClient` is the way you want clients to be created (if you wish to use a custom class).
However, it is best if it implements ServerClient rather than IPollable (which itself already implements IPollable and does more things)

If you do not wish to create your own Server class and make it implement `Server` class, you can use the default `CustomServer` on the library, which is defined the following way:

```cpp
class CustomServer : public Server {
    public:
        CustomServer(int port) : Server(port) {
            return;
        }

        std::shared_ptr<IPollable> createClient(int fd) {
            return std::make_shared<ServerClient>(fd, *this);
        }

        void onClientConnect(std::shared_ptr<IPollable> client) {
            LOG("Client [" << client->getFileDescriptor() << "] connected !");
        }

        void onClientDisconnect(std::shared_ptr<IPollable> client) {
            LOG("Client [" << client->getFileDescriptor() << "] disconnected !");
        }
};
```

### Server's methods

#### up()

Starts the server on the specified port. Creates both TCP and UDP sockets, and begins listening for connections.
Returns `true` if the server started successfully, `false` otherwise.

#### down()

Stops the server. Shuts down both TCP and UDP sockets, clears all connections, and removes all packet executors.
Returns `true` if the server stopped successfully, `false` otherwise.

#### isUp()

Returns `true` if the server is currently running, `false` otherwise.

#### loop()

Main server loop that handles all network operations:
- Sends UDP packets
- Polls for socket events
- Handles client disconnections
- Executes received packets

This method **MUST** be called repeatedly while the server is running.

#### getPacketListener()

Returns the server's packet listener, which allows you to add packet executors for handling received packets.

#### getPollManager()

Returns the server's poll manager, which handles all socket polling and connection management.

#### getMaxConnections()

Returns the maximum number of simultaneous connections the server can handle.

### Server's Client

A connected client is a `Pollable`.
Although, a `Pollable` is not necessarily a `client`

The base pollable class for server clients is `ServerClient`.
This class provides a `sendPacket()` method to send a packet to a connected client.

### Server's UDP Authentication

When a client connects to the server via TCP, the server generates a unique UUID and sends it to the client using a `SAuthentificationPacket`.

The server then waits to receive this UUID back from the client via UDP through a `CAuthentificationPacket`.

Once received, the server binds the TCP and UDP connections together, recognizing them as a single client entity.
After successful authentication, the server sends an `AuthentifiedPacket` to the client on the TCP connection to confirm the authentication was successful.
Only then can the client and server exchange UDP packets.

## The Client

The Client is RéseauType's component that connects to a server using both TCP and UDP.
It handles connection establishment, packet sending and receiving, and executes packet handlers automatically.

### Client's methods

#### connect()

Connects the client to the server at the specified IP and port.
Creates both TCP and UDP sockets and establishes connections
Returns `true` if the connection was successful, `false` otherwise.

#### disconnect()
Disconnects the client from the server.
Closes both TCP and UDP sockets
Clears all connections, and removes all packet executors. 
Returns `true` if the disconnection was successful.

#### isConnected()

Returns `true` if the client is currently connected to the server, `false` otherwise.

#### sendPacket()

Sends a packet to the server.
The packet will be sent through TCP or UDP depending on its mode.

#### loop()

Main client loop that handles all network operations:
- Sends UDP packets
- Polls for socket events
- Executes received packets.

This method **MUST** be called repeatedly while the client is connected.

#### getPacketListener()

Returns the client's packet listener, which allows you to add packet executors for handling received packets.

#### getPollManager()

Returns the client's poll manager, which handles all socket polling and connection management.

#### getIp()

Returns the server's IP address the client is connected to.

#### getPort()

Returns the server's port the client is connected to.

#### isAuthentified()

Returns `true` if the client has been authenticated by the server, `false` otherwise.

#### getUUID()

Returns the unique identifier assigned to this client by the server.

### Client's UDP Authentication

When the client connects to the server via TCP, it receives a `SAuthentificationPacket` which contains an UUID. 
The client sends this UUID to the server via UDP using a `CAuthentificationPacket`.

This process binds the TCP and UDP connections together, allowing the server to recognize them as a single client.

If this authentication fails, the client cannot send or receive any UDP packets.
The client will retry sending the `CAuthentificationPacket` up to 10 times. 
The client only knows if it has been successfully authenticated when it receives an `AuthentifiedPacket` from the server on the TCP end.

## PollManager

The PollManager is RéseauType's component that handles socket polling and connection management.
It is used by both the server and the client to manage all active connections and poll for network events.

Overexplaining this component is not useful, as it is made to never be **edited**.

### PollManager's methods

#### addPollable()

Adds a new pollable connection to the manager.

#### removePollable()

Removes a pollable connection by its file descriptor.
Closes the socket and returns the removed pollable.

#### removePollables()

Removes multiple pollable connections at once.
Returns a vector of the removed pollables.

#### updateFlags()

Updates the polling flags for a specific file descriptor.

#### getConnectionCount()

Returns the total number of active connections.
(This sadly includes more than the number of connected clients to the server and needs to be changed).

#### getPool()

Returns all active the active pollable connections.

#### getPollableByAddress()

Returns a pollable connection by its network address.
Returns nullptr if not found.

#### pollSockets()

Polls all registered sockets for events.
Takes an optional timeout in milliseconds.
Returns a vector of pollables that disconnected during the poll.

#### wakeUp()

Wakes up the poll if it is currently blocking (useful for multi-threading purposes).

#### clear()

Removes all pollables and closes all sockets.
Called when shutting down either the server or client.

## Packet Executors

Packet Executors allow you to run specific code when receiving a particular packet type.
They are event handlers that get triggered automatically when a packet is received by the server or client.

In order to explain them properly, we will take as an example the following case:
We want to print on the console `"meow !!! :3 >\\< {uwu}"` if `ExamplePacket` was being sent
`{uwu}` being the uwu value of the `ExamplePacket` which can be retrieved using a `int getUwU() const;` method.

### Packet Executor's Server Implementation

Each Server's executor must implement the `PacketExecutorImplServer` class

`PacketExecutorImplServer` class is a template class that takes two dynamic types : The first one being the type of packet of the executor (in our case, `ExamplePacket`) and the second being the type of the client that will send us the packet (in our case `ServerClient` (which is the default))

```cpp
class AwesomeExamplePacketExecutor : public PacketExecutorImplServer<ExamplePacket, ServerClient> {
   /* Code.... */
};
```

A class that implements `PacketExecutorImplServer` must define two methods : an `execute(...)` and a `getPacketId()`

`getPacketId()` is the ID of the packet that will be catched (`ExamplePacket` in our example)
`execute(....)` is the method that will be called when receiving an `ExamplePacket`

Those two functions when implemented looks like the following:


```cpp
class AwesomeExamplePacketExecutor : public PacketExecutorImplServer<ExamplePacket, ServerClient> {
   bool execute(Server &srv, std::shared_ptr<ServerClient> con, std::shared_ptr<ExamplePacket> packet) {
      /* Code */
      return true;
   }

    int getPacketId() const {
        return PacketId::NEW_PLAYER;
    }
};
```

The `execute` function takes:
- As a first parameter, the `Server`.
- As a second parameter, a `shared_ptr` of the specified Client Class.
- And at last, a `shared_ptr` of the received packet

The return type of `execute` determines whether the client should be disconnected or no.

As `execute` is the function being called when an `ExamplePacket` is being received, we only need to write what we had to write on the console the following way:

```cpp
bool execute(Server &srv, std::shared_ptr<ServerClient> con, std::shared_ptr<ExamplePacket> packet) {
   (void) srv;
   (void) con;
   std::cout << "meow !!! :3 >\\< " << packet.getUwU() << std::endl;
   return true;
}
```

### Packet Executor's Client Implementation

Each Client's executor must implement the `PacketExecutorImplClient` class

`PacketExecutorImplClient` class is a template class that takes two dynamic types : The first one being the type of packet of the executor (in our case, `ExamplePacket`) and the second being the type of the client that will send us the packet (which **MUST** always be ClientPollable)
P.S: This second forced parameter will be removed in an soon upcoming update.

```cpp
class AwesomeExamplePacketExecutor : public PacketExecutorImplClient<ExamplePacket, ClientPollable> {
   /* Code.... */
};
```

A class that implements `PacketExecutorImplClient` must define two methods : an `execute(...)` and a `getPacketId()`

`getPacketId()` is the ID of the packet that will be catched (`ExamplePacket` in our example)
`execute(....)` is the method that will be called when receiving an `ExamplePacket`

Those two functions when implemented looks like the following:


```cpp
class AwesomeExamplePacketExecutor : public PacketExecutorImplClient<ExamplePacket, ClientPollable> {
   bool execute(Client &cl, std::shared_ptr<ClientPollable> con, std::shared_ptr<ExamplePacket> packet) {
      /* Code */
      return true;
   }

    int getPacketId() const {
        return PacketId::NEW_PLAYER;
    }
};
```

The `execute` function takes:
- As a first parameter, the `Client`.
- As a second parameter, a `shared_ptr` of the specified Client Class.
- And at last, a `shared_ptr` of the received packet

The return type of `execute` determines whether the client should be disconnected or no.

As `execute` is the function being called when an `ExamplePacket` is being received, we only need to write what we had to write on the console the following way:

```cpp
bool execute(Server &srv, std::shared_ptr<ServerClient> con, std::shared_ptr<ExamplePacket> packet) {
   (void) srv;
   (void) con;
   std::cout << "meow !!! :3 >\\< " << packet.getUwU() << std::endl;
   return true;
}
```
