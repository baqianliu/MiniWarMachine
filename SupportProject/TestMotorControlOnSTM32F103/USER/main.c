#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"

int main(void)
{
    u8 t=11; 
    Stm32_Clock_Init(9);            //ϵͳʱ������
    delay_init(72);                 //��ʱ��ʼ��
    uart_init(72,9600);             //���ڳ�ʼ��Ϊ9600
    LED_Init();
    
    while(1)
    {
        printf("t:%d\r\n",t);
        delay_ms(500);
    }
}
