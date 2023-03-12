# tcpserver
TCP/IP server using socket programming

## TCP Server Properties

- On starting, server must **listen** on a user configured IP-Address and Port Number
- Server must be available to **accept** new connection requests from new clients
- Server should be able to handle multiple client's connections **simultaneously**. This can be accomplished through multi-threading, multi-processing, or multiplexing.
- Server must handle both **connection** and **disconnection**
- Server must be able to **shut down gracefully**. This includes disconnecting all clients connections, freeing up all resources before terminating the process.
- Server must be optimized to service **maximum clients** and with as much high availability as possible. 
- Server must be configurable to abide by certain rules. 1) Accept no more new connections. 2) Stop listening to all or particular clients

## TCP Server Architecture

### Server Controller

- Invoked by AppIn Thread / Service Threads
- Set of APIs to manage service operations

### Connection Acceptor

- Responsible for accepting new connection requests from clients. (TCP Handshake)
- A thread

### Client DB Manager

- Responsible for storing all connected clients
- A data structure

### Client Data Request Service

- Responsible for communicating with connected clients
- Maintinas one or more copy of all connected clients
- A thread + data structure
