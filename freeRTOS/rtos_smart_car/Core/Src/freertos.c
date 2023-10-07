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
#include "motor.h"
#include "su03.h"
#include "car_function.h"
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
osThreadId AvoidHandle;
osThreadId TracingHandle;
osThreadId FollowHandle;
osThreadId MicrophoneHandle;
osThreadId GestureHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TaskAvoid(void const * argument);
void TaskTracing(void const * argument);
void TaskFollow(void const * argument);
void TaskMicrophone(void const * argument);
void TaskGesture(void const * argument);

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
  /* definition and creation of Avoid */
  osThreadDef(Avoid, TaskAvoid, osPriorityNormal, 0, 128);
  AvoidHandle = osThreadCreate(osThread(Avoid), NULL);

  /* definition and creation of Tracing */
  osThreadDef(Tracing, TaskTracing, osPriorityLow, 0, 128);
  TracingHandle = osThreadCreate(osThread(Tracing), NULL);

  /* definition and creation of Follow */
  osThreadDef(Follow, TaskFollow, osPriorityLow, 0, 128);
  FollowHandle = osThreadCreate(osThread(Follow), NULL);

  /* definition and creation of Microphone */
  osThreadDef(Microphone, TaskMicrophone, osPriorityNormal, 0, 128);
  MicrophoneHandle = osThreadCreate(osThread(Microphone), NULL);

  /* definition and creation of Gesture */
  osThreadDef(Gesture, TaskGesture, osPriorityLow, 0, 128);
  GestureHandle = osThreadCreate(osThread(Gesture), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	vTaskSuspend(AvoidHandle);
	vTaskSuspend(TracingHandle);
	vTaskSuspend(FollowHandle);
	//vTaskSuspend(GestureHandle);
	
	
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_TaskAvoid */
/**
  * @brief  Function implementing the Avoid thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskAvoid */
void TaskAvoid(void const * argument)
{
  /* USER CODE BEGIN TaskAvoid */
  /* Infinite loop */
  for(;;)
  {
		forward();
    osDelay(1);
  }
  /* USER CODE END TaskAvoid */
}

/* USER CODE BEGIN Header_TaskTracing */
/**
* @brief Function implementing the Tracing thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskTracing */
void TaskTracing(void const * argument)
{
  /* USER CODE BEGIN TaskTracing */
  /* Infinite loop */
  for(;;)
  {
		//forward();
    osDelay(100);
  }
  /* USER CODE END TaskTracing */
}

/* USER CODE BEGIN Header_TaskFollow */
/**
* @brief Function implementing the Follow thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskFollow */
void TaskFollow(void const * argument)
{
  /* USER CODE BEGIN TaskFollow */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END TaskFollow */
}

/* USER CODE BEGIN Header_TaskMicrophone */
/**
* @brief Function implementing the Microphone thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskMicrophone */
void TaskMicrophone(void const * argument)
{
  /* USER CODE BEGIN TaskMicrophone */
  /* Infinite loop */
  for(;;)
  {
		/*
		TaskStatus_t  TaskStatus;
		vTaskGetInfo(GestureHandle, &TaskStatus, pdTRUE, eInvalid);
		if(TaskStatus.eCurrentState == eSuspended) {
			printf("suspend\r\n");
		}
		*/
		taskENTER_CRITICAL();
		get_mode();
		//reset();
		taskEXIT_CRITICAL();
		switch(runMode) {
			case tracingMode: 
				traceing();
				break;
			case followMode:
				follow();
				break;
			case avoidMode:
				avoid();
				break;
			case gestureMode:
				gesture();
				break;
			case testMode:
				test();
				break;
			case stopMode:
				stop();
				break;
		}
    osDelay(100);
  }
  /* USER CODE END TaskMicrophone */
}

/* USER CODE BEGIN Header_TaskGesture */
/**
* @brief Function implementing t he Gesture thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskGesture */
void TaskGesture(void const * argument)
{
  /* USER CODE BEGIN TaskGesture */
  /* Infinite loop */
  for(;;)
  {
		
		//if(runMode != gestureMode) return ;
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
    osDelay(100);
  }
  /* USER CODE END TaskGesture */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

