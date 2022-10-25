from distutils.core import setup, Extension

setup(name="demoCToPythonCPart",   # 命名编译、安装到python库中的文件名 PyInit_mymodel-1.0-py3.8.egg-info
      author="Arize",
      version="1.0",    # 命名编译、安装到python库中的文件名 PyInit_mymodel-1.0-py3.8.egg-info
      install_dir="./",
      include_dirs="C:/Users/z004c9kr/AppData/Local/Programs/Python/Python39",  # 导入python头文件
      ext_modules=[Extension("demoCToPythonCPart", ["demoCToPythonCPart.c"])]   # 此处demoCToPythonCPart必须与PyInit_mymodel后方命名一致。
      )

