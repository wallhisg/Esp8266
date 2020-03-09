#include <tcp_server.h>
#include <connection.h>

//LOCAL struct espconn esp_conn;
//LOCAL esp_tcp esptcp;

LOCAL struct connection_t serverConn;

LOCAL void ICACHE_FLASH_ATTR tcp_server_sent_cb(void *arg);
LOCAL void ICACHE_FLASH_ATTR tcp_server_recv_cb(void *arg, char *pusrdata,
                                                unsigned short length);
LOCAL void ICACHE_FLASH_ATTR tcp_server_discon_cb(void *arg);
LOCAL void ICACHE_FLASH_ATTR tcp_server_recon_cb(void *arg, sint8 err);
LOCAL void ICACHE_FLASH_ATTR tcp_server_listen(void *arg);

extern void ICACHE_FLASH_ATTR uart1_write_char(char c);
/********************************************************************
 * FunctionName : tcp_server_init
 * Description  : parameter initialize as a TCP server
 * Parameters   : port -- server port
 * Returns      : none
*********************************************************************/
void ICACHE_FLASH_ATTR
tcp_server_init(uint32 port)
{
    os_printf("tcp_server_init.\r\n");

    tcp_connection_init(&serverConn.conn, &serverConn.tcp);
    serverConn.conn.proto.tcp->local_port = port;
    
    espconn_regist_connectcb(&serverConn.conn, tcp_server_listen);
    sint8 ret = espconn_accept(&serverConn.conn);
    os_printf("espconn_accept [%d] !!! \r\n", ret);
 
}

/********************************************************************
 * FunctionName : tcp_server_sent_cb
 * Description  : data sent callback.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
*********************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_server_sent_cb(void *arg)
{
   //data sent successfully
 
    os_printf("tcp sent cb \r\n");
}
 
 
/********************************************************************
 * FunctionName : tcp_server_recv_cb
 * Description  : receive callback.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
*********************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_server_recv_cb(void *arg, char *pusrdata, unsigned short length)
{
   //received some data from tcp connection
    
   struct espconn *pespconn = arg;
   os_printf("tcp recv : %s \r\n", pusrdata);
    uart1_sendStr_no_wait(pusrdata);
   //espconn_sent(pespconn, pusrdata, length);
   espconn_sent(pespconn, "<body>Hello, World!</body>", 26);
   espconn_disconnect(pespconn);
    
}
 
/********************************************************************
 * FunctionName : tcp_server_discon_cb
 * Description  : disconnect callback.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
*********************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_server_discon_cb(void *arg)
{
   //tcp disconnect successfully
    
    os_printf("tcp disconnect succeed !!! \r\n");
    char c;
    c = 'c';
    uart1_write_char(c);
}
 
/********************************************************************
 * FunctionName : tcp_server_recon_cb
 * Description  : reconnect callback, error occured in TCP connection.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
*********************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_server_recon_cb(void *arg, sint8 err)
{
   //error occured , tcp connection broke. 
    
    os_printf("reconnect callback, error code %d !!! \r\n",err);
}
 
LOCAL void tcp_server_multi_send(void)
{
    os_printf("tcp_server_multi_send \r\n");
    struct espconn *pesp_conn = &serverConn.conn; /*&esp_conn*/;

    remot_info *premot = NULL;
    uint8 count = 0;
    sint8 value = ESPCONN_OK;
    if (espconn_get_connection_info(pesp_conn,&premot,0) == ESPCONN_OK){
        char *pbuf = "tcp_server_multi_send\n";
        for (count = 0; count < pesp_conn->link_cnt; count ++){
            pesp_conn->proto.tcp->remote_port = premot[count].remote_port;
            
            pesp_conn->proto.tcp->remote_ip[0] = premot[count].remote_ip[0];
            pesp_conn->proto.tcp->remote_ip[1] = premot[count].remote_ip[1];
            pesp_conn->proto.tcp->remote_ip[2] = premot[count].remote_ip[2];
            pesp_conn->proto.tcp->remote_ip[3] = premot[count].remote_ip[3];

            //espconn_sent(pesp_conn, pbuf, os_strlen(pbuf));
        }
    }
}
 
 
/********************************************************************
 * FunctionName : tcp_server_listen
 * Description  : TCP server listened a connection successfully
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
*********************************************************************/
LOCAL void ICACHE_FLASH_ATTR
tcp_server_listen(void *arg)
{
    struct espconn *pesp_conn = arg;
    os_printf("tcp_server_listen !!! \r\n");

    espconn_regist_recvcb(pesp_conn, tcp_server_recv_cb);
    espconn_regist_reconcb(pesp_conn, tcp_server_recon_cb);
    espconn_regist_disconcb(pesp_conn, tcp_server_discon_cb);

    espconn_regist_sentcb(pesp_conn, tcp_server_sent_cb);
    tcp_server_multi_send();
}
 
