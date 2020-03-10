#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <ets_sys.h>
#include <osapi.h>
#include <os_type.h>
#include <user_interface.h>
#include <uart.h>
#include <espconn.h>
#include <mem.h>
#include <gpio.h>

#include <tcp.h>

typedef void (*tcp_server_recv_forward)(void *arg, char *pusrdata, 
                                        unsigned short length);

void ICACHE_FLASH_ATTR tcp_server_init(uint32 port);
void ICACHE_FLASH_ATTR tcp_server_set_recv_forward(tcp_server_recv_forward func);

#endif  //  TCP_SERVER_H
