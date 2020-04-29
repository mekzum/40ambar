#include <stdio.h>
#include "obj_control.h"

extern const Obj_index_t index_objects[NOF_INDEX_ARRAY];

static Obj_control_t obj_control;

Obj_control_t* control;

int main()
{

    control = &obj_control;

    control->obj_index = index_objects;

    control->nof_index = NOF_INDEX_ARRAY;

    Obj_Error_Code err;

    /****************** Write Test *******************************/
    uint32_t data = 0x12345678;

    Obj_setUint32(obj_control.databuffer, data);

    err = obj_write(&obj_control, 0x1002, 0);

    if (err == OBJ_ERR_SUCCESS)
        printf("Index:0x%X subIndex:%X data:0x%X\n",
               obj_control.obj_arg.index,
               obj_control.obj_arg.subIndex,
               Obj_getUint32(obj_control.databuffer));
    else
        printf("Write Data Error Code: %d\n", err);
    /**************************************************************/


    /****************** Read Error Test *******************************/
    err = obj_read(control, 0x1001, 6);
    if (err != OBJ_ERR_SUCCESS)
        printf("Read Data Error Code: %d\n", err);
    /******************************************************************/

    return 0;
}
