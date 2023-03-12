#include "ServerController.h"
#include "ConnectionAcceptor.h"

ConnectionAcceptor::ConnectionAcceptor(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
}

ConnectionAcceptor::~ConnectionAcceptor()
{
}