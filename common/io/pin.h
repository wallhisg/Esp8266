#ifndef PIN_H
#define PIN_H

#include <types.h>
#include <gpio.h>
#include <register.h>

struct pin {
    BIT bit;
    rsize_t periphs_io_mux;
    rsize_t func;
};

typedef struct pin pin;

void pin_init(pin pin, uint8_t mode);
rsize_t digital_read(pin pin);
void digital_write(pin pin, uint8_t val);

#endif  //  PIN_H
