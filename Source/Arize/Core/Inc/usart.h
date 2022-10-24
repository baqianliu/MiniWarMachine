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

#define USART_REC_LEN               200              //定义最大接收字节数 200
#define EN_USART1_RX                1                //使能（1）/禁止（0）串口1接收
#define RXBUFFERSIZE                1                //缓存大小
#define UART_RTOR_BAUD_BIT          22               //向寄存器填入需要超时的长度，单位为一个波特时长，2个字节*11波特长度=22

typedef enum
{
    UART_RXSTA_READY    = 0x0000,                   //接收空状态
    UART_RXSTA_WORKING  = 0x4000,                   //接收到一帧中第一个字节后到接收完成前的状态
    UART_RXSTA_COMPLETE = 0x8000                    //接收完成状态
}USARTRXState;

typedef struct
{
    uint8_t bUsartRxBuf[USART_REC_LEN];             //接收缓冲,最大USART_REC_LEN个字节.

    uint16_t wUartRxCounter;                         //串口1帧接收字节计数

    uint16_t wUsartRxSta;                            //接收状态标记
                                                     //bit15     接收完成标志
                                                     //bit14     接收到0x0d
                                                     //bit13~0   接收到的有效字节数目

    uint8_t* bUsartTxBuf;                            //发送缓冲

    uint16_t wUartTxCounter;                         //串口需要发送的字节总数

    uint32_t wTempUartTxSize;                        //串口当前发送的字节数
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
