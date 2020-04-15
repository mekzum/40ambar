#ifndef OBJECTS_H
#define OBJECTS_H

#include "stdint.h"

/***** Structure for Sub-indexes variables ******/
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

/***** Structure for all variables *********/
typedef struct {
    /*1000      */ LED_Service_t LED_Service;
    /*1001      */ PWM_Service_t PWM_Service;
    /*1002      */ uint32_t value_1;
    /*1003      */ uint32_t value_2;
    /*2000      */ uint16_t value_3;
    /*2001      */ uint8_t value_4;
}objects_t;


/**
 * Structure for object_index
*/
typedef struct {
    /** Number of index */
    uint16_t            index;
    /** Number of sub-indexes parameter. If there are no sub-index, this value is zero*/
    uint8_t             nof_SubIndex;
    /** Attribute. Type of variable. If there are no sub-index, this value is zero
    See #Obj_attr_t */
    uint8_t             attr;
     /** Length of variable in bytes. If there are no sub-index, this value is zero*/
    uint16_t            length;
    /** Pointer to data.If there are sub-index, pointer to data type is #Obj_subIndex_t */
    void               *data;
}obj_index_t;


/**
 * Structure for object_subIndex
*/
typedef struct{
    /** Pointer to data */
    void               *data;
    /** Attribute. Type of variable. See #Obj_attr_t */
    uint16_t            attr;
     /** Length of variable in bytes.*/
    uint16_t            length;
}obj_subIndex_t;


/**
 * Object attributes. for bit masks their value are going on 2^n.
 */
typedef enum{
    OBJ_WRITEABLE        = 0x0001U,  /**< Object data may write to the variable */
    OBJ_READABLE         = 0x0002U,  /**< Object data may read to the variable */

}obj_attr_t;


#endif // OBJECTS_H
