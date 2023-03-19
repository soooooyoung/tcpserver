#include "TcpClient.h"

TcpClient::TcpClient(uint32_t ip_addr, uint16_t port_no)
{
    this->ip_addr = ip_addr;
    this->port_no = port_no;
}
TcpClient::~TcpClient() {}

void TcpClient::Abort()
{
    if (this->client_socket)
    {
        closesocket(this->client_socket);
        this->client_socket = 0;
    }
}
