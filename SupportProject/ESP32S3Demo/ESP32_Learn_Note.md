# 编译
* 请进入 工程 hello_world 目录
> cd %userprofile%\esp\hello_world

* 设置 ESP32-S3 为目标芯片
> idf.py set-target esp32c3

* 然后运行工程配置工具 menuconfig。
> idf.py menuconfig

 idf.py menuconfig --help  #命令，获取配置工具更多信息。
 
 * 编译工程
 idf.py build
 
 * 烧录工程
> idf.py -p PORT flash
  idf.py -p COM3 flash
 
 监视输出
> idf.py -p PORT monitor 
  idf.py -p COM3 monitor 
 # 调试
* https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32c3/api-guides/jtag-debugging/index.html
* 支持 IDF monitor 和 JTAG 两种调试方式

# IDF监视器
* https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32c3/api-guides/tools/idf-monitor.html

