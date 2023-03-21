#ifndef __CLIENTSERVICEMANAGER__
#define __CLIENTSERVICEMANAGER__

#include <map>

class ServerController;
class TcpClient;
class ClientServiceManager
{

private:
    ServerController *ctrlr;
    // std::map that maps a TcpClient* to a HANDLE.
    std::map<TcpClient *, HANDLE> clientThreads;
    HANDLE clientMutex;

public:
    ClientServiceManager(ServerController *);
    ~ClientServiceManager();

    void AddNewClientThread(TcpClient *client);
    void StopClientThread(TcpClient *client);
    void StopAllClientThreads();

    static DWORD WINAPI ListenClientThread(LPVOID param);
};

#endif