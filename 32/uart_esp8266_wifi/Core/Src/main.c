/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//�����������ֽ��� 200���ɸ����������
#define UART1_REC_LEN 200
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t UART1_RX_STA=0;
uint8_t buf=0;
// ���ջ���, ���ڽ��յ������ݷ��������������UART1_REC_LEN���ֽ�
uint8_t UART1_RX_Buffer[UART1_REC_LEN];


char LJWL[]  = "AT+CWJAP=\"tsc000\",\"010203123\"\r\n";
char LJFWQ[] = "AT+CIPSTART=\"TCP\",\"192.168.0.104\",8881\r\n"; 

char TCMS[]  = "AT+CIPMODE=1\r\n";
char SJCS[]  = "AT+CIPSEND\r\n";
char RESTART[] = "AT+RST\r\n";

int AT_OK_Flag = 0;
int AT_Connect_OK_Flag = 0;
int AT_FAILED = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

// �����ж�
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart->Instance != USART1) {
		return;
	}
	// ���ݽ������
	if((UART1_RX_STA & 0x8000) != 0) {
		HAL_UART_Receive_IT(&huart1, &buf, 1);
		return;
	}
	// ���յ��س�֮���жϺ������ǲ��ǻ��У�����ǻ��У����ݽ�����ɣ����ǻ�Ҫ����һ���ж�
	if(UART1_RX_STA&0x4000) {
		if(buf == 0x0a) {
			UART1_RX_STA = UART1_RX_STA| 0x8000;
		// �鿴�Ƿ��յ� WIFI GOT IP
			if(!strcmp((const char *)UART1_RX_Buffer, "WIFI GOT IP")) {
				HAL_UART_Transmit(&huart2, "WIFI GOT IP\r\n", strlen("WIFI GOT IP\r\n"), 100);
				AT_Connect_OK_Flag = 1;
			}
				
			// �鿴�Ƿ��յ� OK
			if(!strcmp((const char *)UART1_RX_Buffer, "OK")) {
				HAL_UART_Transmit(&huart2, "OK\r\n", strlen("OK\r\n"), 100);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
				AT_OK_Flag = 1;
			}

			// �鿴�Ƿ��յ� FAIL
				if(!strcmp(UART1_RX_Buffer, "FAIL"))
				{
					int i = 0;
					for (i = 0; i < 5; i++)
					{
						HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
						HAL_Delay(1000);
					}
					printf(RESTART);
				}
				
				// �ƿ�ָ��
				if(!strcmp(UART1_RX_Buffer, "L-1"))
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
				
				if(!strcmp(UART1_RX_Buffer, "L-0"))
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
					
			memset(UART1_RX_Buffer, 0, UART1_REC_LEN);
			UART1_RX_STA = 0;
			
		} else {
			UART1_RX_STA = 0;
		}
	} else {
		// ���յ��س������ߵڶ�λ��1�����������������
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


void connectWifi() {
	
	printf(LJWL);
	//while(!AT_Connect_OK_Flag);
	while(!AT_OK_Flag);
	//HAL_UART_Transmit(&huart2, "��������ɹ�\r\n", strlen("��������ɹ�\r\n"), 100);
	//HAL_Delay(50);
	AT_OK_Flag = 0;
	HAL_UART_Transmit(&huart2, "��������ɹ�\r\n", strlen("��������ɹ�\r\n"), 100);
		//������������ָ��ȴ��ɹ�
	printf(LJFWQ);
	while(!AT_OK_Flag) HAL_Delay(50);
	AT_OK_Flag = 0;
	HAL_UART_Transmit(&huart2, "���ӷ������ɹ�\r\n", strlen("���ӷ������ɹ�\r\n"), 100);
	//����͸��ģʽָ��ȴ��ɹ�
	printf(TCMS);
	while(!AT_OK_Flag) HAL_Delay(50);
	AT_OK_Flag = 0;
	HAL_UART_Transmit(&huart2, "����͸���ɹ�\r\n", strlen("����͸���ɹ�\r\n"), 100);
	//����͸��ģʽָ��ȴ��ɹ�
	//�������ݴ���ָ��ȴ��ɹ�
	printf(SJCS);
	while(!AT_OK_Flag) HAL_Delay(50);
	
}


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *file) {
	unsigned char temp[1] = {ch};
	HAL_UART_Transmit(&huart1, temp, 1, 0xfff);
	return ch;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart1, &buf, 1);
	HAL_UART_Transmit(&huart2, "let's go\r\n", strlen("let's go\r\n"), 100);

	printf(LJWL);
	//while(!AT_Connect_OK_Flag);
	while(!AT_OK_Flag);
	//HAL_UART_Transmit(&huart2, "��������ɹ�\r\n", strlen("��������ɹ�\r\n"), 100);
	//HAL_Delay(50);
	AT_OK_Flag = 0;
	HAL_UART_Transmit(&huart2, "��������ɹ�\r\n", strlen("��������ɹ�\r\n"), 100);
		//������������ָ��ȴ��ɹ�
	printf(LJFWQ);
	while(!AT_OK_Flag) HAL_Delay(50);
	AT_OK_Flag = 0;
	HAL_UART_Transmit(&huart2, "���ӷ������ɹ�\r\n", strlen("���ӷ������ɹ�\r\n"), 100);
	//����͸��ģʽָ��ȴ��ɹ�
	printf(TCMS);
	while(!AT_OK_Flag) HAL_Delay(50);
	AT_OK_Flag = 0;
	HAL_UART_Transmit(&huart2, "����͸���ɹ�\r\n", strlen("����͸���ɹ�\r\n"), 100);
	//����͸��ģʽָ��ȴ��ɹ�
	//�������ݴ���ָ��ȴ��ɹ�
	printf(SJCS);
	while(!AT_OK_Flag) HAL_Delay(50);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//printf("heart beat\r\n");
		HAL_UART_Transmit(&huart2, "heart beat\r\n", strlen("heart beat\r\n"), 100);
		HAL_Delay(3000);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
