#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <winsock.h>  // #include <arpa/inet.h> - Unix
#include <ws2tcpip.h> // #include <sys/socket.h> - defined in IEEE Std. 1003.1 (POSIX), but Windows is non-compliant with the POSIX standard.
#include "network_utils.h"

//  Network Byte Order **: The TCP/IP standard network byte order is big-endian. In order to participate in a TCP/IP network, little-endian systems usually bear the burden of conversion to network byte order.

// Network Address Format **: A standard internet address uses a two-part, 32-bit address field. The first part of the address field contains the network address; the second part contains the local address. The four different types of address fields are classified as A, B, C, or D, depending on the bit allocation. (Class D addresses are not supported in TCP/IP for z/VM.)
// https://www.ibm.com/docs/en/zvm/7.1?topic=addressing-network-address-format

// uint32_t ip_addr into A.B.C.D format.
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

    // const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
    //  converts from an Internet address in binary format, specified by src, to standard text format, and places the result in dst, if size, the space available in dst, is sufficient.
    // https://www.ibm.com/docs/en/zvse/6.2?topic=SSB27H_6.2.0/fa2ti_call_inet_ntop.htm
    inet_ntop(AF_INET, &ip_addr, out, 16);
    out[15] = '\0';
    return out;
}

//  converts IP Address in A.B.C.D format in uint32_t format.
uint32_t convert_ip_p_to_n(const char *ip_addr)
{
    uint32_t binary_prefix = 0;

    // int inet_pton(int af, const char *restrict src, void *restrict dst);
    // This function converts the character string src into a network address structure in the af address family, then copies the network address structure to dst. The af argument must be either AF_INET or AF_INET6. dst is written in network byte order. (big endian)

    inet_pton(AF_INET, ip_addr, &binary_prefix);
    binary_prefix = htonl(binary_prefix);
    return binary_prefix;
}