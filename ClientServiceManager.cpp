#include "ServerController.h"
#include "ClientServiceManager.h"

ClientServiceManager::ClientServiceManager(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
}

void ClientServiceManager::StartClientServiceManagerThread()
{
}

ClientServiceManager::~ClientServiceManager() {}