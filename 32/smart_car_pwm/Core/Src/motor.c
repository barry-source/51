#include "motor.h"
#include "gpio.h"

#define Left_B1A_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
#define Left_B1A_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)
#define Left_B1B_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET)
#define Left_B1B_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET)

#define Right_A1A_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)
#define Right_A1A_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)
#define Right_A1B_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)
#define Right_A1B_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)

void forward() {
	Left_B1A_W_0();
	Left_B1B_W_1();
	Right_A1A_W_0();
	Right_A1B_W_1();
}

void backward() {
	Left_B1A_W_1();
	Left_B1B_W_0();
	Right_A1A_W_1();
	Right_A1B_W_0();
}

void leftward() {
	Left_B1A_W_0();
	Left_B1B_W_0();
	Right_A1A_W_0();
	Right_A1B_W_1();
}

void rightward() {
	Left_B1A_W_0();
	Left_B1B_W_1();
	Right_A1A_W_0();
	Right_A1B_W_0();
}
	
void stop() {
	Left_B1A_W_0();
	Left_B1B_W_0();
	Right_A1A_W_0();
	Right_A1B_W_0();
}
	