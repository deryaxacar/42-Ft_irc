<div align="center">
  <h1>42 - Ft_Irc</h1>
<p align="center">
The ft_irc project aims to help students gain proficiency in network programming, socket usage, and multi-client management. By developing a server that complies with the IRC protocol, students learn the fundamentals of real-time communication systems and gain experience in building an efficient and robust architecture using C++.
</p>
  <img src="https://github.com/deryaxacar/42-Ft_irc/blob/main/irc-logo.png" alt="irc" height="150" width="150">
</div>

---

## Table of Contents 📚

- [What is an Endpoint?](#what-is-an-endpoint)
- [What is a Socket?](#what-is-a-socket)

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
