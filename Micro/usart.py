from machine import UART     #　导入串口模块
import utime

uart0 = UART(0, 115200)       #　初始化一个串口　


# uart.read()                  # 读取所有收到的信息

while True:
    uart0.write('abc')            # 发送abc三个字符
    utime.sleep(1)