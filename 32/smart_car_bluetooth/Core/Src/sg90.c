#include "sg90.h"
#include "gpio.h"
#include "tim.h"

void sg90_init() {
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 17);
}

void turn_0_degree() {
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 5);
}

void turn_90_degree() {
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 17);
}


void turn_180_degree() {
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 25);
}
