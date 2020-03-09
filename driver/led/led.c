#include "led.h"
#include <list.h>
#include <debug.h>
#include <uaccess.h>
#include <edk/device/cdev.h>
#include <edk/device/char_dev.h>
#include <edk/device/devfs.h>
#include <edk/log/debug.h>


static const char LED_NAME[] = "led";

LOCAL struct list_head led_list_;

static struct dev_props led_props;
static struct led_device led1;

/* prototypes */
ssize_t led_open(struct inode *inode, struct file *file);
ssize_t led_release(struct inode *inode, struct file *file);
ssize_t led_read(struct file *file, char *buf, rsize_t count);
ssize_t led_write(struct file *file, char *buf, rsize_t count);

static struct file_operations leds_fops = {
    .open = led_open,
    .read = led_read,
    .write = led_write,
    .release = led_release
};

ssize_t led_init()
{
    INIT_LIST_HEAD(&led_list_);

    ssize_t ret = 0;

    dev_t dev;
    ret = alloc_chrdev(&led_list_, &dev, 1, LED_NAME);

    if(ret)
        goto exit_led_init;

    cdev_init(&led1.cdev, &leds_fops, &led_props);
    ret = cdev_add(&led_list_, &led1.cdev, dev, 0);

    // set led state
    led1.state = LED_ON;
    
    WRITE_PERI_REG(RTC_GPIO_ENABLE, (READ_PERI_REG(RTC_GPIO_ENABLE) & (uint32_t)0xfffffffe) | (uint32_t)0x1);
exit_led_init:
    return ret;
}


ssize_t led_open(struct inode *inode, struct file *file)
{
    kdebug(DBG_LED, "\tled open.\r\n");
    ssize_t ret = 0;

    struct led_device *led_devp;
    led_devp = container_of(inode->i_cdev, struct led_device, cdev);
    file->private_data = led_devp;

    return ret;
}

ssize_t led_read(struct file *file, char *buf, rsize_t count)
{
    kdebug(DBG_LED, "\tled_read.\r\n");
    ssize_t ret = 0;

    struct led_device *led_devp = file->private_data;

    if(led_devp->state == LED_ON)
        ret = copy_to_user(buf, "1", 1);
    else
        ret = copy_to_user(buf, "0", 1);
    return ret;
}

ssize_t led_write(struct file *file, char *buf, rsize_t count)
{
    kdebug(DBG_LED, "\tled_write.\r\n");
    ssize_t ret = 0;

    struct led_device *led_devp = file->private_data;

    char kbuf = 0;
    if(copy_from_user(&kbuf, buf, 1))
    {
        ret = -EFAULT;
        goto exit_led_write;
    }

    if (kbuf == '1')
    {
        led_devp->state = LED_ON;
        kdebug(DBG_LED, "\tled_write ON: %d\r\n", kbuf);
        gpio_output_set(0, BIT2, BIT2, 0);
        *buf = '0';

    }
    else if (kbuf == '0')
    {
        led_devp->state = LED_OFF;
        kdebug(DBG_LED, "\tled_write OFF: %d\r\n", kbuf);
        gpio_output_set(BIT2, 0, BIT2, 0);
        *buf = '1';
    }

exit_led_write:
    return ret;
}

ssize_t led_release(struct inode *inode, struct file *file)
{
    kdebug(DBG_LED, "\tled_release.\r\n");

    ssize_t ret = 0;

    return ret;
}
