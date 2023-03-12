#include "ServerController.h"
#include "ClientServiceManager.h"

ClientServiceManager::ClientServiceManager(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
}

ClientServiceManager::~ClientServiceManager() {}