#ifndef __CLIENTSERVICEMANAGER__
#define __CLIENTSERVICEMANAGER__

#include <vector>

class ServerController;
class TcpClient;
class ClientServiceManager
{

private:
    ServerController *ctrlr;
    std::vector<HANDLE> clientThreads;
    HANDLE clientMutex;

public:
    ClientServiceManager(ServerController *);
    ~ClientServiceManager();

    void AddNewClientThread(TcpClient *client);
    void StopAllClientThreads();

    static DWORD WINAPI ListenClientThread(LPVOID param);
};

#endif