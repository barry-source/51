#include "motor.h"
#include "gpio.h"

// 目前只有A1B,和B1B接入PWM
// A1B--->A1---->TIM2_CH2
// B1B--->A0---->TIM2_CH1


//#define Left_B1A_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
//#define Left_B1A_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)
//#define Left_B1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET)
//#define Left_B1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET)
//#define Left_B1B_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET)
//#define Left_B1B_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET)

//#define Right_A1A_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)
//#define Right_A1A_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)
//#define Right_A1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)
//#define Right_A1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
//#define Right_A1B_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)
//#define Right_A1B_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)

// 小车右后为A，右前为B，左后为C，左前为D,所有电平默认都是低电平
// 左前
#define Left_D1A_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)	
#define Left_D1A_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)
#define Left_D1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define Left_D1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
// 左后
#define Left_C1A_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define Left_C1A_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define Left_C1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)
#define Left_C1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
// 右前
#define Right_B1A_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)
#define Right_B1A_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)
#define Right_B1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)
#define Right_B1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
// 右后
#define Right_A1A_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET)
#define Right_A1A_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET)
#define Right_A1B_W_1() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET)
#define Right_A1B_W_0() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET)

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
}

void forward() {
	// 左前
	Left_D1A_W_0();
	Left_D1B_W_1();
	// 右前
	Right_B1A_W_0();
	Right_B1B_W_1();
	// 左后
	Left_C1A_W_1();
	Left_C1B_W_0();
	// 右后
	Right_A1A_W_1();
	Right_A1B_W_0();
}

void backward() {
	// 左前
	Left_D1A_W_1();
	Left_D1B_W_0();
	// 右前
	Right_B1A_W_1();
	Right_B1B_W_0();
	// 左后
	Left_C1A_W_0();
	Left_C1B_W_1();
	// 右后
	Right_A1A_W_0();
	Right_A1B_W_1();
}

void leftward() {
	// 左前
	Left_D1A_W_1();
	Left_D1B_W_0();
	// 右前
	Right_B1A_W_0();
	Right_B1B_W_1();
	// 左后
	Left_C1A_W_0();
	Left_C1B_W_1();
	// 右后
	Right_A1A_W_1();
	Right_A1B_W_0();
}

void rightward() {
	// 左前
	Left_D1A_W_0();
	Left_D1B_W_1();
	// 右前
	Right_B1A_W_1();
	Right_B1B_W_0();
	// 左后
	Left_C1A_W_1();
	Left_C1B_W_0();
	// 右后
	Right_A1A_W_0();
	Right_A1B_W_1();
}

void hor_leftward() {
	// 左前
	Left_D1A_W_1();
	Left_D1B_W_0();
	// 右前
	Right_B1A_W_0();
	Right_B1B_W_1();
	// 左后
	Left_C1A_W_1();
	Left_C1B_W_0();
	// 右后
	Right_A1A_W_0();
	Right_A1B_W_1();
}

void hor_rightward() {
	// 左前
	Left_D1A_W_0();
	Left_D1B_W_1();
	// 右前
	Right_B1A_W_1();
	Right_B1B_W_0();
	// 左后
	Left_C1A_W_0();
	Left_C1B_W_1();
	// 右后
	Right_A1A_W_1();
	Right_A1B_W_0();
}
	
void stop() {
	if(mode == NORMAL) {
		
	} else {
		
	}
}

