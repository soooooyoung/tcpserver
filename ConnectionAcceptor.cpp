#include "ServerController.h"
#include "ConnectionAcceptor.h"

ConnectionAcceptor::ConnectionAcceptor(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
}

ConnectionAcceptor::~ConnectionAcceptor()
{
    StopConnectionAcceptorThread();
    closesocket(this->socket_hdl);
    WSACleanup();
}

void ConnectionAcceptor::Init()
{
    // Initialize Window's Socket (Winsock)
    // NOTE: On Windows systems, the core components of the socket come in the form of a dll file. (ws2_32.dll)
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        printf("WSAStartup failed\n");
        // exit(1);
    }
    this->socket_hdl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->socket_hdl == INVALID_SOCKET)
    {
        printf("Failed to create socket.\n");
        WSACleanup();
        // exit(1);
    }

    // server address setting

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->ctrlr->port_no);
    server_addr.sin_addr.s_addr = htonl(this->ctrlr->ip_addr);

    // bind socket
    if (bind(this->socket_hdl, (sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Failed to bind socket.\n");
        closesocket(this->socket_hdl);
        WSACleanup();
        // exit(1);
    }

    // listen on socket
    if (listen(this->socket_hdl, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Failed to listen on socket.\n");
        closesocket(this->socket_hdl);
        WSACleanup();
        // exit(1);
    }
}

void ConnectionAcceptor::StartConnectionAcceptorThread()
{

    this->running_flag = true;
    DWORD threadId;
    this->thread_hdl = CreateThread(NULL, 0, ConnectionAcceptorThread, (LPVOID)this, 0, &threadId);

    printf("Connection Acceptor Thread Started");
}

void ConnectionAcceptor::StopConnectionAcceptorThread()
{
    this->running_flag = false;
    WaitForSingleObject(this->thread_hdl, INFINITE);
    CloseHandle(this->thread_hdl);
    this->thread_hdl = NULL;
}

DWORD WINAPI ConnectionAcceptor::ConnectionAcceptorThread(LPVOID lpParam)
{
    ConnectionAcceptor *acceptor = (ConnectionAcceptor *)lpParam;

    // while available, accept client

    while (acceptor->running_flag)
    {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int comm_sock_fd;

        SOCKET clientSocket = accept(acceptor->socket_hdl, (struct sockaddr *)&client_addr, &addr_len);

        if (clientSocket != INVALID_SOCKET)
        {
            printf("Connection Attempt");
            // Create and Initialize TcpClient
            TcpClient *newClient = new TcpClient(htonl(client_addr.sin_addr.s_addr), htons(client_addr.sin_port));

            newClient->client_socket = clientSocket;
            // Add client information for client db manager and client service manager to process through server controller
            acceptor->ctrlr->ProcessAddClient(newClient);
        }
        else
        {
            printf("Connection Accept Failed");
            closesocket(clientSocket);
        }
    }

    return 0;
}