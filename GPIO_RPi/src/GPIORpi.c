#include "GPIORpi.h"

int GPIO_Init(GPIO_t* instance)
{
    //Default init name, gpio_number, 
    //auto export the gpio
    //default set at output
    //default set value to HIGH
}
int GPIO_Init(GPIO_t* instance,
            int number, direction_t dir,
            active_low_t act, gpio_value_t initVal)
{
    //Init name, gpio_number
    //init all other properties 
}

int GPIO_export(GPIO_t* instance)
{
    //Export the gpio
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR
}
int GPIO_unexport(GPIO_t* instance)
{
    //Export the gpio
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd, pass cmd UNEXPORT_CMD
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR
}

int GPIO_set_active_low(GPIO_t* instance, active_low_t act)
{
    //Set gpio active low -> TRUE/FALSE
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd(), pass cmd SET_ACTIVE_LOW_CMD
    //Pass the active low value
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR
}
int GPIO_set_value(GPIO_t* instance, gpio_value_t val)
{
    //Set value to LOW/HIGH
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd(), pass cmd SET_VALUE_CMD
    //Pass the gpio_value
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR
}
int GPIO_set_direction(GPIO_t* instance, direction_t dir)
{
    //Set direction to INPUT/OUTPUT
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd(), pass cmd SET_DIR_CMD
    //Pass the direction value
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR   
}

int GPIO_get_value(GPIO_t* instance, gpio_value_t* retVal)
{
    //Get gpio_value
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd(), pass cmd GET_VALUE_CMD
    //Pass retVal
    //if ioctl_cmd() return SUCCESS, then read the retVal in other place, return SUCCESS
    //else print error log, return ERROR   
}
int GPIO_get_export_status(GPIO_t* instance, export_t* retVal)
{
    return SUCCESS;
}
int GPIO_get_direction(GPIO_t* instance, direction_t* retVal)
{
    return SUCCESS;
}

int ioctl_cmd(GPIO_t* instance, gpio_command_t cmd, void* val)
{
    //Perform GPIO check before implement on hardware
    //  1)EXPORT_CMD: Check instance.export_status == UNEXPORTED ?
    //                if yes {check is_exported() if return TRUE change export_status -> EXPORTED, then return SUCCESS
    //                                            else call ioctl_cmd_export(). If return SUCCESS,change export_status -> EXPORTED, return SUCCESS, else return ERROR}
    //                else {check is_exported() if return TRUE just return SUCCESS and print log "already exported\n"}
    //                                          else call ioctl_cmd_export(). If return SUCCESS, return SUCCESS, else change export_status -> UNEXPORTED, return ERROR}
    //  2)UNEXPORTED_CMD: Check instance.export_status == EXPORTED ?
    //                if yes {check is_exported() if return FALSE change export_status -> UNEXPORTED, then return SUCCESS
    //                                            else call ioctl_cmd_unexport(). If return SUCCESS,change export_status -> UNEXPORTED, return SUCCESS, else return ERROR}
    //                else {check is_exported() if return FALSE just return SUCCESS and print log "already unexported\n"}
    //                                          else call ioctl_cmd_unexport(). If return SUCCESS, return SUCCESS, else change export_status -> UNEXPORTED, return ERROR}
    //  3)SET_ACTIVE_LOW_CMD:   check is_exported() && export_status == EXPORTED ?
    //                          if yes call ioctl_cmd_set_active_low(), if return SUCCESS, return SUCCESS, else return ERROR
    //                          else print log "please export first\n", return ERROR
    //  4)SET_DIR_CMD:          check is_exported() && export_status == EXPORTED ?
    //                          if yes call ioctl_cmd_set_dir(), if return SUCCESS, return SUCCESS, else return ERROR
    //                          else print log "please export first\n", return ERROR
    //  5)SET_VALUE_CMD:        check is_exported() && export_status == EXPORTED ?
    //                          if yes call ioctl_cmd_set_value, if return SUCCESS, return SUCCESS, else return ERROR          
    //                          else print log "please export first\n", return ERROR
    //  6)GET_VALUE_CMD:        check is_exported() && export_status == EXPORTED ?
    //                          if yes call ioctl_cmd_get_value, if return SUCCESS, return SUCCESS, else return ERROR          
    //                          else print log "please export first\n", return ERROR
}
int ioctl_is_exported(GPIO_t* instance)
{
    //check check in /sys/class/gpio/ are there /gpio_num or not ?
    //return TRUE if yes
    //else return FALSE
}

//All below function directly run on file:
//ie: /sys/class/gpio/
/*set functions run write():1)set_active_low: /gpio_num/active_low
                            2)export:   /export
                            3)unexport: /unexport
                            4)set_dir:  /gpio_num/direction
                            5)set_value:/gpio_num/value                              
*/
//get functions run read(): get_value:  /gpio_num/value
int ioctl_cmd_set_active_low(int num, active_low_t val)
{

}
int ioctl_cmd_export(int num)
{

}
int ioctl_cmd_unexport(int num)
{

}
int ioctl_cmd_set_dir(int num, direction_t dir)
{

}
int ioctl_cmd_set_value(int num, gpio_value_t val)
{

}
int ioctl_cmd_get_value(int num, gpio_value_t* val)
{

}