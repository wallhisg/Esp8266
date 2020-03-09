#include "pin.h"

void pin_init(pin pin, uint8_t mode)
{
    PIN_FUNC_SELECT(pin.periphs_io_mux, pin.func);
    
    if(mode == INPUT)
    {
        GPIO_DIS_OUTPUT(pin.bit);
        PIN_PULLUP_DIS(pin.bit);
    }
    else if(mode == INPUT_PULLUP)
    {
        GPIO_DIS_OUTPUT(pin.bit);
        PIN_PULLUP_EN(pin.bit);
    }
    else if(mode == OUTPUT)
    {
        GPIO_OUTPUT_SET(pin.bit, 0);
    }
}

rsize_t digital_read(pin pin)
{
    rsize_t ret;
    
    return ret;
}

void digital_write(pin pin, uint8_t val)
{
    if(val == HIGH)
        GPIO_OUTPUT_SET(GPIO_ID_PIN(pin.bit), 1);
    else
        GPIO_OUTPUT_SET(GPIO_ID_PIN(pin.bit), 0);
}



