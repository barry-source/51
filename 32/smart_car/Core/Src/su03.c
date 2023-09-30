#include "su03.h"
#include "gpio.h"

#define SU_A25_Value() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11)
#define SU_A26_Value() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)
#define SU_A27_Value() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)

// Ä¬ÈÏstopMode
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
	
	if(SU_A25_Value() == GPIO_PIN_RESET && SU_A26_Value() == GPIO_PIN_RESET && SU_A27_Value() == GPIO_PIN_RESET) {
		runMode = stopMode;
	}
	return runMode;
}
