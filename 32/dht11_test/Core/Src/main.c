
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
#include "gpio.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int fputc(int ch, FILE *file) {
	unsigned char temp[1] = {ch};
	HAL_UART_Transmit(&huart1, temp, 1, 0xfff);
	return ch;
}

void dht_mode(uint32_t mode)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = mode;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define DHT_W_1()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)
#define DHT_W_0()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)
#define DHT_R() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

 void delay_us(__IO uint32_t delay) {
    int last, curr, val;
    int temp;

    while (delay != 0) { 
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - 72 * temp;
        if (curr >= 0){
            do{
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        } else{
            curr += 72 * 1000;
            do{
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}
 
char datas[5];
char temp[8];
char huma[8];

void check_dht() {
	dht_mode(GPIO_MODE_OUTPUT_PP);
	DHT_W_1();
	DHT_W_0();
	delay_us(30000);
	DHT_W_1();
	delay_us(60);
	dht_mode(GPIO_MODE_INPUT);
	while(!DHT_R());
}

void trig_dht() {
	dht_mode(GPIO_MODE_OUTPUT_PP);
	DHT_W_1();
	DHT_W_0();
	delay_us(30000);
	DHT_W_1();
	delay_us(60);
	dht_mode(GPIO_MODE_INPUT);
	while(DHT_R());
	while(!DHT_R());
	while(DHT_R());
}

void receiveData() {
	char value;
	char tmp;
	int i, j;
	for(i = 0; i < 5;i ++) {
		for(j = 0; j < 8; j ++) {
			while(!DHT_R()); // 检测是否从50us的低电平拉高
			delay_us(40); // 0 是26-28us， 1 是70us，选择中间值，另外40-26 < 50us,未越过数据开始的低电平范围
			dht_mode(GPIO_MODE_INPUT);
			if(DHT_R() == 1) {
				value = 1;
				while(DHT_R()); // 检测到1 检测下一次数据
			} else {
				value = 0;
			} 
			tmp <<= 1;
			tmp += value;
		}
		datas[i] = tmp;
	}
}


void Build_Datas()
{
	huma[0] = 'H';
	huma[1] = datas[0]/10 + 0x30;
	huma[2] = datas[0]%10 + 0x30;
	huma[3] = '.';
	huma[4] = datas[1]/10 + 0x30;
	huma[5] = datas[1]%10 + 0x30;
	huma[6] = '%';
	huma[7] = '\0';
	
	temp[0] = 'T';
	temp[1] = datas[2]/10 + 0x30;
	temp[2] = datas[2]%10 + 0x30;
	temp[3] = '.';
	temp[4] = datas[3]/10 + 0x30;
	temp[5] = datas[3]%10 + 0x30;
	temp[6] = 'C';
	temp[7] = '\0';
	
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */
	printf("begin------\r\n");
	HAL_Delay(2000);
	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_Delay(1000);
		trig_dht();
		receiveData();
		Build_Datas();
		printf("%s\r\n", temp);
		printf("%s\r\n", huma);
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
