#include "ServerController.h"

// NOTE ABOUT MAKEFILE
// Building a C++ program is a two-stage process. First, you compile each .cpp file into a .o object file. Compiling converts the source code into machine code but doesn't resolve function calls from other source files (since they haven't been compiled yet).
// Link the object files together to create an executable. Linking resolves the external references in each object file.
// https://stackoverflow.com/questions/18252734/using-o-files-in-makefile
int main(int arg, char **argv)
{
    ServerController *server1 = new ServerController("127.0.0.1", 40000, "Default TCP Server");
    server1->Start();

    scanf("\n");

    return 0;
}