#include "timer.h"
#include "led.h"

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)
{
    if(TIM3->SR&0X0001)//����ж�
    {
        LED1=!LED1;
    }
    TIM3->SR&=~(1<<0);//����жϱ�־λ
}

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    RCC->APB1ENR|=1<<1;             //TIM3ʱ��ʹ��
    TIM3->ARR=arr;                  //�趨�������Զ���װֵ
    TIM3->PSC=psc;                  //Ԥ��Ƶ������
    TIM3->DIER|=1<<0;               //���������ж�
    TIM3->CR1|=0x01;                //ʹ�ܶ�ʱ��3
    MY_NVIC_Init(1,3,TIM3_IRQn,2);  //��ռ1�������ȼ�3����2
}

//TIM1_CH1 PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u16 arr,u16 psc)
{
    //�˲������ֶ��޸�IO������
    RCC->APB2ENR|=1<<11;        //TIM1ʱ��ʹ��
    GPIOA->CRH&=0XFFFFFFF0;     //PA8���֮ǰ������
    GPIOA->CRH|=0X0000000B;     //���ù������
    
    TIM1->ARR=arr;              //�趨�������Զ���װֵ
    TIM1->PSC=psc;              //Ԥ��Ƶ������
    
    TIM1->CCMR1|=7<<4;          //CH1 PWM2ģʽ
    TIM1->CCMR1|=1<<3;          //CH1Ԥװ��ʹ��
    TIM1->CCER|=1<<0;           //OC1 ���ʹ��
    TIM1->BDTR|=1<<15;          //MOE �����ʹ��

    TIM1->CR1=0x0080;           //ARPEʹ��
    TIM1->CR1|=0x01;            //ʹ�ܶ�ʱ��1
}  













