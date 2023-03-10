#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <winsock.h>  // #include <arpa/inet.h> - Unix
#include <ws2tcpip.h> // #include <sys/socket.h> - defined in IEEE Std. 1003.1 (POSIX), but Windows is non-compliant with the POSIX standard.
#include "network_utils.h"

char *convert_ip_n_to_p(uint32_t ip_addr, char *output_buffer)
{

    char *out = NULL;
    static char str_ip[16];

    // If output is provided, return result in output,
    // else return result in local static buffer of 16 bytes.
    out = !output_buffer ? str_ip : output_buffer;

    // void* memset( void* str, int ch, size_t n);
    // Memset() converts the value ch to unsigned char and copies it into each of the first n characters of the object pointed to by str[]. If the object is not trivially-copyable (e.g., scalar, array, or a C-compatible struct), the behavior is undefined. If n is greater than the size of the object pointed to by str, the behavior is undefined.
    // https://www.geeksforgeeks.org/memset-in-cpp/
    memset(out, 0, 16);

    // Host TO Network translation
    // convert values between host and network byte order
    // makes sure the endian of a 32 bit data value is correct (Big endian)

    ip_addr = htonl(ip_addr);
    inet_ntop(AF_INET, &ip_addr, out, 16);
    out[15] = '\0';
    return out;
}