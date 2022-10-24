#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"

typedef struct
{
    PyObject_HEAD
        int id;
    PyObject *username;
    int age;
    PyObject *address;
} UserObject;

static void User_dealloc(UserObject *self)
{
    Py_XDECREF(self->username);
    Py_XDECREF(self->address);

    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *User_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    UserObject *self;
    self = (UserObject *)type->tp_alloc(type, 0);

    if (self != NULL)
    {
        self->username = PyUnicode_FromString("");
       if (self->username == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }

       self->address = PyUnicode_FromString("");
        if (self->address == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
        self->age = 0;
    }
    return (PyObject *)self;
}

static int User_init(UserObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"id", "username", "age", "address", NULL};
    PyObject *username = NULL, *address = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "iOi|O", kwlist,
                                     &self->id,
                                     &username,
                                     &self->age,
                                     &address))
        return -1;

    if (username)
    {
        tmp = self->username;
        Py_INCREF(username);
        self->username = username;
        Py_XDECREF(tmp);
    }

    if (address)
    {
        tmp = self->address;
        Py_INCREF(address);
        self->address = address;
        Py_XDECREF(tmp);
    }
    return 0;
}

static PyMemberDef User_members[] = {
    {"id", T_INT, offsetof(UserObject, id), 0,
     "user_id"},
    {"username", T_OBJECT_EX, offsetof(UserObject, username), 0,
     "user_name"},
    {"address", T_OBJECT_EX, offsetof(UserObject, address), 0,
     "addr"},
    {"age", T_INT, offsetof(UserObject, age), 0,
     "ages"},
    {NULL} /* Sentinel */
};

static PyObject *User_user_info(UserObject *self, PyObject *Py_UNUSED(ignored))
{
    if (self->id == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "id");
        return NULL;
    }

    if (self->username == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "username");
        return NULL;
    }

    if (self->age == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "age");
        return NULL;
    }

    // if (self->address == NULL)
    // {
    //     PyErr_SetString(PyExc_AttributeError, "address");
    //     return NULL;
    // }

    return PyUnicode_FromFormat("%d %S %d %S", self->id, self->username, self->age, self->address);
}

static PyMethodDef User_methods[] = {
    {"user_info", (PyCFunction)User_user_info, METH_NOARGS,
     "this fuction will display."},
    {NULL} /* Sentinel */
};

static PyTypeObject UserType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "demoCToPythonCPart.User",
    .tp_doc = "This text will be displayed in the class documentation.",
    .tp_basicsize = sizeof(UserObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = User_new,
    .tp_init = (initproc)User_init,
    .tp_dealloc = (destructor)User_dealloc,
    .tp_members = User_members,
    .tp_methods = User_methods,
};

static PyModuleDef demoCToPythonCPart = {
    PyModuleDef_HEAD_INIT,
    .m_name = "demoCToPythonCPart",
    .m_doc = "This text will appear in the module's documentation.",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_demoCToPythonCPart(void)
{
    PyObject *m;
    if (PyType_Ready(&UserType) < 0)
        return NULL;

    m = PyModule_Create(&demoCToPythonCPart);
    if (m == NULL)
        return NULL;

    Py_INCREF(&UserType);
    if (PyModule_AddObject(m, "User", (PyObject *)&UserType) < 0)
    {
        Py_DECREF(&UserType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
