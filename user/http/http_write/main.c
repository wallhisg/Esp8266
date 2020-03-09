#include <ets_sys.h>
#include <osapi.h>
#include <os_type.h>
#include <user_interface.h>
#include <uart.h>
#include <espconn.h>
#include <mem.h>
#include <gpio.h>
#include <gpio16.h>

#include <c_types.h>

#include <user_config.h>
#include <tcp_server.h>
#include <edk/sys/init.h>
#include <types.h>
#include <led.h>
#include <http.h>
#include "http_write.h"


// #include <stdlib_noniso.h>

static bool flagtr = true;
static os_timer_t led_timer;
static int led_value = 0;

static struct inode inode;
static struct file file;
static char wbuf = '1';

struct http_method mt ;
struct http_method *method;

void led_service_cb(void *args)
{
    //Do blinky stuff
    devfs_open(&inode, 0x500, 1);
    // open dev
    inode.i_fop->open(&inode, &file);
    // write dev
    inode.i_fop->write(&file, &wbuf, 0);
//     
    kprintf("Blink\r\n");
    display_heap();
    

}
void app_init()
{
    // init uart
    uart_div_modify(0, UART_CLK_FREQ / 9600);
    edk_init();
    led_init();
    // init ...
    WRITE_PERI_REG(PAD_XPD_DCDC_CONF, (READ_PERI_REG(PAD_XPD_DCDC_CONF) & 0xffffffbc) | (uint32_t)0x1);  
    WRITE_PERI_REG(RTC_GPIO_CONF, (READ_PERI_REG(RTC_GPIO_CONF) & (uint32_t)0xfffffffe) | (uint32_t)0x0);

    os_timer_setfn(&led_timer, (os_timer_func_t *)led_service_cb, NULL);
    os_timer_arm(&led_timer, 1000, 1);
    
    // init tcp
    //Set  station mode 
    wifi_set_opmode(STATIONAP_MODE); 

    // ESP8266 connect to router.
    set_station_config();
    
    display_heap();
}

void user_init(void)
{

    system_init_done_cb(app_init);
    
}
