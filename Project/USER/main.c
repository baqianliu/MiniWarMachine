#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"

int main(void)
{
    u8 t=11; 
    Stm32_Clock_Init(9);            //系统时钟设置
    delay_init(72);                 //延时初始化
    uart_init(72,9600);             //串口初始化为9600
    LED_Init();
    
    while(1)
    {
        printf("t:%d\r\n",t);
        delay_ms(500);
    }
}

