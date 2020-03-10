#include "http_response.h"
#include <tcp_server.h>

void ICACHE_FLASH_ATTR
http_response(struct espconn *pespconn, int error, char *html_txt)
{
    char *buffer = NULL;
    int html_length = 0;
    buffer = (char *)os_malloc(256 * sizeof(char));
    if(buffer != NULL)
    {
        if(html_txt != NULL)
        {
            html_length = os_strlen(html_txt);
        }
        else
        {
            html_length = 0;
        }

        os_sprintf(buffer, "HTTP/1.1 %d OK\r\n"
                            "Content-Length: %d\r\n"
                            "Content-Type: text/html\r\n"
                            "Connection: Closed\r\n"
                            "\r\n"
        ,error, html_length);

        if(html_length > 0)
        {
            buffer = (char *)os_realloc(buffer, (256 + html_length) *sizeof(char));
            os_strcat(buffer, html_txt);
        }

        espconn_sent(pespconn, buffer, strlen(buffer));
        os_free(buffer);
    }
}
