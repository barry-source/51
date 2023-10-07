#include "sg90.h"
#include "gpio.h"
#include "tim.h"

void sg90_init() {
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	// 这里需要加些延时PWM才能运行，裸机模式就不需要加
	HAL_Delay(100);
	turn_90_degree();
}

void turn_0_degree() {
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 5);
}

void turn_90_degree() {
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 15);
}


void turn_180_degree() {
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 25);
}
