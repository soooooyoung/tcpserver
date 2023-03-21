#include "ServerController.h"
#include "ClientDbManager.h"

ClientDbManager::ClientDbManager(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
    // Initialize Mutex for add/remove client
    this->dbMutex = CreateMutex(NULL, FALSE, NULL);
};

ClientDbManager::~ClientDbManager()
{
    // Client DB is responsible for the memory allocation of TcpClient
    for (auto it = this->client_db.begin(); it != this->client_db.end(); ++it)
    {
        delete *it;
    }

    // Close mutex
    CloseHandle(this->dbMutex);
}

bool ClientDbManager::IsMaxed()
{
    if (this->client_db.size() > this->max_clients)
    {
        return true;
    }
    return false;
}

void ClientDbManager::AddClient(TcpClient *client)
{
    // Only add one at a time
    // SRW locks are generally faster than critical sections for uncontended access. This is because SRW locks use spin-waiting instead of context switching when contention is low, which can be more efficient in certain situations.
    WaitForSingleObject(this->dbMutex, INFINITE);
    this->client_db.push_back(client);
    ReleaseMutex(this->dbMutex);
}

void ClientDbManager::RemoveClient(TcpClient *client)
{
    // Removing client uses erase instead of remove because remove doesn't actually delete elements from the container but only shunts non-deleted elements forwards on top of deleted elements.
    WaitForSingleObject(this->dbMutex, INFINITE);
    for (auto i = this->client_db.begin(); i != this->client_db.end(); i++)
    {
        if (*i == client)
        {
            (*i)->Abort();
            delete *i;
            this->client_db.erase(i);
            break;
        }
    }
    ReleaseMutex(this->dbMutex);
}
