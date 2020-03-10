#ifndef HTTP_PAGE_H
#define HTTP_PAGE_H

#include <types.h>
#include <http_response.h>

char *index_html =
"<!DOCTYPE html>\r\n"
"<html>\r\n"
"<body>\r\n"
"\r\n"
"<title>ESP Input Form</title>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n"
"</head><body>\r\n"
"   <form action=\"/get\">\r\n"
"       input1: <input type=\"text\" name=\"ssid\">\r\n"
"       input2: <input type=\"text\" name=\"password\">\r\n"
"       <input type=\"submit\" value=\"Submit\">\r\n"
"   </form><br>\r\n"
"</body></html>";

void ICACHE_FLASH_ATTR
tcp_server_recv_cb_response(void *arg, char *pusrdata, unsigned short length)
{
    char *ptr = 0;
    //received some data from tcp connection
    os_printf("tcp_server_recv_cb_response\r\n");
    
    uart1_sendStr_no_wait(pusrdata);
    
    struct espconn *pespconn = arg;
    // os_printf("tcp recv : %s \r\n", pusrdata);
    ptr = (char *)os_strstr(pusrdata, "\r\n");
    ptr[0] = '\0';
    
    if (os_strcmp(pusrdata, "GET / HTTP/1.1") == 0)
    {
        http_response(pespconn, 200, index_html);
    }
    else if (os_strcmp(pusrdata, "GET /led_on HTTP/1.1") == 0)
    {
        os_printf("led_on\r\n");
        http_response(pespconn, 200, NULL);
    } 
    else if (os_strcmp(pusrdata, "GET /led_off HTTP/1.1") == 0)
    {
        os_printf("led_off\r\n");
        http_response(pespconn, 200, NULL);
    }
    
}
#endif  //  HTTP_PAGE_H

