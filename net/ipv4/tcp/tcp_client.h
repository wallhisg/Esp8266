#include "connection.h"

#define NET_DOMAIN "Desktop"
#define packet_size   (2 * 1024)

extern  bool flagtr;

void ICACHE_FLASH_ATTR tcp_client_init(const char remoteIp[], uint32 remotePort);

