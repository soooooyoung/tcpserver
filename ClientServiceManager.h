#ifdef __CLIENTSERVICEMANAGER__
#define __CLIENTSERVICEMANAGER__


class ServerController;

class ClientServiceManager{

    private:

    public:
    ServerController *ctrlr;
    ClientServiceManager(ServerController *);
    ~ClientServiceManager();
}

#endif