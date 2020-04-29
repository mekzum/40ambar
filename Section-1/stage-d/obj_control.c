#include "obj_control.h"

uint16_t Obj_getUint16(const uint8_t data[])
{
    Obj_bytes_t b;
    b.u8[0] = data[0];
    b.u8[1] = data[1];
    return b.u16[0];
}

uint32_t Obj_getUint32(const uint8_t data[])
{
    Obj_bytes_t b;
    b.u8[0] = data[0];
    b.u8[1] = data[1];
    b.u8[2] = data[2];
    b.u8[3] = data[3];
    return b.u32[0];
}

void Obj_setUint16(uint8_t data[], const uint16_t value)
{
    Obj_bytes_t b;
    b.u16[0] = value;
    data[0] = b.u8[0];
    data[1] = b.u8[1];
}

void Obj_setUint32(uint8_t data[], const uint32_t value)
{
    Obj_bytes_t b;
    b.u32[0] = value;
    data[0] = b.u8[0];
    data[1] = b.u8[1];
    data[2] = b.u8[2];
    data[3] = b.u8[3];
}

/**
 * @brief Find Object in Index Object Array
 * @param control
 * @return Obj_Error_Code
 */
static Obj_Error_Code findObject(Obj_control_t* control)
{
    if(control == 0 /*NULL*/)
        return  OBJ_ERR_NULL_PARAM;

    const Obj_index_t* indexListHead;

    uint16_t index = control->obj_arg.index;

    for (int i = 0; i < control->nof_index; i++) {
        indexListHead = &control->obj_index[i];

        if (indexListHead->index == index) {
            control->obj_arg.i_element = i;

            return OBJ_ERR_SUCCESS;
        }
    }

    return OBJ_ERR_NO_INDEX;
}

/**
 * @brief Get Object Address
 * @param control
 * @return Obj_Error_Code
 */
static Obj_Error_Code getObjectAddress(Obj_control_t* control)
{

    if(control == 0 /*NULL*/)
        return  OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) { /* Object is index type */
        control->obj_arg.data = object->data;
    }
    else if (object->nof_SubIndex < control->obj_arg.subIndex) {
        /* Object is sub-index type but sub-index is out of bounds */
        return OBJ_ERR_NO_SUB_INDEX;
    }
    else { /* Object is sub-index type*/
        control->obj_arg.data = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].data;
    }

    return OBJ_ERR_SUCCESS;
}

/**
 * @brief Get Object Lenght
 * @param control
 * @return Obj_Error_Code
 */
static Obj_Error_Code getObjectLenght(Obj_control_t* control)
{
    if(control == 0 /*NULL*/)
        return  OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) { /* Object is index type */
        control->obj_arg.length = object->length;
    }
    else if (object->nof_SubIndex < control->obj_arg.subIndex) {
        /* Object is sub-index type but sub-index is out of bounds */
        return OBJ_ERR_NO_SUB_INDEX;
    }
    else { /* Object is sub-index type*/
        control->obj_arg.length = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].length;
    }

    return OBJ_ERR_SUCCESS;
}

/**
 * @brief Get Object Attr
 * @param control
 * @return Obj_control_t
 */
static Obj_Error_Code getObjectAttr(Obj_control_t* control)
{

    if(control == 0 /*NULL*/)
        return  OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if (object->nof_SubIndex == 0U) { /* Object is index type */
        control->obj_arg.attr = object->attr;
    }
    else if (object->nof_SubIndex < control->obj_arg.subIndex) {
        /* Object is sub-index type but sub-index is out of bounds */
        return OBJ_ERR_NO_SUB_INDEX;
    }
    else { /* Object is sub-index type*/
        control->obj_arg.attr = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].attr;
    }

    return OBJ_ERR_SUCCESS;
}

/**
 * @brief Init Write Read
 * @param control
 * @param index
 * @param subIndex
 * @return Obj_Error_Code
 */
static Obj_Error_Code initWriteRead(Obj_control_t* control, uint16_t index, uint8_t subIndex)
{

    if(control == 0 /*NULL*/)
        return  OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;

    control->obj_arg.index = index;
    control->obj_arg.subIndex = subIndex;

    /* find object in index array */
    err = findObject(control);
    if (err != OBJ_ERR_SUCCESS)
        return err;

    /* get object address to odf_arg*/
    err = getObjectAddress(control);
    if (err != OBJ_ERR_SUCCESS)
        return err;

    /* get object lenght to odf_arg*/
    err = getObjectLenght(control);
    if (err != OBJ_ERR_SUCCESS)
        return err;

    /* get object attribute to odf_arg*/
    err = getObjectAttr(control);
    if (err != OBJ_ERR_SUCCESS)
        return err;

    control->obj_arg.databuffer =  (const uint8_t *)&control->databuffer;

    return OBJ_ERR_SUCCESS;
}

Obj_Error_Code obj_read(Obj_control_t* control, uint16_t index, uint8_t subIndex)
{
    if(control == 0 /*NULL*/)
        return  OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;

    /* find object and fill arg. in index array */
    err = initWriteRead(control, index, subIndex);
    if (err != OBJ_ERR_SUCCESS)
        return err;

    /* start to copy data */
    uint8_t* buffer = (uint8_t *) control->obj_arg.databuffer;
    uint8_t* Objectdata = (uint8_t*)control->obj_arg.data;
    uint8_t length = control->obj_arg.length;

    /* is object readable? */
    if ((control->obj_arg.attr & OBJ_READABLE) == 0)
        return OBJ_ERR_WRITEONLY; /* attempt to read a write-only object */

    /* copy data from object to buffer*/
    if (Objectdata != 0) {
        while (length--)
            *(buffer++) = *(Objectdata++);
        // memcpy(buffer, Objectdata, lenght);
    }

    return OBJ_ERR_SUCCESS;
}

Obj_Error_Code obj_write(Obj_control_t* control, uint16_t index, uint8_t subIndex)
{
    if(control == 0 /*NULL*/)
        return  OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;

    /* find object and fill arg. in index array */
    err = initWriteRead(control, index, subIndex);
    if (err != OBJ_ERR_SUCCESS)
        return err;

    /* start to copy data */
    uint8_t* buffer =  ( uint8_t *)control->obj_arg.databuffer;
    uint8_t* Objectdata = (uint8_t*)control->obj_arg.data;
    uint8_t length = control->obj_arg.length;

    /* is object writeable? */
    if ((control->obj_arg.attr & OBJ_WRITEABLE) == 0)
        return OBJ_ERR_READONLY; /* attempt to write a read-only object */

    /* copy data from buffer to object*/
    if (Objectdata != 0) {
        while (length--)
            *(Objectdata++) = *(buffer++);
        // memcpy(buffer, Objectdata, lenght);
    }

    return OBJ_ERR_SUCCESS;
}
