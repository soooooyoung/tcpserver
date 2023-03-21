#ifndef __CLIENTDBMANAGER__
#define __CLIENTDBMANAGER__

#include <list>

class ServerController;
class TcpClient;

class ClientDbManager
{
private:
    std::list<TcpClient *> client_db;
    HANDLE dbMutex;
    int max_clients = 10;

public:
    ServerController *ctrlr;
    ClientDbManager(ServerController *);
    ~ClientDbManager();

    void AddClient(TcpClient *client);
    void RemoveClient(TcpClient *client);

    bool IsMaxed();
};

#endif