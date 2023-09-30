#include "car_function.h"
#include "stm32f1xx_hal.h"
#include "su03.h"
#include "sg90.h"
#include "sr04.h"
#include "motor.h"
#include "tim.h"
#include "sensor.h"
#include "oled.h"

#define MIDDLE 0
#define LEFT 1
#define RIGHT 2

double disLeft = 0;
double disMiddle = 0;
double disRight = 0;
char dir = MIDDLE;

enum Mode lastMode = stopMode;

void follow() {
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		HAL_Delay(100);
		// 处理oled
		oled_clear();
		oled_show_string(2,2,"-----Follow----");
	}
	return ;
	if(leftFollowValue() == GPIO_PIN_RESET && rightFollowValue() == GPIO_PIN_RESET) {
		forward();
	}
	if(leftFollowValue() == GPIO_PIN_RESET && rightFollowValue() == GPIO_PIN_SET) {
		leftward();
	}
	if(leftFollowValue() == GPIO_PIN_SET && rightFollowValue() == GPIO_PIN_RESET) {
		rightward();
	}
	if(leftFollowValue() == GPIO_PIN_SET && rightFollowValue() == GPIO_PIN_SET) {
		stop();
	}
}

void avoid() {
		if(runMode != lastMode) {
			lastMode = runMode;
			changeMode(NORMAL);
			HAL_Delay(500);
			// 处理oled
			oled_clear();
			oled_show_string(2,2,"-----Avoid----");
		}
		return ;
		if(dir != MIDDLE) {
			dir = MIDDLE;
			turn_90_degree();
			HAL_Delay(300);
		}
		disMiddle = get_distance();
		
		if(disMiddle > 35) {
			forward();
		} else if(disMiddle < 10) {
			backward();
		} else {
			stop();
			turn_180_degree();
			HAL_Delay(300);
			disLeft = get_distance();
			
			turn_90_degree();
			HAL_Delay(300);
			
			turn_0_degree();
			dir = RIGHT;
			HAL_Delay(300);
			disRight = get_distance();
			
			if(disLeft < disRight) {
				rightward();
				HAL_Delay(150);
				stop();
			} 
			if(disLeft > disRight){
				leftward();
				HAL_Delay(150);
				stop();
			}
		}

}

void traceing() {
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(PWM);
		HAL_Delay(500);
		// 处理oled
		oled_clear();
		oled_show_string(2,2,"-----Tracing----");
	}
	return ;
	if(leftTraceValue() == GPIO_PIN_RESET && rightTraceValue() == GPIO_PIN_RESET) {
		forward();
	}
	if(leftTraceValue() == GPIO_PIN_RESET && rightTraceValue() == GPIO_PIN_SET) {
		leftward();
	}
	if(leftTraceValue() == GPIO_PIN_SET && rightTraceValue() == GPIO_PIN_RESET) {
		rightward();
	}
	if(leftTraceValue() == GPIO_PIN_SET && rightTraceValue() == GPIO_PIN_SET) {
		stop();
	}
}

void stop_car() {
	if(runMode != lastMode) {
		lastMode = runMode;
		oled_clear();
		oled_show_string(2,2,"-----Stop----");
	}
}

void init() {

}
