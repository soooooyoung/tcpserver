#ifdef __SERVERCONTROLLER__
#define __SERVERCONTROLLER__

#include <stdint.h>
#include <string>

class ConnectionAcceptor;
class ClientServiceManager;
class ClientDbManager;


class ServerController {

    private:
    ConnectionAcceptor *conn_acc;
    ClientDbManager *client_db_mgr;
    ClientServiceManager *client_svc_mgr;

    public:
    uint32_t ip_addr;
    uint16_t port_no;
    std::string name;
    
    ServerController(string ip_addr, uint16_t port_no, string name);
    ~ServerController();

    void Start();
    void Stop();
}


#endif