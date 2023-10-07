#include "su03.h"
#include "gpio.h"

#define SU_A25_Value() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11)
#define SU_A26_Value() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)
#define SU_A27_Value() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)

// 默认stopMode
enum Mode runMode = stopMode;

enum Mode get_mode() {
	if(SU_A25_Value() == GPIO_PIN_RESET && SU_A26_Value() == GPIO_PIN_SET && SU_A27_Value() == GPIO_PIN_SET) {
		runMode = tracingMode;
	}
		
	if(SU_A25_Value() == GPIO_PIN_SET && SU_A26_Value() == GPIO_PIN_RESET && SU_A27_Value() == GPIO_PIN_SET) {
		runMode = followMode;
	}
	
	if(SU_A25_Value() == GPIO_PIN_SET && SU_A26_Value() == GPIO_PIN_SET && SU_A27_Value() == GPIO_PIN_RESET) {
		runMode = avoidMode;
	}
	
	if(SU_A25_Value() == GPIO_PIN_RESET && SU_A26_Value() == GPIO_PIN_RESET && SU_A27_Value() == GPIO_PIN_SET) {
		runMode = gestureMode;
	}
	
	if(SU_A25_Value() == GPIO_PIN_RESET && SU_A26_Value() == GPIO_PIN_SET && SU_A27_Value() == GPIO_PIN_RESET) {
		runMode = testMode;
	}
	
	// 这里可以定义都低为模块不存在，有空再改吧
	if(SU_A25_Value() == GPIO_PIN_RESET && SU_A26_Value() == GPIO_PIN_RESET && SU_A27_Value() == GPIO_PIN_RESET) {
		runMode = stopMode;
	}
	
	return runMode;
}
