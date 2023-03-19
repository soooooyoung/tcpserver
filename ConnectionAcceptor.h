#ifndef __CONNECTIONACCEPTOR__
#define __CONNECTIONACCEPTOR__

class ServerController;

class TcpClient;
// Represents threads that accept new connections to the server
// ** accept(): When accepting new connection, server needs to create a new socket to handle communication with the client.

// ** File Descriptor: represents open files, sockets, pipes, and other input/output resources in Unix-like operating systems. The file descriptor returned by the `accept()` system call represents the new socket that has been created to handle communication with the client. This file descriptor can be used with other input/output system calls, such as `read()` and `write()`, to read and wrtie data to the client.

// UNIX: The `accept()` system call returns a new file descriptor that can be used to read and write data to the newly established connection.

// WINDOW: The `accept()` returns a new accepted connection as a new socket "handle" that can be used to communicate with the client

class ConnectionAcceptor
{

private:
    ServerController *ctrlr;
    SOCKET socket_hdl;
    HANDLE thread_hdl;
    bool running_flag;

public:
    ConnectionAcceptor(ServerController *);
    ~ConnectionAcceptor();
    void Init();

    void StartConnectionAcceptorThread();
    void StopConnectionAcceptorThread();
    static DWORD WINAPI ConnectionAcceptorThread(LPVOID param);
};

#endif