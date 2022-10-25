from machine import Pin, PWM
import utime

led_onboard =machine.Pin(25, machine.Pin.OUT)

# http://www.micropython.com.cn/en/latet/library/machine.PWM.html
# pwm0 = PWM(Pin(25))         # 从1个引脚中创建PWM对象
# pwm0.freq(1000)             # 设置频率
# pwm0.duty_u16(65536)        # 设置占空比100%
# pwm2 = PWM(Pin(2), freq=20000, duty=512) # 在同一语句下创建和配置 PWM 存在一些问题
#PWM.init(\*, freq, duty_u16, duty_ns)

pwm0 = PWM(Pin(25))      # 从1个引脚中创建PWM对象
pwm0.freq(1000)         # 设置频率
pwm0.duty_u16(0)

n = 0
while True:
#     global n
    b = 5%3
    n = (n + 1) % 65536
    pwm0.duty_u16(abs(n))          # 设置占空比
    
    #led_onboard.toggle()
#     utime.sleep(1)