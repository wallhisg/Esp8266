#ifndef HTTP_RESPONSE
#define HTTP_RESPONSE

#include <types.h>
#include <ets_sys.h>
#include <osapi.h>
#include <os_type.h>
#include <user_interface.h>
#include <uart.h>
#include <espconn.h>
#include <mem.h>


/**********************************************************************
    * FunctionName  :   http_response
    * Description   :   send the html body with the html header.
    * Parameters    :   pespconn - espconn of the http server
    *                   error - status code
    *               :   html_txt - 
    *                   the buffer which contents the html file
    * Returns         : none
**********************************************************************/
void ICACHE_FLASH_ATTR
http_response(struct espconn *pespconn, int error, char *html_txt);

#endif  //  http_response
