#include <include/types.h>
#include <debug.h>
#include <mem_alloc.h>
#include <mathdef.h>
#include <http.h>


char  *http_write()
{
    struct http http;
    http_init(&http);

    // HTTP BODY
    http_add_body(&http, "Usually GET requests don\'t have a body");
    int bodyLen = http_get_body_len(&http);


    // HTTP HEADER - METHOD
    http_add_method(&http, "GET", "/json", "HTTP/1.1");

    // HTTP HEADER
    http_add_header(&http, "Host", "localhost:8080");
    
    rsize_t lenInt = get_int_len(bodyLen);
    char *bodyLenChar = (char *)kmalloc((lenInt + 1) * sizeof(char));
    ksprintf(bodyLenChar, "%d", bodyLen);
    http_add_header(&http, "Content-Length", bodyLenChar);
    kfree(bodyLenChar);


    // HTTP VALUE
    char *httpVal = http_get_value(&http);
    kprintf("%s\r\n", httpVal);
    
//     kfree(httpVal);
    http_free(&http);
    return httpVal;
}

