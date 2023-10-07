/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "su03.h"
#include "string.h"

#define UART1_REC_LEN 200
uint16_t UART1_RX_STA=0;
uint8_t buf=0;
// 接收缓冲, 串口接收到的数据放在这个数组里，最大UART1_REC_LEN个字节
uint8_t UART1_RX_Buffer[UART1_REC_LEN];
/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
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

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

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

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	if(huart->Instance != USART1) {
		return;
	}
	// 数据接收完成
	if((UART1_RX_STA & 0x8000) != 0) {
		HAL_UART_Receive_IT(&huart1, &buf, 1);
		return;
	}
	
	// 接收到回车之后判断后续的是不是换行，如果是换行，数据接收完成，但是还要开启一下中断
	if(UART1_RX_STA&0x4000) {
		if(buf == 0x0a) {
			UART1_RX_STA = UART1_RX_STA| 0x8000;
			if(!strcmp((const char *)UART1_RX_Buffer, "M0")) {
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
				runMode = stopMode;
			} else if(!strcmp((const char *)UART1_RX_Buffer, "M1")) {
				runMode = tracingMode;
			} else if(!strcmp((const char *)UART1_RX_Buffer, "M2")) {
				runMode = avoidMode;
			} else if(!strcmp((const char *)UART1_RX_Buffer, "M3")) {
				runMode = followMode;
			} else {
				runMode = stopMode;
			}
			memset(UART1_RX_Buffer, 0, UART1_REC_LEN);
			UART1_RX_STA = 0;
		} else {
			UART1_RX_STA = 0;
		}
	} else {
		// 接收到回车，将高第二位置1，否则继续接收数据
		if(buf == 0x0d) {
			UART1_RX_STA |= 0x4000;
		} else {
			UART1_RX_Buffer[UART1_RX_STA&0x3fff] = buf;
			UART1_RX_STA ++;
			if(UART1_RX_STA > UART1_REC_LEN - 1) {
				UART1_RX_STA = 0;
			}
		}
	}
	HAL_UART_Receive_IT(&huart1, &buf, 1);
}
/* USER CODE END 1 */
