#include "ServerController.h"
#include "ClientServiceManager.h"

struct ServiceThreadParams
{
    TcpClient *client;
    ServerController *ctrlr;
};

ClientServiceManager::ClientServiceManager(ServerController *ctrlr)
{
    this->ctrlr = ctrlr;
    this->clientMutex = CreateMutex(NULL, FALSE, NULL);
}

ClientServiceManager::~ClientServiceManager()
{
    // Close all thread handles in the vector
    StopAllClientThreads();
    // The std::vector class internally manages an array to hold its elements, and the memory for that array is automatically allocated and deallocated by the std::vector object itself.
}

void ClientServiceManager::AddNewClientThread(TcpClient *client)
{
    WaitForSingleObject(this->clientMutex, INFINITE);
    ServiceThreadParams *params = new ServiceThreadParams;
    params->client = client;
    params->ctrlr = this->ctrlr;
    this->clientThreads.push_back(CreateThread(NULL, 0, ListenClientThread, params, 0, NULL));
    ReleaseMutex(this->clientMutex);
}

void ClientServiceManager::StopAllClientThreads()
{
    // Join all the client threads
    for (auto &thread : this->clientThreads)
    {
        WaitForSingleObject(this->clientMutex, INFINITE);
        CloseHandle(thread);
        ReleaseMutex(this->clientMutex);
    }
    // Clear the clientThreads vector
    this->clientThreads.clear();
    // Close mutex
    CloseHandle(this->clientMutex);
}

DWORD WINAPI ClientServiceManager::ListenClientThread(LPVOID lpParam)
{

    ServiceThreadParams *params = (ServiceThreadParams *)lpParam;
    TcpClient *client = params->client;
    ServerController *ctrlr = params->ctrlr;
    char buffer[1024];
    int bytesReceived;

    while (true)
    {
        // recv returns the number of bytes received, or `SOCKET_ERROR` if an error occurs. When the recv function is called, it fills the buffer with the received data, but does not null-terminate the data.
        bytesReceived = recv(client->client_socket, buffer, 1024, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            printf("Receive from client failed\n");
            ctrlr->ProcessRemoveClient(client);
            // return value of 0 indicates success and a nonzero value indicating an error.
            break;
        }
        else if (bytesReceived == 0)
        {
            printf("TcpClient disconnected\n");
            ctrlr->ProcessRemoveClient(client);
            break;
        }

        // null-terminate the received data in the buffer. Ensures that any C or C++ functions that operate on the string will stop reading at the end of the received data, preventing any potential issues with buffer overflows or undefined behavior.
        // C-style strings are null-terminated. If the received data does not already contain a null character, any C or C++ functions that operate on the string may continue to read beyond the end of the buffer, resulting in undefined behavior.
        // **null-terminated: have a null character('\0') at the end of the string to makr the end of the string. This is used by many C and C++ functions that operate on strings.
        buffer[bytesReceived] = '\0';
        printf("Data received from client: %s", buffer);

        memset(buffer, 0, 1024);
    }

    delete params;
    return 0;
}