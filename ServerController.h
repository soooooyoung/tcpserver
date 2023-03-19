#ifndef __SERVERCONTROLLER__
#define __SERVERCONTROLLER__

#include <iostream>
#include <stdint.h>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "ConnectionAcceptor.h"
#include "ClientDbManager.h"
#include "ClientServiceManager.h"
#include "TcpClient.h"
#include "network_utils.h"

class ConnectionAcceptor;
class ClientServiceManager;
class ClientDbManager;
class TcpClient;

class ServerController
{

private:
    ConnectionAcceptor *conn_acc;
    ClientDbManager *client_db_mgr;
    ClientServiceManager *client_svc_mgr;

public:
    ServerController(std::string ip_addr, uint16_t port_no, std::string name);
    ~ServerController();

    void Start();
    void Stop();

    void ProcessAddClient(TcpClient *client);

    void ProcessRemoveClient(TcpClient *client);

    uint32_t ip_addr;
    uint16_t port_no;
    std::string name;
};

#endif