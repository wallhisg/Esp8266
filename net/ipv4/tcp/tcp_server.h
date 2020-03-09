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

void ICACHE_FLASH_ATTR tcp_server_init(uint32 port);

#endif  //  TCP_SERVER_H
