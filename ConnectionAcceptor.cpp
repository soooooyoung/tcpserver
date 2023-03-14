#include "ServerController.h"
#include "ConnectionAcceptor.h"

ConnectionAcceptor::ConnectionAcceptor(ServerController *ctrlr)
{
    // Initialize Window's Socket (Winsock)
    // NOTE: On Windows systems, the core components of the socket come in the form of a dll file. (ws2_32.dll)
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        printf("WSAStartup failed");
        exit(1);
    }
    this->socket_hdl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->socket_hdl == INVALID_SOCKET)
    {
        printf("Failed to create socket.");
        WSACleanup();
        exit(1);
    }

    this->ctrlr = ctrlr;
}

ConnectionAcceptor::~ConnectionAcceptor()
{
    WSACleanup();
}

void ConnectionAcceptor::StartConnectionAcceptorThread()
{
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->ctrlr->port_no);
    server_addr.sin_addr.s_addr = htonl(this->ctrlr->ip_addr);

    // bind socket
    if (bind(this->socket_hdl, (sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Failed to bind socket.");
        closesocket(socket_hdl);
        WSACleanup();
        exit(1);
    }

    // listen on socket
    if (listen(this->socket_hdl, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Failed to listen on socket.");
        closesocket(this->socket_hdl);
        WSACleanup();
        exit(1);
    }

    // TODO: while available, accept client

}
