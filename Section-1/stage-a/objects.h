#ifndef OBJECTS_H
#define OBJECTS_H

#include "stdint.h"

/***** Structure for Sub-indexes variables ********************************************/
/*1000    */ typedef struct {
    uint8_t noSubIndex;
    uint8_t LED1;
    uint8_t LED2;
    uint8_t LED3;
    uint8_t LED4;
} LED_Service_t;
/*1001    */ typedef struct {
    uint8_t noSubIndex;
    uint8_t CH1_Duty;
    uint8_t CH2_Duty;
    uint16_t PWM_Status;
} PWM_Service_t;

/***** Structure for all variables ********************************************/
typedef struct {
    /*1000      */ LED_Service_t LED_Service;
    /*1001      */ PWM_Service_t PWM_Service;
    /*1002      */ uint32_t value_1;
    /*1003      */ uint32_t value_2;
    /*2000      */ uint16_t value_3;
    /*2001      */ uint8_t value_4;
} Objects_t;



typedef struct {
    uint16_t            index;
    uint8_t             nof_SubIndex;
    uint16_t            length;
    uint8_t             attr;
    void               *pData;
}Obj_index_t;


#endif // OBJECTS_H
