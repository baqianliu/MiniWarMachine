/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
    
#define USART_TX_Pin GPIO_PIN_9
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_10
#define USART_RX_GPIO_Port GPIOA

#define USART_REC_LEN               200              //�����������ֽ��� 200
#define EN_USART1_RX                1                //ʹ�ܣ�1��/��ֹ��0������1����
#define RXBUFFERSIZE                1                //�����С
#define UART_RTOR_BAUD_BIT          22               //��Ĵ���������Ҫ��ʱ�ĳ��ȣ���λΪһ������ʱ����2���ֽ�*11���س���=22

typedef enum
{
    UART_RXSTA_READY    = 0x0000,                   //���տ�״̬
    UART_RXSTA_WORKING  = 0x4000,                   //���յ�һ֡�е�һ���ֽں󵽽������ǰ��״̬
    UART_RXSTA_COMPLETE = 0x8000                    //�������״̬
}USARTRXState;

typedef struct
{
    uint8_t bUsartRxBuf[USART_REC_LEN];             //���ջ���,���USART_REC_LEN���ֽ�.

    uint16_t wUartRxCounter;                         //����1֡�����ֽڼ���

    uint16_t wUsartRxSta;                            //����״̬���
                                                     //bit15     ������ɱ�־
                                                     //bit14     ���յ�0x0d
                                                     //bit13~0   ���յ�����Ч�ֽ���Ŀ

    uint8_t* bUsartTxBuf;                            //���ͻ���

    uint16_t wUartTxCounter;                         //������Ҫ���͵��ֽ�����

    uint32_t wTempUartTxSize;                        //���ڵ�ǰ���͵��ֽ���
}UART_DRIVE;

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */


void USART1_Init(uint32_t bound);
uint8_t uart1_send(uint8_t *pData, uint16_t Size);
void ChangeUSARTRxState(UART_DRIVE* usart_drive, USARTRXState usart_rxState);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
