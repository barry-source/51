#include "sr04.h"
#include "gpio.h"
#include "tim.h"


void time1_delay_us(uint16_t n) {
	__HAL_TIM_ENABLE(&htim1);
	__HAL_TIM_SetCounter(&htim1, 0);
	while(__HAL_TIM_GetCounter(&htim1) < (n - 1));
	__HAL_TIM_DISABLE(&htim1);
}

double get_distance() {

	int cnt = 0;
	//trig 要保持至少10us的高电平
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	time1_delay_us(20);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET);
	HAL_TIM_Base_Start(&htim1);
	__HAL_TIM_SetCounter(&htim1, 0);
	
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_SET);
	HAL_TIM_Base_Stop(&htim1);
	
	cnt = __HAL_TIM_GetCounter(&htim1);
	return 340 * 0.000001 * cnt * 100 / 2;
}
