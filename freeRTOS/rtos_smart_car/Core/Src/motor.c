#include "motor.h"
#include "gpio.h"
#include "tim.h"

// 目前只有A1B,和B1B接入PWM
// A1B--->A1---->TIM2_CH2
// B1B--->A0---->TIM2_CH1


#define Left_B1A_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
#define Left_B1A_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)
#define Left_B1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET)
#define Left_B1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET)
//#define Left_B1B_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET)
//#define Left_B1B_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET)

#define Right_A1A_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)
#define Right_A1A_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)
#define Right_A1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)
#define Right_A1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
//#define Right_A1B_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)
//#define Right_A1B_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)

uint8_t mode = NORMAL;

void init_port() {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
} 

void changeMode(uint8_t m) {
	mode = m;
	if(mode == NORMAL) {
		HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_2);
		init_port();
	} else {
		MX_TIM2_Init();
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
		HAL_Delay(500);
	}
}

void forward() {
	if(mode == NORMAL) {
		Left_B1A_W_0();
		Left_B1B_W_1();
		Right_A1A_W_0();
		Right_A1B_W_1();
	} else {
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,10);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,13);
	}
}

void backward() {
	if(mode == NORMAL) {
		Left_B1A_W_1();
		Left_B1B_W_0();
		Right_A1A_W_1();
		Right_A1B_W_0();
	} else {
	
	}
}

void leftward() {
	if(mode == NORMAL) {
		Left_B1A_W_0();
		Left_B1B_W_1();
		Right_A1A_W_0();
		Right_A1B_W_0();
	} else {
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,1);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,13);
	}
}

void rightward() {
	if(mode == NORMAL) {
		Left_B1A_W_0();
		Left_B1B_W_0();
		Right_A1A_W_0();
		Right_A1B_W_1();
	} else {
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,13);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,1);
	}
}
	
void stop() {
	if(mode == NORMAL) {
		Left_B1A_W_0();
		Left_B1B_W_0();
		Right_A1A_W_0();
		Right_A1B_W_0();
	} else {
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,0);
	}
}

