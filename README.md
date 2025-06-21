<div align="center">
  <h1>42 - Ft_Irc</h1>
<p align="center">
The ft_irc project aims to help students gain proficiency in network programming, socket usage, and multi-client management. By developing a server that complies with the IRC protocol, students learn the fundamentals of real-time communication systems and gain experience in building an efficient and robust architecture using C++.
</p>
  <img src="https://github.com/deryaxacar/42-Ft_irc/blob/main/irc-logo.png" alt="irc" height="150" width="150">
</div>

---

## Table of Contents 📚

* [What is an Endpoint?](#what-is-an-endpoint)
* [What is a Socket?](#what-is-a-socket)
* [Network and Communication Fundamentals](#network-and-communication-fundamentals)
* [Concurrency and Scalability](#concurrency-and-scalability)
* [Application Architecture and Logic](#application-architecture-and-logic)
* [Supported IRC Commands](#supported-irc-commands)
* [Testing the Server](#testing-the-server)
* [Error Handling Strategy](#error-handling-strategy)
* [Project Structure](#project-structure)
* [Future Improvements](#future-improvements)

---

## What is an Endpoint?

In software development, especially in the context of web services (APIs), an **endpoint** refers to a specific URL where communication occurs between a client and a server. Each endpoint performs a specific function.

🔧 **Technically speaking:**  
Each endpoint is defined by a specific HTTP route and usually paired with an HTTP method (GET, POST, PUT, DELETE).

**Example:**

| Action             | Endpoint              | URL                    | Method |
|--------------------|-----------------------|------------------------|--------|
| List Products       | GET /api/products/    | `/api/products/`       | GET    |
| Product Detail      | GET /api/products/ID  | `/api/products/123/`   | GET    |
| Add New Product     | POST /api/products/   | `/api/products/`       | POST   |
| Update Product      | PUT /api/products/ID  | `/api/products/123/`   | PUT    |
| Delete Product      | DELETE /api/products/ID | `/api/products/123/` | DELETE |

🧠 **In Simple Terms:**  
Endpoints are like the buttons on a website. For example:

- If there's a "Sign Up" button: there's an endpoint like `/api/register/`
- If there's an "Add to Cart" button: it corresponds to `/api/cart/add/`

📦 **For Backend Developers:**  
An endpoint typically includes:

- **URL:** `/api/user/login/`
- **HTTP Method:** `POST`
- **Request Data:** JSON object with user credentials
- **Response Data:** Success or error message (and often a token)

---

## What is a Socket?

A **socket** is a communication endpoint used for exchanging data over a network between two devices (typically computers).  
It allows one computer to connect and talk to another over the internet or a local network.

💡 **Technically:**  
A socket is defined by:

- **IP Address** (which computer?)
- **Port Number** (which application?)  
So, a socket = (IP address + Port)

🧱 **How Sockets Work:**

1. The **server** starts listening on a specific port (e.g., `127.0.0.1:5000`)
2. The **client** tries to connect to that IP and port
3. Once connected, data is exchanged between the two
4. After the communication ends, the socket is closed

🔁 **Types of Sockets:**

| Type       | Description                                              |
|------------|----------------------------------------------------------|
| TCP Socket | Reliable, ordered communication (e.g., HTTP, FTP)        |
| UDP Socket | Fast but unreliable (e.g., video games, VoIP)            |

> Since the IRC protocol requires user sessions and reliable message delivery, **TCP** sockets are used.

---

## Network and Communication Fundamentals

### 🧭 Client-Server Architecture

This is a basic communication model where a central server provides services to multiple clients. In IRC systems, all message traffic is routed through the server.

### 🌐 TCP/IP Protocol Suite

* **TCP (Transmission Control Protocol)** is used in IRC systems for reliable, ordered, and lossless data transmission.
* It's connection-oriented and ensures data integrity, making it suitable for real-time chat applications.

### 🧵 Socket Programming Concepts

* A socket is an endpoint defined by an IP address and a port number.
* Basic operations:

  * Create a socket (`socket()`)
  * Bind to an address (`bind()`)
  * Listen for connections (`listen()`)
  * Accept new connections (`accept()`)
  * Send/receive data (`send()`, `recv()`)

### 📦 Data Serialization & Parsing

IRC is a **text-based protocol**. Messages:

* Are serialized into bytes before transmission,
* Then parsed and interpreted by the server.
* Example: `PRIVMSG #channel :Hello there!` sends a message to all users in `#channel`.

---

## Concurrency and Scalability

A real IRC server must handle hundreds or thousands of clients simultaneously and efficiently.

### ⚙️ I/O Multiplexing

* **Goal**: Handle multiple connections in a single thread, avoiding the overhead of spawning one thread per client.
* **Techniques**:

  * `select`
  * `poll`
  * `epoll` (Linux)
  * `kqueue` (macOS/BSD)

> This project typically uses `poll()` for portability and simplicity.

### 🔁 Event Loop

* The server runs a continuous loop monitoring for events (incoming data, disconnection, etc.).
* When an event occurs, the appropriate handler function is executed.
* This enables a reactive and modular design.

### 🚫 Non-blocking I/O

* Functions like `recv()` or `accept()` return immediately if there's no data.
* This ensures the server can continue processing other clients without being blocked.

---

## Application Architecture and Logic

### 🔄 State Machine Management

* Each client connection has a **state**:

  * e.g., Unregistered → Registered → Joined Channel
* Example: After `NICK` and `USER` commands, the user becomes "registered".

### 📜 Protocol Implementation

* The server must conform to **IRC RFC 2812** standards.
* This includes handling valid commands, parameter counts, reply formats, and numeric codes.
* Example:

  * `:server 001 nick :Welcome to the Internet Relay Network`

### 🧑‍⚖️ Access Control & Authorization

* Users can have different permissions:

  * Channel operators can kick, ban, or change topic.
* The server validates permissions before executing privileged actions.

### 🛄 Message Queuing & Routing

* The server determines how to route messages:

  * To another user (private message)
  * To all users in a channel
* This may involve message queuing or direct delivery depending on the design.

---

## Supported IRC Commands 📟

The following commands are implemented in compliance with the IRC protocol (RFC 2812). Each command follows strict syntax, validation, and state logic.

| Command   | Description                                                     |
| --------- | --------------------------------------------------------------- |
| `NICK`    | Sets or changes the nickname of a user                          |
| `USER`    | Registers a new user with username and real name                |
| `JOIN`    | Joins one or more channels (creates channel if not exists)      |
| `PART`    | Leaves a channel                                                |
| `PRIVMSG` | Sends a private message to a user or channel                    |
| `NOTICE`  | Sends a non-reply message (no automatic replies like `PRIVMSG`) |
| `PING`    | Ping request to check connection health                         |
| `PONG`    | Ping response                                                   |
| `QUIT`    | Disconnects the user with an optional message                   |
| `MODE`    | Changes or queries channel/user modes                           |
| `TOPIC`   | Gets or sets the topic of a channel                             |
| `KICK`    | Removes a user from a channel (requires operator status)        |

---

## Testing the Server 🔍

**Netcat:**
Netcat (nc) is a lightweight, command-line based networking tool used for testing network connections, transferring data, and listening on ports. It can act as both a client and a server.

🔧 What is it used for?

  - Establishing TCP or UDP connections
  - Listening on a port (acting like a server)
  - Transferring files
  - Sending and receiving data over sockets to test network applications

### 🧪 Netcat Example

```bash
$ nc 127.0.0.1 6667
NICK mynick
USER mynick 0 * :Real Name
JOIN #test
PRIVMSG #test :Hello everyone!
```

Expected response:

```
:ircserv 001 mynick :Welcome to the IRC server!
```

### 🤖 Automated Scripts

You can also write automated test scripts using Python (e.g., with `socket` and `unittest`) to simulate multiple clients joining, messaging, and disconnecting.

---

## Error Handling Strategy ⚠️

The server gracefully handles and responds to user mistakes or protocol violations:

* ❌ Invalid command format → numeric error codes
* ❌ Nickname already in use → `433 ERR_NICKNAMEINUSE`
* ❌ Not registered → `451 ERR_NOTREGISTERED`
* ❌ Trying to join without USER/NICK → rejected with reason

All socket operations are wrapped in exception-safe logic. Disconnected clients are cleaned up and removed from internal structures (`pollfd`, nickmap, channels, etc.).

---

## Project Structure 📁

```
ft_irc/
│
├── Commands/
│   ├── Invite.cpp / Invite.hpp
│   ├── Join.cpp / Join.hpp
│   ├── Kick.cpp / Kick.hpp
│   ├── Mode.cpp / Mode.hpp
│   ├── Nick.cpp / Nick.hpp
│   ├── Part.cpp / Part.hpp
│   ├── Pass.cpp / Pass.hpp
│   ├── Privmsg.cpp / Privmsg.hpp
│   ├── Quit.cpp / Quit.hpp
│   ├── Topic.cpp / Topic.hpp
│   └── User.cpp / User.hpp
│
├── Modes/
│   ├── Invite.cpp / Invite.hpp
│   ├── Key.cpp / Key.hpp
│   ├── Limit.cpp / Limit.hpp
│   ├── Modes.cpp / Modes.hpp
│   ├── Op.cpp / Op.hpp
│   └── Topic.cpp / Topic.hpp
│
├── Commands.cpp / Commands.hpp
├── Server.cpp / Server.hpp
├── main.cpp
├── Makefile
├── README.md
```

---
