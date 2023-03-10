#ifndef __CLIENTDBMANAGER__
#define __CLIENTDBMANAGER__

#include <list>

class Client;
class ServerController;

class ClientDbManager
{
private:
    std::list<SOCKET> client_db;
    SRWLOCK lock;

public:
    ServerController *ctrlr;
    ClientDbManager(ServerController *);
    ~ClientDbManager();

    void AddClient(SOCKET client);
    void RemoveClient(SOCKET client);
};

#endif