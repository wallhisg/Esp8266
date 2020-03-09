#include "tcp_client.h"
#include "tcp.h"
#include <http_write.h>

LOCAL struct connection_t clientConn_;

LOCAL void ICACHE_FLASH_ATTR tcp_client_recv_cb(void *arg, char *pusrdata, unsigned short length);
LOCAL void ICACHE_FLASH_ATTR tcp_client_sent_cb(void *arg);
LOCAL void ICACHE_FLASH_ATTR tcp_client_discon_cb(void *arg);
LOCAL void ICACHE_FLASH_ATTR tcp_client_sent_data(struct espconn *pespconn);
LOCAL void ICACHE_FLASH_ATTR tcp_client_connect_cb(void *arg);
LOCAL void ICACHE_FLASH_ATTR tcp_client_recon_cb(void *arg, sint8 err);

void ICACHE_FLASH_ATTR
tcp_client_init(const char remoteIp[4], uint32 remotePort)
{
    os_printf("tcp_client_init.\r\n");
    tcp_connection_init(&clientConn_.conn, &clientConn_.tcp);

    // set remote ip
    os_memcpy(clientConn_.conn.proto.tcp->remote_ip, remoteIp, 4);
    // set remote port
    clientConn_.conn.proto.tcp->remote_port = remotePort;
    // set local port of esp8266
    clientConn_.conn.proto.tcp->local_port = espconn_port();

    // register connect callback
    espconn_regist_connectcb(&clientConn_.conn, tcp_client_connect_cb);
    // register reconnect callback as error handler
    espconn_regist_reconcb(&clientConn_.conn, tcp_client_recon_cb);

    espconn_connect(&clientConn_.conn);
}

/*****************************************************************************
 * FunctionName : tcp_client_recv_cb
 * Description  : receive callback.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
******************************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_client_recv_cb(void *arg, char *pusrdata, unsigned short length)
{
   //received some data from tcp connection
    os_printf("tcp recv !!! %s \r\n", pusrdata);

}
/*****************************************************************************
 * FunctionName : tcp_client_sent_cb
 * Description  : data sent callback.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
******************************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_client_sent_cb(void *arg)
{
   //data sent successfully
    os_printf("tcp sent succeed !!! \r\n");
}
/*****************************************************************************
 * FunctionName : tcp_client_discon_cb
 * Description  : disconnect callback.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
******************************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_client_discon_cb(void *arg)
{
   //tcp disconnect successfully
    os_printf("tcp disconnect succeed !!! \r\n");
}
/*****************************************************************************
 * FunctionName : user_esp_platform_sent
 * Description  : Processing the application data and sending it to the host
 * Parameters   : pespconn -- the espconn used to connetion with the host
 * Returns      : none
******************************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_client_sent_data(struct espconn *pespconn)
{
    os_printf("tcp_client_sent_data\r\n");
    char 	datasend[256];

    char *httpSend = http_write();
    strcpy(datasend, httpSend);
    espconn_sent(pespconn, datasend, strlen(datasend));
    espconn_disconnect(pespconn);

    kfree(httpSend);
//   flagtr = false;
}

/*****************************************************************************
 * FunctionName : tcp_client_connect_cb
 * Description  : A new incoming tcp connection has been connected.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
******************************************************************************/
LOCAL void ICACHE_FLASH_ATTR tcp_client_connect_cb(void *arg)
{
    //flagtr = true;

    os_printf("tcp_client_connect_cb\r\n");
    struct espconn *pespconn = arg;

    os_printf("connect succeed !!! \r\n");

    espconn_regist_recvcb(pespconn, tcp_client_recv_cb);
    espconn_regist_sentcb(pespconn, tcp_client_sent_cb);
    espconn_regist_disconcb(pespconn, tcp_client_discon_cb);

    tcp_client_sent_data(pespconn);
}

/*****************************************************************************
 * FunctionName : tcp_client_recon_cb
 * Description  : reconnect callback, error occured in TCP connection.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
******************************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_client_recon_cb(void *arg, sint8 err)
{
    os_printf("tcp_client_recon_cb\r\n");

    //error occured , tcp connection broke. user can try to reconnect here.
    os_printf("reconnect callback, error code %d !!! \r\n",err);
}
