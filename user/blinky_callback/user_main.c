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
#include <pin.h>
#include <led.h>

static bool flagtr = true;
static os_timer_t led_timer;
static int led_value = 0;

static struct inode inode;
static struct file file;
static char wbuf = '1';

static pin ledPin = {
    .bit = BIT_2,
    .periphs_io_mux = PERIPHS_IO_MUX_GPIO2_U,
    .func = FUNC_GPIO2
};


rsize_t toggleLed = LOW;
void led_service_cb(void *args)
{
    
    if(toggleLed == LOW)
    {
        toggleLed = HIGH;
        digital_write(ledPin, HIGH);
    }
    else 
    {
        toggleLed = LOW;
        digital_write(ledPin, LOW);
    }
    

    kprintf("Blink\r\n");
    

}


void app_init()
{
    // init uart
    uart_div_modify(0, UART_CLK_FREQ / 9600);

    os_timer_setfn(&led_timer, (os_timer_func_t *)led_service_cb, NULL);
    os_timer_arm(&led_timer, 1000, 1);
    
    // init pin
    pin_init(ledPin, OUTPUT);
    
    // init tcp / set station mode 
    wifi_set_opmode(STATIONAP_MODE); 

    // ESP8266 connect to router.
    set_station_config();

    display_heap();
}

void user_init(void)
{

    system_init_done_cb(app_init);
    
}
