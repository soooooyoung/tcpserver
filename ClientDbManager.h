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

public:
    ServerController *ctrlr;
    ClientDbManager(ServerController *);
    ~ClientDbManager();

    void AddClient(TcpClient *client);
    void RemoveClient(TcpClient *client);


};

#endif