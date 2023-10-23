#include "motor.h"
#include "gpio.h"

// Ŀǰֻ��A1B,��B1B����PWM
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

// С���Һ�ΪA����ǰΪB�����ΪC����ǰΪD,���е�ƽĬ�϶��ǵ͵�ƽ
// ��ǰ
#define Left_D1A_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)	
#define Left_D1A_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)
#define Left_D1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define Left_D1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
// ���
#define Left_C1A_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define Left_C1A_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define Left_C1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)
#define Left_C1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
// ��ǰ
#define Right_B1A_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)
#define Right_B1A_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)
#define Right_B1B_W_1() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)
#define Right_B1B_W_0() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
// �Һ�
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
	// ��ǰ
	Left_D1A_W_0();
	Left_D1B_W_1();
	// ��ǰ
	Right_B1A_W_0();
	Right_B1B_W_1();
	// ���
	Left_C1A_W_1();
	Left_C1B_W_0();
	// �Һ�
	Right_A1A_W_1();
	Right_A1B_W_0();
}

void backward() {
	// ��ǰ
	Left_D1A_W_1();
	Left_D1B_W_0();
	// ��ǰ
	Right_B1A_W_1();
	Right_B1B_W_0();
	// ���
	Left_C1A_W_0();
	Left_C1B_W_1();
	// �Һ�
	Right_A1A_W_0();
	Right_A1B_W_1();
}

void leftward() {
	// ��ǰ
	Left_D1A_W_1();
	Left_D1B_W_0();
	// ��ǰ
	Right_B1A_W_0();
	Right_B1B_W_1();
	// ���
	Left_C1A_W_0();
	Left_C1B_W_1();
	// �Һ�
	Right_A1A_W_1();
	Right_A1B_W_0();
}

void rightward() {
	// ��ǰ
	Left_D1A_W_0();
	Left_D1B_W_1();
	// ��ǰ
	Right_B1A_W_1();
	Right_B1B_W_0();
	// ���
	Left_C1A_W_1();
	Left_C1B_W_0();
	// �Һ�
	Right_A1A_W_0();
	Right_A1B_W_1();
}

void hor_leftward() {
	// ��ǰ
	Left_D1A_W_1();
	Left_D1B_W_0();
	// ��ǰ
	Right_B1A_W_0();
	Right_B1B_W_1();
	// ���
	Left_C1A_W_1();
	Left_C1B_W_0();
	// �Һ�
	Right_A1A_W_0();
	Right_A1B_W_1();
}

void hor_rightward() {
	// ��ǰ
	Left_D1A_W_0();
	Left_D1B_W_1();
	// ��ǰ
	Right_B1A_W_1();
	Right_B1B_W_0();
	// ���
	Left_C1A_W_0();
	Left_C1B_W_1();
	// �Һ�
	Right_A1A_W_1();
	Right_A1B_W_0();
}
	
void stop() {
	if(mode == NORMAL) {
		
	} else {
		
	}
}

