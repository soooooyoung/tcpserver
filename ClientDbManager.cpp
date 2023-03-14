#include "ServerController.h"
#include "ClientDbManager.h"

ClientDbManager::ClientDbManager(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
    // Initialize critical section for db
    InitializeCriticalSection(&this->cs);
};

ClientDbManager::~ClientDbManager()
{
}

void ClientDbManager::AddClient(SOCKET client)
{
    // Only add one at a time
    if (TryEnterCriticalSection(&this->cs))
    {
        this->client_db.push_back(client);
        LeaveCriticalSection(&this->cs);
    }
    else
    {
        // handle fail case
    }
}

void ClientDbManager::RemoveClient(SOCKET client)
{
    // Removing client uses erase instead of remove because remove doesn't actually delete elements from the container but only shunts non-deleted elements forwards on top of deleted elements.

    for (auto i = this->client_db.begin(); i != this->client_db.end(); i++)
    {
        if (*i == client)
        {
            this->client_db.erase(i);
            break;
        }
    }
}