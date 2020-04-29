/** @file obj_control.h
 * Control of object module
 */


#ifndef OBJ_CONTROL_H
#define OBJ_CONTROL_H

#include "stdint.h"
#include "objects.h"


/**
 * Union for byte-extraction
 */
typedef union{
    uint8_t  u8[8];  /**< 8 bytes */
    uint16_t u16[4]; /**< 4 words */
    uint32_t u32[2]; /**< 2 double words */
}Obj_bytes_t;

/**
 * Object attributes. for bit masks their value are going on 2^n.
 */
typedef enum{
    OBJ_ERR_SUCCESS                 = 0x0000, /**< 0x0000 , No Error */
    OBJ_ERR_NO_INDEX                = 0x0002, /**< 0x0002 , Index has not been founded */
    OBJ_ERR_NO_SUB_INDEX            = 0x0004, /**< 0x0004 , Sub-index has not been founded */
    OBJ_ERR_WRITEONLY               = 0x0008, /**< 0x0008 , Attempt to read a write only object */
    OBJ_ERR_READONLY                = 0x0010, /**< 0x0010 , Attempt to write a read only object */
    OBJ_ERR_NULL_PARAM              = 0x0020, /**< 0x0020 , detect Null parameter */
}Obj_Error_Code;


/**
 * Structure for obj_arg
 * It's like an object control workspace.
 * It's filling temporarily user data and getting some functions value
*/
typedef struct {
    /** Pointer to object data */
    void* data;

    /** Pointer to databuffer for copy data from object data. */
    const uint8_t* databuffer;

    /** Index element number in index_struct array*/
    uint16_t i_element;

    /** Number of index. It comes from user*/
    uint16_t index;
    /** Number of sub-index. It comes from user*/
    uint8_t subIndex;

    /** Attribute. Type of variable. */
    uint8_t attr;

    /** Length of variable in bytes.*/
    uint16_t length;

} Obj_arg_t;

/**
 * Structure for object_index
*/
typedef struct {

    /** Pointer to obj_index structture array */
    const Obj_index_t* obj_index;

    /** size of obj_index structurre array */
    uint8_t nof_index;

    /** Control data buffer to copy object data.
    * It must mapped obj_arg_t data buffer  */
    uint8_t databuffer[4];

    /** See #obj_arg_t */
    Obj_arg_t obj_arg;

}Obj_control_t;


/**
 * @brief obj_read
 * @param control
 * @param index
 * @param subIndex
 * @return error code
 */
Obj_Error_Code  obj_read  (Obj_control_t *control , uint16_t index, uint8_t subIndex);


/**
 * @brief obj_write
 * @param control
 * @param index
 * @param subIndex
 * @return error code
 */
Obj_Error_Code obj_write(Obj_control_t *control , uint16_t index, uint8_t subIndex);

/******************************** General Helper Functions****************/

/**
 * Helper function returns uint16 from byte array.
 *
 * @param data Location of source data.
 * @return Variable of type uint16_t.
 */
uint16_t Obj_getUint16(const uint8_t data[]);


/**
 * Helper function returns uint32 from byte array.
 *
 * @param data Location of source data.
 * @return Variable of type uint32_t.
 */
uint32_t Obj_getUint32(const uint8_t data[]);


/**
 * Helper function writes uint16 to byte array.
 *
 * @param data Location of destination data.
 * @param value Variable of type uint16_t to be written into data.
 */
void Obj_setUint16(uint8_t data[], const uint16_t value);


/**
 * Helper function writes uint32 to byte array.
 *
 * @param data Location of destination data.
 * @param value Variable of type uint32_t to be written into data.
 */
void Obj_setUint32(uint8_t data[], const uint32_t value);

#endif // OBJ_CONTROL_H
