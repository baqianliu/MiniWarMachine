[toc]
## demoC文件分析
* 定义函数，将函数列表挂载到自定义的类，再类挂载到自定义的模块上，再初始化模块
#### 1. 定义内部字段
*   ```c
    typedef struct
    {
        PyObject_HEAD
        int id;
        PyObject *username;
        int age;
        PyObject *address;
    } UserObject;
    ```
* 内部字段定义为一个结构体，相当于python中定义class的字段，在初始化函数中根据这个模版分配内存并产生新的类。
* 关于[PyObject_HEAD](https://zhuanlan.zhihu.com/p/137760766)，是Python内部定义的一个宏，python中每一个对象的开始字节都是相同的头部
* 关于[PyObject](https://www.w3cschool.cn/article/29330845.html)，是定义Python对象的基础结构体
#### 2. [定义函数，添加到函数列表](https://segmentfault.com/a/1190000015724170)
* 实现函数接口
    * ```c
            static PyObject *User_user_info(UserObject *self, PyObject *Py_UNUSED(ignored))
            {
                //coding...
                return PyUnicode_FromFormat("%d %S %d %S", self->id, self->username, self->age, self->address);
            }
        ```
    * **PyObject self**是Python内部使用的, **PyObject args**包揽所有传给函数的参数，它是一个参数列表，所有参数都被整合到一  个string中，我们需要使用**PyArg_ParseTuple**来解开参数列表。
* 定义方法列表，并添加自定义的函数接口
    *   ```c
        static PyMethodDef User_methods[] = {
            {"user_info", (PyCFunction)User_user_info, METH_NOARGS, "this fuction will display."},
            {NULL, NULL, 0, NULL} /* Sentinel */
        };
        ```
    * PyMethodDef结构体中，
        ```c
        struct PyMethodDef {
            const char  *ml_name;   /* 在Python中使用的方法名 */
            PyCFunction ml_meth;    /* C模块内的函数名 */
            int         ml_flags;   /* Combination of METH_xxx flags, which mostly describe the args expected by the C func */
            const char  *ml_doc;    /* The __doc__ attribute, or NULL */
        };
        ```
    * 这个列表的最后必须以 {NULL, NULL, 0, NULL} 的形式来代表声明结束 

#### 3. 定义调用类，挂在方法列表
* 定义我们所编写的C函数如何被Python调用
*   ```c
    static PyTypeObject UserType = {
        PyVarObject_HEAD_INIT(NULL, 0)                                          //
        .tp_name = "demoCToPythonCPart.User",                                   //类名
        .tp_doc = "This text will be displayed in the class documentation.",    //此处的字符串降作为模块的python doc出现，可在python中通过__doc__调用
        .tp_basicsize = sizeof(UserObject),                                     //为了告诉python需要分配多少内存
        .tp_itemsize = 0,                                                       //如果不是长度可以变化的类，此处总是为0
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                   //定义类的类型掩码，所有的类都应该包含Py_TPFLAGS_DEFAULT，所以也是固定写法，不用特别在意。后面会引入一些其他类型掩码
        .tp_new = User_new,                                                     //要创建对象，必须提供tp_new处理程序，相当于Python函数__new__()，但必须显式指定。在本例中，我们使用API函数User_new()提供的默认实现
        .tp_init = (initproc)User_init,                                         //
        .tp_dealloc = (destructor)User_dealloc,                                 //
        .tp_members = User_members,                                             //
        .tp_methods = User_methods,                                             //挂载自定义的方法列表
    };
    ```
* [PyTypeObject](https://blog.csdn.net/zhangyifei216/article/details/50581787)这个结构体可以定义新的类型，控制了对象的行为
#### 4. 定义初始化模块，挂载自定义类
*   ```c
    static PyModuleDef demoCToPythonCPart = {
        PyModuleDef_HEAD_INIT,
        .m_name = "demoCToPythonCPart",                                         //模块名称
        .m_doc = "This text will appear in the module's documentation.",
        .m_size = -1,
    };
    ```
* 定义init函数，创建模块，再将自定义的类`User`挂载到模块`demoCToPythonCPart`上来
*   ```c
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
    ```
* Python内存回收管理[Py_INCREF() 和 Py_DECREF()](https://www.zybuluo.com/dream-cheny/note/346447)

## 生成库文件命令
```shell
    python setup.py install #安装库，默认路径
    python setup.py install --prefix=D:/lib #指定库的生成路径
```

## 参考链接
* [【Python】使用C语言编写Python扩展模块，史诗级详细](https://blog.csdn.net/bitekong/article/details/119954575)
* [python包管理工具setup参数](https://www.cnblogs.com/potato-chip/p/9106225.html)
* [ Python 的 setup.py](https://zhuanlan.zhihu.com/p/276461821)
* [python包的安装函数及设置安装路径](https://blog.csdn.net/sowhatgavin/article/details/81912541)