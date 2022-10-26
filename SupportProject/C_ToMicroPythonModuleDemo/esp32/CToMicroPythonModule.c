#include "stdint.h"
#include "stdio.h"

#include "../../../ThirdParty/micropython/py/obj.h"
#include "../../../ThirdParty/micropython/py/runtime.h"

//define globle dictionary, then we can add type and function here
STATIC const mp_rom_map_elem_t CToMicroPythonModule_global_table[] = {
    {MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_CToMicroPythonMoudule)},//correspond micropython __name__ property
};

//register CToMicroPythonModule_global_table to mp_module_CToMicroPythonModule_globals
STATIC MP_DEFINE_CONST_DICT(mp_module_CToMicroPythonModule_globals, CToMicroPythonModule_global_table);

//define a module type
const mp_obj_module_t mp_module_CToMicroPythonModule = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&mp_module_CToMicroPythonModule_globals;
}