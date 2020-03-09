#ifndef TCP_CONFIG_H
#define TCP_CONFIG_H

#include <c_types.h>
#include <ets_sys.h>
#include <osapi.h>
#include <user_interface.h>
#include <os_type.h>
#include <espconn.h>

#include <uart.h>
#include <mem.h>
#include <gpio.h>


#define SSID 		"Wireless"
#define PASSWORD 	"12345678abcd"

#define TCP_LOCAL_SERVER_PORT     1112

// remote IP of TCP server
#define IP_REMOTE_OCTET_1   192
#define IP_REMOTE_OCTET_2   168
#define IP_REMOTE_OCTET_3   1
#define IP_REMOTE_OCTET_4   100
// remote server port of TCP server
#define TCP_REMOTE_SERVER_PORT  8080
/********************************************************************
 * FunctionName : user_esp_platform_check_ip
 * Description  : check whether get ip addr or not
 * Parameters   : none
 * Returns      : none
*********************************************************************/
void ICACHE_FLASH_ATTR
tcp_check_ip(void);

/********************************************************************
 * FunctionName : user_set_station_config
 * Description  : set the router info which ESP8266 station will connect to
 * Parameters   : none
 * Returns      : none
*********************************************************************/
void ICACHE_FLASH_ATTR set_station_config(void);

#endif  //  TCP_CONFIG_H
