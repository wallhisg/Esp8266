#include "tcp.h"
#include <net/ipv4/tcp/tcp_server.h>
#include <net/ipv4/tcp/tcp_client.h>

LOCAL char remoteServerIp[4] = {IP_REMOTE_OCTET_1,
                                IP_REMOTE_OCTET_2,
                                IP_REMOTE_OCTET_3,
                                IP_REMOTE_OCTET_4};
extern  bool flagtr;
LOCAL os_timer_t tcpTimer;
LOCAL struct espconn 	user_tcp_conn;
LOCAL struct _esp_tcp 	user_tcp;

/********************************************************************
 * FunctionName : user_esp_platform_check_ip
 * Description  : check whether get ip addr or not
 * Parameters   : none
 * Returns      : none
*********************************************************************/
void ICACHE_FLASH_ATTR
tcp_check_ip(void)
{
    uint8 ret = 0;
    
    os_printf("user_esp_platform_check_ip \r\n");
    struct ip_info ipconfig;

   //disarm timer first
    os_timer_disarm(&tcpTimer);

   //get ip info of ESP8266 station
    wifi_get_ip_info(STATION_IF, &ipconfig);

    if (wifi_station_get_connect_status() == STATION_GOT_IP && ipconfig.ip.addr != 0) 
    {
        os_printf("got ip !!! \r\n");
        tcp_server_init(TCP_LOCAL_SERVER_PORT);
        tcp_client_init(remoteServerIp, TCP_REMOTE_SERVER_PORT);

        ret = 0;
    } 
    else {

        if ((wifi_station_get_connect_status() == STATION_WRONG_PASSWORD || 
            wifi_station_get_connect_status() == STATION_NO_AP_FOUND || 
            wifi_station_get_connect_status() == STATION_CONNECT_FAIL)) 
        {
            os_printf("connect fail !!! \r\n");
            ret = -1;
        } 
        else 
        {
           //re-arm timer to check ip
            os_timer_setfn(&tcpTimer, (os_timer_func_t *)tcp_check_ip, NULL);
            os_timer_arm(&tcpTimer, 100, 0);
        }
    }
}

/********************************************************************
 * FunctionName : user_set_station_config
 * Description  : set the router info which ESP8266 station will connect to
 * Parameters   : none
 * Returns      : none
*********************************************************************/
void ICACHE_FLASH_ATTR
set_station_config(void)
{
    os_printf("user_set_station_config \r\n");
    os_printf("SDK version:%s\n", system_get_sdk_version());
    // Wifi configuration
    char ssid[32] = SSID;
    char password[64] = PASSWORD;
    struct station_config stationConf;

    //need not mac address
    stationConf.bssid_set = 0;

    //Set ap settings
    os_memcpy(&stationConf.ssid, ssid, 32);
    os_memcpy(&stationConf.password, password, 64);
    wifi_station_set_config(&stationConf);

    //set a timer to check whether got ip from router succeed or not.
    os_timer_disarm(&tcpTimer);
    os_timer_setfn(&tcpTimer, (os_timer_func_t *)tcp_check_ip, NULL);
    os_timer_arm(&tcpTimer, 100, 0);

}
