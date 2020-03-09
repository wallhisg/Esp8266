#ifndef LED_H
#define LED_H

#include <edk/include/types.h>
#include <edk/include/list.h>
#include <edk/device/cdev.h>

#define NUM_LED      2

#define LED_ON       1
#define LED_OFF      0

struct led_device {
    rsize_t state;
    struct cdev cdev;
};

ssize_t led_init();

#endif // LED_H
