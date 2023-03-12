#ifndef __CONNECTIONACCEPTOR__
#define __CONNECTIONACCEPTOR__

class ServerController;

class ConnectionAcceptor
{

private:
public:
    ServerController *ctrlr;
    ConnectionAcceptor(ServerController *);
    ~ConnectionAcceptor();
};

#endif