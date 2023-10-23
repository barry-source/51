#include "sg90.h"
#include "gpio.h"
#include "tim.h"

void sg90_init() {
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim11, TIM_CHANNEL_1, 30);
}

void turn_0_degree() {
	__HAL_TIM_SetCompare(&htim11, TIM_CHANNEL_1, 10);
}

void turn_90_degree() {
	__HAL_TIM_SetCompare(&htim11, TIM_CHANNEL_1, 30);
}


void turn_180_degree() {
	__HAL_TIM_SetCompare(&htim11, TIM_CHANNEL_1, 50);
}
