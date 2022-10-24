/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

UART_HandleTypeDef USART1_Handler;
UART_DRIVE usart1_drive;


/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance               =       USART1;
  huart1.Init.BaudRate          =       115200;
  huart1.Init.WordLength        =       UART_WORDLENGTH_8B;
  huart1.Init.StopBits          =       UART_STOPBITS_1;
  huart1.Init.Parity            =       UART_PARITY_NONE;
  huart1.Init.Mode              =       UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl         =       UART_HWCONTROL_NONE;
  huart1.Init.OverSampling      =       UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */
  
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, 3, 4);
    
  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */


void USART1_IRQHandler(void)
{ 
    uint32_t isrflags   = READ_REG(USART1_Handler.Instance->ISR);
    uint32_t cr1its     = READ_REG(USART1_Handler.Instance->CR1);
    uint32_t cr3its     = READ_REG(USART1_Handler.Instance->CR3);
    UART_HandleTypeDef *huart=&USART1_Handler;

    if (((isrflags & UART_FLAG_ORE) != RESET) &&
        (((cr1its & USART_CR1_RXNEIE) != RESET) || ((cr3its & USART_CR3_EIE) != RESET)))
    {
        __HAL_UART_DISABLE_IT(&USART1_Handler, UART_FLAG_ORE);
    }
    
    if ((__HAL_UART_GET_FLAG(&USART1_Handler, UART_FLAG_RXNE) != RESET))
    {
        usart1_drive.bUsartRxBuf[usart1_drive.wUartRxCounter] = (uint8_t)(USART1_Handler.Instance->RDR & (uint8_t)0x00FF);
        usart1_drive.wUartRxCounter++;
        if(usart1_drive.wUartRxCounter >= USART_REC_LEN-1)
        {
            usart1_drive.wUartRxCounter = 0;
        }
//        if (usart1_drive.wUsartRxSta == UART_RXSTA_READY)                                        //接收到一帧中的第一个字节
//        {
//            ChangeUSARTRxState(&usart1_drive, UART_RXSTA_WORKING);
//            usart1_drive.wUartRxCounter = 0;
//            memset(usart1_drive.bUsartRxBuf,0,sizeof(usart1_drive.bUsartRxBuf));
//            usart1_drive.bUsartRxBuf[usart1_drive.wUartRxCounter] = (uint8_t)(USART1_Handler.Instance->RDR & (uint8_t)0x00FF);
//            usart1_drive.wUartRxCounter++;
//        }
//        else if (usart1_drive.wUsartRxSta == UART_RXSTA_WORKING)                                   //进行除第一个字节外的数据处理
//        {
//            usart1_drive.bUsartRxBuf[usart1_drive.wUartRxCounter] = (uint8_t)(USART1_Handler.Instance->RDR & (uint8_t)0x00FF);
//            usart1_drive.wUartRxCounter++;
//        }
    }

    if (READ_BIT(USART1_Handler.Instance->ISR, USART_ISR_RTOF))                                  //进入超时中断
    {
        SET_BIT(USART1_Handler.Instance->ICR, USART_ICR_RTOCF);                                  //清空中断
        if (usart1_drive.wUartRxCounter > 0)
        {
            ChangeUSARTRxState(&usart1_drive, UART_RXSTA_COMPLETE);                                //接收完成了，将接收状态置为0x8000供主函数判断回显
            usart1_drive.wTempUartTxSize = 0;
        }
    }
    
    // send   USART_CR1_TXEIE  USART_IT_TXE
    if (((isrflags & USART_ISR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
    {
        if (usart1_drive.wUartTxCounter == 0)
        {
            /* Disable the UART Transmit Data Register Empty Interrupt */
            CLEAR_BIT(huart->Instance->CR1, USART_CR1_TXEIE);
            
            /* Enable the UART Transmit Complete Interrupt */
            SET_BIT(huart->Instance->CR1, USART_CR1_TCIE);
            
            USART1_Handler.gState = HAL_UART_STATE_READY;
        }
        else
        {
            huart->Instance->TDR = usart1_drive.bUsartTxBuf[(usart1_drive.wTempUartTxSize)++];
            usart1_drive.wUartTxCounter--;
        }
    }
    
    if (((isrflags & USART_ISR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
    {
        CLEAR_BIT(huart->Instance->CR1, USART_CR1_TCIE);
        USART1_Handler.gState = HAL_UART_STATE_READY;
    }
} 

/**
  * @brief 向串口发送消息API
  * @param pData:数据Buffer，Size数据大小
  * @retval 发送成功返回1，发送失败返回0
  */
uint8_t uart1_send(uint8_t *pData, uint16_t Size)
{
    if ( pData == NULL || Size <= 0u )
        return 0;
    else
    {
        usart1_drive.bUsartTxBuf = pData;
        usart1_drive.wUartTxCounter = Size;
        usart1_drive.wTempUartTxSize= 0;
        
        //打开发送数据寄存器是否为空使能
        SET_BIT(USART1_Handler.Instance->CR1, USART_CR1_TXEIE);
        return 1;
    }
}

static uint8_t s_u8ChangeUSARTRxStateFlag = 0;
/** void ChangeUSARTRxState(UART_DRIVE* usart_drive, USARTRXState usart_rxState)
 *@brief 对USART Rx状态进行改变
 *@param usart_drive,串口操作句柄； usart_rxState,串口将要成为的Rx状态
 */
void ChangeUSARTRxState(UART_DRIVE* usart_drive, USARTRXState usart_rxState)
{
    if ( s_u8ChangeUSARTRxStateFlag == 0 )
    {
        s_u8ChangeUSARTRxStateFlag = 1;
        usart_drive->wUsartRxSta = usart_rxState;
        s_u8ChangeUSARTRxStateFlag = 0;
    }
}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
