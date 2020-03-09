#ifndef CONNECTION_H
#define CONNECTION_H

#include <c_types.h>
#include <ets_sys.h>
#include <osapi.h>
#include <user_interface.h>
#include <os_type.h>
#include <espconn.h>
#include <mem.h>


struct connection_t {
    struct espconn conn;
    union {
        esp_tcp tcp;
        esp_udp udp;
    };
};

void ICACHE_FLASH_ATTR tcp_connection_init(struct espconn *conn,
                                           esp_tcp *tcp);

#endif  //  CONNECTION_H
 
