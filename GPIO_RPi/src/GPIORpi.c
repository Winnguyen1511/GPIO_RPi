#include "GPIORpi.h"

int GPIO_Init_Default(GPIO_t* instance, int number)
{
    //Default init name, gpio_number, 
    //auto export the gpio
    //default set at output
    //default set value to HIGH
    char name[MAX_NAME_SIZE], number_char[MAX_PIN_SIZE];
    strcmp(name, GPIO_PREFIX);
    sprintf(number_char, "%d", number);
    strcmp(name, number_char);
    instance->name = (char*)malloc(MAX_NAME_SIZE *(sizeof(char)));
    strcpy(instance->name, name);
    instance->gpio_num = number;

    if(!GPIO_export(instance))
    {
        printf("Error: Cannot export gpio%d\n", instance->gpio_num);
        return ERROR;
    }

    if(!GPIO_set_direction(instance, OUTPUT))
    {
        printf("Error: Cannot set direction gpio%d\n", instance->gpio_num);
        return ERROR;
    }

    if(!GPIO_set_value(instance, HIGH))
    {
        printf("Error: Cannot set value gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    return SUCCESS;
    
}
int GPIO_Init_Custom(GPIO_t* instance,\
            int number, direction_t dir,\
            active_low_t act, gpio_value_t initVal)
{
    //Init name, gpio_number
    //init all other properties 
    char name[MAX_NAME_SIZE] = {0}, number_char[MAX_PIN_SIZE] ={0};
    strcat(name, GPIO_PREFIX);
    sprintf(number_char, "%d", number);
    strcat(name, number_char);
    instance->name = (char*)malloc(MAX_NAME_SIZE *(sizeof(char)));
    strcpy(instance->name, name);
    instance->gpio_num = number;

    if(!GPIO_export(instance))
    {
        printf("Error: Cannot export gpio%d\n", instance->gpio_num);
        return ERROR;
    }

    if(!GPIO_set_active_low(instance, act))
    {
        printf("Error: Cannot set active low->%d gpio%d\n",act, instance->gpio_num);
        return ERROR;
    }

    if(!GPIO_set_direction( instance, dir ))
    {
        printf("Error: Cannot set direction gpio%d\n", instance->gpio_num);
        return ERROR;
    }

    if(!GPIO_set_value(instance, initVal))
    {
        printf("Error: Cannot set value gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    return SUCCESS;
}
int GPIO_Denit(GPIO_t* instance)
{
    if(instance->direction == OUTPUT)
    {
        active_low_t tmpAct;
        if(!GPIO_get_active_low(instance, &tmpAct))
        {
            printf("Error: Cannot get active low gpio%d\n", instance->gpio_num);
            return ERROR;
        }

        if(tmpAct == HIGH_ACTIVE)
        {
            if(!GPIO_set_value(instance, LOW))
            {
                printf("Error: Cannot set value gpio%d\n", instance->gpio_num);
                return ERROR;
            }
        }
        else if(tmpAct == LOW_ACTIVE)
        {
            if(!GPIO_set_value(instance, HIGH))
            {
                printf("Error: Cannot set value gpio%d\n", instance->gpio_num);
                return ERROR;
            }
        }
        else
        {
            //do nothing
        }
    }
    if(!GPIO_unexport(instance))
    {
        printf("Error: Cannot unexport gpio%d", instance->gpio_num);
        return ERROR;
    }
    return SUCCESS;
}
int GPIO_export(GPIO_t* instance)
{
    //Export the gpio
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR
    if(!ioctl_cmd(instance, EXPORT_CMD, NULL))
    {
        printf("Error: ioctl cmd export gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    //instance->export_status = EXPORTED;
    return SUCCESS;
}
int GPIO_unexport(GPIO_t* instance)
{
    //Export the gpio
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd, pass cmd UNEXPORT_CMD
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR
    if(!ioctl_cmd(instance, UNEXPORT_CMD, NULL))
    {
        printf("Error: ioctl cmd unexport gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    //instance->export_status = UNEXPORTED;
    return SUCCESS;
}

int GPIO_set_active_low(GPIO_t* instance, active_low_t act)
{
    //Set gpio active low -> TRUE/FALSE
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd(), pass cmd SET_ACTIVE_LOW_CMD
    //Pass the active low value
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR
    if(!ioctl_cmd(instance, SET_ACTIVE_LOW_CMD, &act))
    {
        printf("Error: ioctl cmd set active low gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    //instance->active_low = act;
    return SUCCESS;
}
int GPIO_set_value(GPIO_t* instance, gpio_value_t val)
{
    //Set value to LOW/HIGH
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd(), pass cmd SET_VALUE_CMD
    //Pass the gpio_value
    //if ioctl_cmd() return SUCCESS, then return SUCCESS
    //else print error log, return ERROR
    if(!ioctl_cmd(instance, SET_VALUE_CMD, &val))
    {
        printf("Error: ioctl cmd set value gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    //instance->value = val;
    return SUCCESS;
}



int GPIO_set_direction(GPIO_t* instance, direction_t dir)
{
    if(!ioctl_cmd(instance, SET_DIR_CMD, &dir))
    {
        printf("Error: ioctl cmd set direction gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    //instance->direction = dir;
    return SUCCESS;   
}

int GPIO_get_active_low(GPIO_t* instance, active_low_t* retVal)
{
    if(!ioctl_cmd(instance, GET_ACTIVE_LOW_CMD, retVal))
    {
        printf("Error: ioctl get active low gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    //if( *retVal == instance->active_low)
    // {
    //     return SUCCESS;
    // }
    // else
    // {
    //     printf("Error: internal core error gpio%d\n", instance->gpio_num);
    //     return ERROR;
    // }
    return SUCCESS;
}

int GPIO_get_value(GPIO_t* instance, gpio_value_t* retVal)
{
    //Get gpio_value
    //Call ioctl_cmd(), pass the GPIO struct to ioctl_cmd(), pass cmd GET_VALUE_CMD
    //Pass retVal
    //if ioctl_cmd() return SUCCESS, then read the retVal in other place, return SUCCESS
    //else print error log, return ERROR
    if(!ioctl_cmd(instance, GET_VALUE_CMD, retVal))
    {
        printf("Error: ioctl get value gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    // if( *retVal == instance->value)
    // {
    //     return SUCCESS;
    // }
    // else
    // {
    //     printf("Error: internal core error gpio%d\n", instance->gpio_num);
    //     return ERROR;
    // }
    return SUCCESS;
}
int GPIO_get_export_status(GPIO_t* instance, export_t* retVal)
{
    int dirStat = ioctl_is_exported(instance);
    if((instance->export_status == EXPORTED)
        &&(dirStat == TRUE))
        *retVal = EXPORTED;
    else if((instance->export_status == UNEXPORTED)
            &&(dirStat == FALSE))
        *retVal = UNEXPORTED;
    else{
        *retVal = -1;
        printf("Error: internal core error gpio%d\n", instance->gpio_num);
        return ERROR;
    }
    return SUCCESS;
}
int GPIO_get_direction(GPIO_t* instance, direction_t* retVal)
{
    if(!ioctl_cmd(instance, GET_DIR_CMD, retVal))
    {
        printf("Error: ioctl cmd get direction gpio%d\n", instance->gpio_num);
        return ERROR;
    }

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
    //  3)SET_DIR_CMD:          check is_exported() && export_status == EXPORTED ?
    //                          if yes call ioctl_cmd_set_dir(), if return SUCCESS, return SUCCESS, else return ERROR
    //                          else print log "please export first\n", return ERROR
    //  4)SET_ACTIVE_LOW_CMD:   check is_exported() && export_status == EXPORTED ?
    //                          if yes call ioctl_cmd_set_active_low(), if return SUCCESS, return SUCCESS, else return ERROR
    //                          else print log "please export first\n", return ERROR
    //  5)SET_VALUE_CMD:        check is_exported() && export_status == EXPORTED ?
    //                          if yes call ioctl_cmd_set_value, if return SUCCESS, return SUCCESS, else return ERROR          
    //                          else print log "please export first\n", return ERROR
    //  6)GET_DIR_CMD:
    //  7)GET_ACTIVE_LOW_CMD:
    //  8)GET_VALUE_CMD:        check is_exported() && export_status == EXPORTED ?
    //                          if yes call ioctl_cmd_get_value, if return SUCCESS, return SUCCESS, else return ERROR          
    //                          else print log "please export first\n", return ERROR

    if(cmd == EXPORT_CMD || cmd == UNEXPORT_CMD)
    {
        int dir_exist = ioctl_is_exported(instance);
        if(cmd == EXPORT_CMD)
        {
            if(instance->export_status == UNEXPORTED)
            {
                if(dir_exist == TRUE)
                {
                    instance->export_status = EXPORTED;
                    return SUCCESS;
                }
                else{
                    if(!ioctl_cmd_export(instance->gpio_num))
                        return ERROR;
                    instance->export_status = EXPORTED;
                    return SUCCESS;
                }
            }
            else{
                if(dir_exist == FALSE)
                {
                    printf("already unexported\n");
                    return SUCCESS;
                }
                else{
                    if(!ioctl_cmd_export(instance->gpio_num))
                    {
                        instance->export_status = UNEXPORTED;
                        return ERROR;
                    }
                    return SUCCESS;
                }
            }
        }
        else
        {
            if(instance->export_status == EXPORTED)
            {
                if(dir_exist == FALSE)
                {
                    instance->export_status = UNEXPORTED;
                    return SUCCESS;
                }
                else{
                    if(!ioctl_cmd_unexport(instance->gpio_num))
                        return ERROR;
                    instance->export_status = UNEXPORTED;
                    return SUCCESS;
                }
            }
            else{
                if(dir_exist == TRUE)
                {
                    printf("already exported\n");
                    return SUCCESS;
                }
                else{
                    if(!ioctl_cmd_export(instance->gpio_num))
                    {
                        instance->export_status = EXPORTED;
                        return ERROR;
                    }
                    return SUCCESS;
                }
            }
        }
            
    }
    else
    {
        export_t    tmpExport;
        int dir_exist = ioctl_is_exported(instance);
        if(dir_exist == TRUE)
            tmpExport = EXPORTED;
        else
            tmpExport = UNEXPORTED;
        
        if(instance->export_status != tmpExport)
        {
            printf("Error: internal error export status gpio%d\n", instance->gpio_num);
            return ERROR;
        }
        int ret;
        switch (cmd)
        {
        case SET_DIR_CMD:
            ret = (ioctl_cmd_set_dir(instance->gpio_num, *((direction_t*)val) )) ? SUCCESS : ERROR; 
            break;
        case SET_ACTIVE_LOW_CMD:
            ret = (ioctl_cmd_set_active_low(instance->gpio_num, *((active_low_t*)val)))? SUCCESS : ERROR;
            break;
        case SET_VALUE_CMD:
            ret = (ioctl_cmd_set_value(instance->gpio_num, *((gpio_value_t*)val)))? SUCCESS : ERROR;
            break;
        case GET_DIR_CMD:
            ret = (ioctl_cmd_get_dir(instance->gpio_num, (direction_t*)val))? SUCCESS : ERROR;
            break;
        case GET_ACTIVE_LOW_CMD:
            ret = (ioctl_cmd_get_active_low(instance->gpio_num, (active_low_t*)val)) ? SUCCESS : ERROR;
            break;
        case GET_VALUE_CMD:
            ret = (ioctl_cmd_get_value(instance->gpio_num, (gpio_value_t*)val)) ? SUCCESS : ERROR;
            break;
        }
        if(ret == ERROR)
            val = (void*)-1;
        return ret;   
    }

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
    int fd;
    char name[MAX_NAME_SIZE] = {0}, number_char[MAX_PIN_SIZE] ={0};
    strcat(name, GPIO_PREFIX);
    sprintf(number_char, "%d", num);
    strcat(name, number_char);
    char path[MAX_PATH_SIZE]={0};
    strcat(path, GPIO_PATH);
    strcat(path, name);
    strcat(path, ACTIVE_LOW);
    char str_val;
    fprintf(&str_val, "%d", (int)val);
    fd = open(path, FILE_FLAGS, FILE_PERMS);
    if(fd == -1)
    {
        printf("Error: ioctl cmd set active low open file\n");
        return ERROR;
    }
    if(write(fd, &str_val, 1) != 1)
    {
        printf("Error : ioctl set active low write file\n");
        return ERROR;
    }
    close(fd);
    return SUCCESS;
}
int ioctl_cmd_export(int num)
{
    int fd, size;
    char path[MAX_PATH_SIZE]={0}, number_char[MAX_PIN_SIZE] = {0};
    strcat(path, GPIO_PATH);
    if(num > 9) size = 2;
    else size = 1;
    sprintf(number_char, "%d", num);
    strcat(path, EXPORT);
    fd = open(path, FILE_FLAGS, FILE_PERMS);
    if(fd == -1)
    {
        printf("Error: ioctl cmd export open file\n");
        return ERROR;
    }
    if(write(fd, number_char, size) != size)
    {
        printf("Error : ioctl set export write file\n");
        return ERROR;
    }
    close(fd);
    return SUCCESS;
}
int ioctl_cmd_unexport(int num)
{
    int fd, size;
    char path[MAX_PATH_SIZE]={0}, number_char[MAX_PIN_SIZE] = {0};
    strcat(path, GPIO_PATH);
    if(num > 9) size = 2;
    else size = 1;
    sprintf(number_char, "%d", num);
    strcat(path, UNEXPORT);
    fd = open(path, FILE_FLAGS, FILE_PERMS);
    if(fd == -1)
    {
        printf("Error: ioctl cmd unexport open file\n");
        return ERROR;
    }
    if(write(fd, number_char, size) != size)
    {
        printf("Error : ioctl set unexport write file\n");
        return ERROR;
    }
    close(fd);
    return SUCCESS;
}
int ioctl_cmd_set_dir(int num, direction_t dir)
{
    int fd, size;
    char name[MAX_NAME_SIZE] = {0}, number_char[MAX_PIN_SIZE] ={0};
    strcat(name, GPIO_PREFIX);
    sprintf(number_char, "%d", num);
    strcat(name, number_char);
    char path[MAX_PATH_SIZE]={0};
    strcat(path, GPIO_PATH);
    strcat(path, name);
    strcat(path, DIRECTION);
    char *str_val;
    if(dir == OUTPUT)
    {
        size = 3;
        str_val = "out";
    }
    else
    {
        size = 2;
        str_val = "in";
    }
        
    //fprintf(str_val, "%d", (int)val);
    fd = open(path, FILE_FLAGS, FILE_PERMS);
    if(fd == -1)
    {
        printf("Error: ioctl cmd set dir open file\n");
        return ERROR;
    }
    if(write(fd, str_val, size) != size)
    {
        printf("Error : ioctl cmd set dir write file\n");
        return ERROR;
    }
    close(fd);
    return SUCCESS;
}
int ioctl_cmd_set_value(int num, gpio_value_t val)
{
    int fd;
    char name[MAX_NAME_SIZE] = {0}, number_char[MAX_PIN_SIZE] ={0};
    strcat(name, GPIO_PREFIX);
    sprintf(number_char, "%d", num);
    strcat(name, number_char);
    char path[MAX_PATH_SIZE]={0};
    strcat(path, GPIO_PATH);
    strcat(path, name);
    strcat(path, VALUE);
    char str_val;
    fprintf(str_val, "%d", (int)val);
    fd = open(path, FILE_FLAGS, FILE_PERMS);
    if(fd == -1)
    {
        printf("Error: ioctl cmd set value open file\n");
        return ERROR;
    }
    if(write(fd, &str_val, 1) != 1)
    {
        printf("Error : ioctl set value write file\n");
        return ERROR;
    }
    close(fd);
    return SUCCESS;
}
int ioctl_cmd_get_value(int num, gpio_value_t* val)
{
    int fd;
    char name[MAX_NAME_SIZE] = {0}, number_char[MAX_PIN_SIZE] ={0};
    strcat(name, GPIO_PREFIX);
    sprintf(number_char, "%d", num);
    strcat(name, number_char);
    char path[MAX_PATH_SIZE]={0};
    strcat(path, GPIO_PATH);
    strcat(path, name);
    strcat(path, VALUE);
     char str_val;
    // fprintf(str_val, "%d", (int)val);
    fd = open(path, FILE_FLAGS, FILE_PERMS);
    if(fd == -1)
    {
        printf("Error: ioctl cmd set value open file\n");
        return ERROR;
    }
    if(read(fd, &str_val, 1) != 1)
    {
        printf("Error : ioctl set value write file\n");
        return ERROR;
    }
    int tmp = atoi(&str_val);
    *val = (gpio_value_t)tmp;
    close(fd);
    return SUCCESS;
}

int ioctl_cmd_get_dir(int num, direction_t* val)
{
    int fd, size = 3;
    char name[MAX_NAME_SIZE] = {0}, number_char[MAX_PIN_SIZE] ={0};
    strcat(name, GPIO_PREFIX);
    sprintf(number_char, "%d", num);
    strcat(name, number_char);
    char path[MAX_PATH_SIZE]={0};
    strcat(path, GPIO_PATH);
    strcat(path, name);
    strcat(path, DIRECTION);
    char str_val[size];
    fd = open(path, FILE_FLAGS, FILE_PERMS);
    if(fd == -1)
    {
        printf("Error: ioctl cmd get dir open file\n");
        return ERROR;
    }
    if(read(fd, str_val, size) != size)
    {
        printf("Error : ioctl cmd get dir write file\n");
        return ERROR;
    }
    if(strcmp(str_val, "out") == 0)
    {
        *val = OUTPUT;
    }
    else if(strcmp(str_val, "in") == 0)
    {
        *val = INPUT;
    }
    close(fd);
    return SUCCESS;
}
int ioctl_cmd_get_active_low(int num, active_low_t* val)
{
    int fd;
    char name[MAX_NAME_SIZE] = {0}, number_char[MAX_PIN_SIZE] ={0};
    strcat(name, GPIO_PREFIX);
    sprintf(number_char, "%d", num);
    strcat(name, number_char);
    char path[MAX_PATH_SIZE]={0};
    strcat(path, GPIO_PATH);
    strcat(path, name);
    strcat(path, ACTIVE_LOW);
    char str_val;
    // fprintf(str_val, "%d", (int)val);
    fd = open(path, FILE_FLAGS, FILE_PERMS);
    if(fd == -1)
    {
        printf("Error: ioctl cmd get active low open file\n");
        return ERROR;
    }
    if(read(fd, &str_val, 1) != 1)
    {
        printf("Error : ioctl get active low write file\n");
        return ERROR;
    }
    int tmp = atoi(&str_val);
    *val = (active_low_t)tmp;
    close(fd);
    return SUCCESS;
}