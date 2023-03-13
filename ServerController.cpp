#include <iostream>
#include <assert.h>
#include "ServerController.h"
#include "ConnectionAcceptor.h"
#include "ClientDbManager.h"
#include "ClientServiceManager.h"
#include "network_utils.h"

ServerController::ServerController(std::string ip_addr, uint16_t port_no, std::string name)
{

    // c_str
    // Return const pointer to null-terminated contents. This is a handle to internal data.
    this->ip_addr = convert_ip_p_to_n(ip_addr.c_str());
    this->port_no = port_no;
    this->name = name;

    // Initialize Services
    this->conn_acc = new ConnectionAcceptor(this);
    this->client_db_mgr = new ClientDbManager(this);
    this->client_svc_mgr = new ClientServiceManager(this);
}

void ServerController::Start()
{
    // Start Service Threads
    this->conn_acc->StartConnectionAcceptorThread();
    this->client_svc_mgr->StartClientServiceManagerThread();
    this->client_db_mgr->StartClientDbManagerThread();

    printf("Server started: [%s, %d]\nOk.\n", convert_ip_n_to_p(this->ip_addr, 0), this->port_no);
}

ServerController::~ServerController()
{
}