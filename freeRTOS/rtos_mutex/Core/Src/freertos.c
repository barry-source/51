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
osThreadId TaskLowHandle;
osThreadId TaskMHandle;
osThreadId TaskHighHandle;
osMutexId myMutexHandle;
osSemaphoreId myBinaryHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TaskLowEntry(void const * argument);
void Task02(void const * argument);
void Task3(void const * argument);

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
  /* Create the mutex(es) */
  /* definition and creation of myMutex */
  osMutexDef(myMutex);
  myMutexHandle = osMutexCreate(osMutex(myMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinary */
  osSemaphoreDef(myBinary);
  myBinaryHandle = osSemaphoreCreate(osSemaphore(myBinary), 1);

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
  /* definition and creation of TaskLow */
  osThreadDef(TaskLow, TaskLowEntry, osPriorityBelowNormal, 0, 128);
  TaskLowHandle = osThreadCreate(osThread(TaskLow), NULL);

  /* definition and creation of TaskM */
  osThreadDef(TaskM, Task02, osPriorityNormal, 0, 128);
  TaskMHandle = osThreadCreate(osThread(TaskM), NULL);

  /* definition and creation of TaskHigh */
  osThreadDef(TaskHigh, Task3, osPriorityAboveNormal, 0, 128);
  TaskHighHandle = osThreadCreate(osThread(TaskHigh), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_TaskLowEntry */
/**
  * @brief  Function implementing the TaskLow thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskLowEntry */
void TaskLowEntry(void const * argument)
{
  /* USER CODE BEGIN TaskLowEntry */
  /* Infinite loop */
  for(;;)
  {
		
		xSemaphoreTake(myMutexHandle, portMAX_DELAY);
		printf("TaskL:正在执行任务...\r\n");
		HAL_Delay(1000);
		printf("TaskL：任务执行完成...\r\n");
		xSemaphoreGive(myMutexHandle);
		osDelay(1000);
		/*
    xSemaphoreTake(myBinaryHandle, portMAX_DELAY);
		printf("TaskL:正在执行任务...\r\n");
		HAL_Delay(1000);
		printf("TaskL：任务执行完成...\r\n");
		xSemaphoreGive(myBinaryHandle);
		osDelay(1000);
		*/
  }
  /* USER CODE END TaskLowEntry */
}

/* USER CODE BEGIN Header_Task02 */
/**
* @brief Function implementing the TaskM thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task02 */
void Task02(void const * argument)
{
  /* USER CODE BEGIN Task02 */
  /* Infinite loop */
  for(;;)
  {
		printf("TaskM:穿插任务...\r\n");
    osDelay(1000);
  }
  /* USER CODE END Task02 */
}

/* USER CODE BEGIN Header_Task3 */
/**
* @brief Function implementing the TaskHigh thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task3 */
void Task3(void const * argument)
{
  /* USER CO DE BEGIN Task3 */
  /* Infinite loop */
  for(;;)
  {
		
		xSemaphoreTake(myMutexHandle, portMAX_DELAY);
		printf("TaskH:正在执行任务...\r\n");
		HAL_Delay(1000);
		printf("TaskH：任务执行完成...\r\n");
		xSemaphoreGive(myMutexHandle);
		/*
		xSemaphoreTake(myBinaryHandle, portMAX_DELAY);
		printf("TaskH:正在执行任务...\r\n");
		HAL_Delay(1000);
		printf("TaskH：任务执行完成...\r\n");
		xSemaphoreGive(myBinaryHandle);
		*/
    osDelay(1000);
  }
  /* USER CODE END Task3 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

