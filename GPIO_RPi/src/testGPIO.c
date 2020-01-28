#include <stdio.h>
#include <stdlib.h>
#include "GPIORpi.h"

int main(int argc, char** argv)
{
    printf("Welcome to test GPIO program:\n");
    ioctl_cmd_export(17);
    ioctl_cmd_set_dir(17, OUTPUT);
    ioctl_cmd_set_active_low(17, HIGH_ACTIVE);
    ioctl_cmd_set_value(17, HIGH);
    return SUCCESS;
}