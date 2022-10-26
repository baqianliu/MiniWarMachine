[toc]

## 用C添加 MicroPython module
#### 新建CToMicroPythonModule.c
* 如CToMicroPythonModule.c文件中，先创建mp_rom_map_elem_t类型的table，再定义DICT，再声明mp_obj_module_t类型的moduule，将DICT绑定上来
#### 将c文件添加到Makefile
* 最新版本的esp-idf开发环境需要使用新的工具idf.py来编译、烧录程序
* 添加CToMicroPythonModule.c到编译源文件列表
#### 注册新建的模块
* 在mpconfigport.h文件中添加新建的mudule

## 参考链接
* [MicroPython开发之--用C添加接口（添加module）](https://blog.csdn.net/solar_Lan/article/details/88913109)