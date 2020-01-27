#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define GPIO_PATH   "/sys/class/gpio/"
#define EXPORT      "export"
#define UNEXPORT    "unexport"
#define GPIO_PREFIX "gpio"
#define DIRECTION   "direction"
#define ACTIVE_LOW  "active_low"
#define VALUE       "value"
#define SUCCESS     0
#define ERROR       -1
#define TRUE        1
#define FALSE       0

typedef enum export_enum{EXPORTED, UNEXPORTED}export_t;
typedef enum direction_enum{INPUT, OUTPUT}direction_t;
typedef enum active_low_enum{HIGH_ACTIVE=0, LOW_ACTIVE}active_low_t;
typedef enum gpio_value_num{LOW=0, HIGH}gpio_value_t;
typedef enum gpio_command_enum
{
    EXPORT_CMD,
    UNEXPORT_CMD,
    SET_ACTIVE_LOW_CMD, 
    SET_DIR_CMD, 
    SET_VALUE_CMD,
    GET_VALUE_CMD    
}gpio_command_t;

typedef struct {
    char* name;
    int gpio_num;
    export_t export_status;
    direction_t direction;
    active_low_t active_low;
    gpio_value_t value;
}GPIO_t;

int GPIO_Init(GPIO_t* instance);
int GPIO_Init(GPIO_t* instance,\
            int number, direction_t dir,\
            active_low_t act, gpio_value_t initVal);

int GPIO_export(GPIO_t* instance);
int GPIO_unexport(GPIO_t* instance);

int GPIO_set_active_low(GPIO_t* instance, active_low_t act);
int GPIO_set_value(GPIO_t* instance, gpio_value_t val);
int GPIO_set_direction(GPIO_t* instance, direction_t dir);

int GPIO_get_value(GPIO_t* instance, gpio_value_t* retVal);
int GPIO_get_export_status(GPIO_t* instance, export_t* retVal);
int GPIO_get_direction(GPIO_t* instance, direction_t* retVal);

int ioctl_cmd(GPIO_t* instance, gpio_command_t cmd, void* val);
int ioctl_is_exported(GPIO_t* instance);
int ioctl_cmd_export(int num);
int ioctl_cmd_unexport(int num);
int ioctl_cmd_set_active_low(int num, active_low_t val);
int ioctl_cmd_set_dir(int num, direction_t dir);
int ioctl_cmd_set_value(int num, gpio_value_t val);
int ioctl_cmd_get_value(int num, gpio_value_t* val);
