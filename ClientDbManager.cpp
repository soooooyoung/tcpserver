#include "ServerController.h"
#include "ClientDbManger.h"

ClientDbManager::ClientDbManager(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
};

ClientDbManager::~ClientDbManager()
{
}