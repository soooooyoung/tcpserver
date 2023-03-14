#include "ServerController.h"
#include "ClientDbManager.h"

ClientDbManager::ClientDbManager(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
    // Initialize SRWLock for add/remove client
    InitializeSRWLock(&this->lock);
};

ClientDbManager::~ClientDbManager()
{
}

void ClientDbManager::AddClient(SOCKET client)
{
    // Only add one at a time
    // SRW locks are generally faster than critical sections for uncontended access. This is because SRW locks use spin-waiting instead of context switching when contention is low, which can be more efficient in certain situations.
    AcquireSRWLockExclusive(&this->lock);
    this->client_db.push_back(client);
    ReleaseSRWLockExclusive(&this->lock);
}

void ClientDbManager::RemoveClient(SOCKET client)
{
    // Removing client uses erase instead of remove because remove doesn't actually delete elements from the container but only shunts non-deleted elements forwards on top of deleted elements.
    AcquireSRWLockExclusive(&this->lock);
    for (auto i = this->client_db.begin(); i != this->client_db.end(); i++)
    {
        if (*i == client)
        {
            this->client_db.erase(i);
            break;
        }
    }
    ReleaseSRWLockExclusive(&this->lock);
}