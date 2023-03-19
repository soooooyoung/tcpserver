#ifndef __TCPCLIENT__
#define __TCPCLIENT__

#include <stdint.h>
#include <winsock2.h>

class TcpClient
{

private:
    uint32_t ip_addr;
    uint16_t port_no;

public:
    TcpClient(uint32_t ip_addr, uint16_t port_no);
    ~TcpClient();
    void Abort();
    void Init(SOCKET client_socket);
    SOCKET client_socket;
};

#endif