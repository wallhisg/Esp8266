#include "connection.h"

void ICACHE_FLASH_ATTR tcp_connection_init(struct espconn *conn, 
                                           esp_tcp *tcp)
{
    conn->type = ESPCONN_TCP;
    conn->state = ESPCONN_NONE;
    conn->proto.tcp = tcp;
}
