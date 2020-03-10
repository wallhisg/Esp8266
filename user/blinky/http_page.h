#ifndef HTTP_PAGE_H
#define HTTP_PAGE_H

#include <types.h>
#include <http_response.h>

char *index_html =
"<!DOCTYPE html>\r\n"
"<html>\r\n"
"<body>\r\n"
"\r\n"
"<h1>ESP8266 HTTP server demo </h1>\r\n"
"<button type='button' onclick='led_on()'>ON</button><br>\r\n"
"<br>\r\n"
"<button type='button' onclick='led_off()'>OFF</button><br>\r\n"
" \r\n"
"<script>\r\n"

"function led_on() {\r\n"
"  var xhttp;\r\n"
"  if (window.XMLHttpRequest) {\r\n"
"    // code for modern browsers\r\n"
"    xhttp = new XMLHttpRequest();\r\n"
"    } else {\r\n"
"    // code for IE6, IE5\r\n"
"    xhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\r\n"
"  }\r\n"
"  xhttp.open(\"GET\", 'led_on', true);\r\n"
"  xhttp.send();\r\n"
"}\r\n"

"function led_off() {\r\n"
"  var xhttp;\r\n"
"  if (window.XMLHttpRequest) {\r\n"
"    // code for modern browsers\r\n"
"    xhttp = new XMLHttpRequest();\r\n"
"    } else {\r\n"
"    // code for IE6, IE5\r\n"
"    xhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\r\n"
"  }\r\n"
"  xhttp.open(\"GET\", 'led_off', true);\r\n"
"  xhttp.send();\r\n"
"}\r\n"

"</script>\r\n"
"\r\n"
"</body>\r\n"
"</html>\r\n";

void ICACHE_FLASH_ATTR
tcp_server_recv_cb_response(void *arg, char *pusrdata, unsigned short length)
{
    char *ptr = 0;
    //received some data from tcp connection
    os_printf("tcp_server_recv_cb_response\r\n");
    
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

