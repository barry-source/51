#include "sensor.h"

GPIO_PinState leftTraceValue() {
	return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3);
}

GPIO_PinState rightTraceValue() {
	return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
}

GPIO_PinState leftFollowValue() {
	return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
}

GPIO_PinState rightFollowValue() {
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
}
