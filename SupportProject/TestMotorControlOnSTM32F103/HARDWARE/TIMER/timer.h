#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

//ͨ���ı�TIM1->CCR1��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
#define LED0_PWM_VAL TIM1->CCR1
 
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);
#endif






















