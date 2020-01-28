#include <stdio.h>
#include <stdlib.h>
#include "GPIORpi.h"
#include <unistd.h>
int main(int argc, char** argv)
{
    printf("Welcome to test GPIO program:\n");
    // if(ioctl_is_exported(17) == FALSE)
    //     ioctl_cmd_export(17);
    // ioctl_cmd_set_dir(17, OUTPUT);
    // ioctl_cmd_set_active_low(17, HIGH_ACTIVE);
    // ioctl_cmd_set_value(17, HIGH);
    GPIO_t gpio17;
    GPIO_Init_Custom(&gpio17, 17, OUTPUT, HIGH_ACTIVE, HIGH);
    //ioctl_cmd(&gpio17, EXPORT_CMD, NULL);
    sleep(2);
    GPIO_set_value(&gpio17, LOW);
    printf("Info of gpio%d:\n",gpio17.gpio_num);
    printf("num=%d, active_low=%d, dir=%d, value=%d\n",\
	gpio17.gpio_num, gpio17.active_low, gpio17.direction, gpio17.value);
    return SUCCESS;
}
