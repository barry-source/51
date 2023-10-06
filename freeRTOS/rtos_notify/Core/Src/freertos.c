/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Task1Handle;
osThreadId Task2Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
EventGroupHandle_t eventgroup_handle;

/* USER CODE END FunctionPrototypes */

void TaskOne(void const * argument);
void TaskTwo(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */ 
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task1 */
  osThreadDef(Task1, TaskOne, osPriorityNormal, 0, 128);
  Task1Handle = osThreadCreate(osThread(Task1), NULL);

  /* definition and creation of Task2 */
  osThreadDef(Task2, TaskTwo, osPriorityIdle, 0, 128);
  Task2Handle = osThreadCreate(osThread(Task2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	eventgroup_handle = xEventGroupCreate();
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_TaskOne */
/**
  * @brief  Function implementing the Task1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskOne */
void TaskOne(void const * argument)
{
  /* USER CODE BEGIN TaskOne */
	uint32_t rtn = 0;
  /* Infinite loop */
  for(;;)
  {
		
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		{
			osDelay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
			{
				printf("按键1\r\n");
				xTaskNotify(Task2Handle, 1, eSetValueWithOverwrite);
			}
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);
		}
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
		{
			osDelay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
			{
				printf("按键2\r\n");
				xTaskNotify(Task2Handle, 2, eSetValueWithOverwrite);
			}
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET);
		}
		/*
		
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		{
			osDelay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
			{
				printf("0bit写1\r\n");
				xTaskNotify(Task2Handle, 0x01, eSetBits);
			}
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);
		}
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
		{
			osDelay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
			{
				printf("1bit写1\r\n");
				xTaskNotify(Task2Handle, 0x02, eSetBits);
			}
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET);
		}
		*/
		
		/*
    // 等待 KEY1 按下
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		{
			osDelay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
			{
				printf("key1按下\r\n");
				rtn = xTaskNotifyGive(Task2Handle);
				printf("返回值：%d\r\n", rtn);
			}
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);
		}
		*/
		osDelay(10);
  }
  /* USER CODE END TaskOne */
}

/* USER CODE BEGIN Header_TaskTwo */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskTwo */
void TaskTwo(void const * argument)
{
  /* USER CODE BEGIN TaskTwo */
	uint32_t rev = 0;
	uint32_t notify_val = 0, event_bit = 0;
  /* Infinite loop */
  for(;;)
  {
		xTaskNotifyWait(0, 0xFFFFFFFF, &notify_val, portMAX_DELAY);
		printf("接收到的通知值为：%d\r\n", notify_val);
		
		/*
		xTaskNotifyWait(0, 0xffffffff, &notify_val, portMAX_DELAY);
		if (notify_val & 0x01)
			event_bit |= 0x01;
		if (notify_val & 0x02)
			event_bit |= 0x02;
		if (event_bit == (0x01 | 0x02))
		{
			printf("接收成功！\r\n");
			event_bit = 0;
		}
		*/
		
		/*
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
		{
			osDelay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
			{
				// true 是二值信号量
				//rev = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
				// 计数信号量
				rev = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
				if(rev != 0) {
					printf("接收完成: %d\r\n", rev);
				} else {
					printf("接收错误");
				}
			}
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET);
		}
		*/
		osDelay(1);
  }
  /* USER CODE END TaskTwo */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

