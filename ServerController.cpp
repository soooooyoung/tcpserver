#include "ServerController.h"

ServerController::ServerController(std::string ip_addr, uint16_t port_no, std::string name)
{

    // c_str
    // Return const pointer to null-terminated contents. This is a handle to internal data.

    // NOTE: this** to reference the current object instance's member variables when you want to differentiate between a member variable and a local variable or parameter that has the same name.
    // using this-> in a .cpp file can help make code more clear and readable, especially in cases where you have a large and complex class with many member variables and functions.

    this->ip_addr = convert_ip_p_to_n(ip_addr.c_str());
    this->port_no = port_no;
    this->name = name;

    // Initialize Services
    this->conn_acc = new ConnectionAcceptor(this);
    this->client_db_mgr = new ClientDbManager(this);
    this->client_svc_mgr = new ClientServiceManager(this);

    // Winsock Initialization
    this->conn_acc->Init();
}

ServerController::~ServerController()
{
}

void ServerController::Start()
{
    // Start Service Threads
    this->conn_acc->StartConnectionAcceptorThread();

    printf("Server started: [%s, %d]\nOk.\n", convert_ip_n_to_p(this->ip_addr, 0), this->port_no);
}

void ServerController::ProcessAddClient(TcpClient *client)
{
    // TODO: Multithreading for larger traffic
    this->client_db_mgr->AddClient(client);
    // TODO: Start Listening to TcpClient with TcpClient Service Manager
    this->client_svc_mgr->AddNewClientThread(client);
}

void ServerController::ProcessRemoveClient(TcpClient *client)
{
    this->client_db_mgr->RemoveClient(client);
}