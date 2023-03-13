#include "ServerController.h"
#include "ClientDbManager.h"

ClientDbManager::ClientDbManager(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
};

void ClientDbManager::StartClientDbManagerThread()
{
}

ClientDbManager::~ClientDbManager()
{
}