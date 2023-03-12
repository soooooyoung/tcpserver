#ifndef __CLIENTDBMANAGER__
#define __CLIENTDBMANAGER__

#include <list>

class Client;
class ServerController;

class ClientDbManager
{
private:
    std::list<Client *> client_db;

public:
    ServerController *ctrlr;
    ClientDbManager(ServerController *);
    ~ClientDbManager();
};

#endif