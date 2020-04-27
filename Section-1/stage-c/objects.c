#include "objects.h"

/***** Definition for Objects ******/
objects_t objects = {
    /*0x1000*/ { 0x04, 0x00, 0x00, 0x00, 0x00 },
    /*0x1001*/ { 0x03, 0x00, 0x00, 0x00 },
    /*0x1002*/ 0x110,
    /*0x1003*/ 0xABCDEF12,
    /*0x2000*/ 0x50,
    /*0x2001*/ 0x10
};

/***** Definition for Sub-indexes ******/
const Obj_subIndex_t LED_Service_1000[5] = {
    { (void*)&objects.LED_Service.noSubIndex, OBJ_READABLE, 1 },
    { (void*)&objects.LED_Service.LED1, (OBJ_READABLE + OBJ_WRITEABLE), 1 },
    { (void*)&objects.LED_Service.LED2, (OBJ_READABLE + OBJ_WRITEABLE), 1 },
    { (void*)&objects.LED_Service.LED3, (OBJ_READABLE + OBJ_WRITEABLE), 1 },
    { (void*)&objects.LED_Service.LED4, (OBJ_READABLE + OBJ_WRITEABLE), 1 },
};

const Obj_subIndex_t PWM_Service_1001[4] = {
    { (void*)&objects.PWM_Service.noSubIndex, OBJ_READABLE, 1 },
    { (void*)&objects.PWM_Service.CH1_Duty, (OBJ_READABLE + OBJ_WRITEABLE), 1 },
    { (void*)&objects.PWM_Service.CH2_Duty, (OBJ_READABLE + OBJ_WRITEABLE), 1 },
    { (void*)&objects.PWM_Service.PWM_Status, OBJ_READABLE, 2 },
};



/***** Definition for main index ******/
const Obj_index_t index_objects[NOF_INDEX_ARRAY]=
{
{0x1000, 0x05, 0x0, 0, (void*)&LED_Service_1000},
{0x1001, 0x04, 0x0, 0, (void*)&PWM_Service_1001},
{0x1002, 0x00, (OBJ_READABLE + OBJ_WRITEABLE), 4, (void*)&objects.value_1},
{0x1003, 0x00, (OBJ_READABLE), 4, (void*)&objects.value_2},
{0x2000, 0x00, (OBJ_READABLE + OBJ_WRITEABLE), 2, (void*)&objects.value_3},
{0x2001, 0x00, (OBJ_READABLE + OBJ_WRITEABLE), 1, (void*)&objects.value_4},
};
