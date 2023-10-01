#include "car_function.h"
#include "stm32f1xx_hal.h"
#include "su03.h"
#include "sg90.h"
#include "sr04.h"
#include "motor.h"
#include "tim.h"
#include "sensor.h"
#include "oled.h"
#include "dht11.h"
#include "stdio.h"
#include "usart.h"

#define MIDDLE 0
#define LEFT 1
#define RIGHT 2

double disLeft = 0;
double disMiddle = 0;
double disRight = 0;
char dir = MIDDLE;

enum Mode lastMode = stopMode;

// 温湿度不能频繁刷新，影响小车的运行，计次刷新一次
uint32_t count = 0;

void follow() {
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		
		// 处理oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : follow");
		HAL_Delay(100);
	}

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
			// 处理oled
			oled_clear_1_line();
			oled_show_string(1,2,"mode : avoid");
			HAL_Delay(500);
		}

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
		oled_clear_1_line();
		oled_show_string(1,2,"mode : trace");
	}

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
		oled_clear_1_line();
		oled_show_string(1,2, "mode : stop");
	}
}

void display_temp_humi() {
	
	if(runMode != stopMode) {
		return;
		/*
		// 停止模式时正常检测湿度，非停止模式，计数50w检测一次
		count ++;
		if(count <= 500000) { return; }
		count = 0;
		*/
	} 
	count = 0;
	//记得关中断，否则会影响DHT11采集数据
	HAL_TIM_Base_Stop_IT(&htim3);
	char msg[16];
	
	uint8_t result = trig_dht();
	//printf("result: %d\r\n", result);
	receive_data();
	printf("test1");
	
	oled_clear(4, 8, 56, 128);
	sprintf(msg, "Temp : %d.%d C", datas[2], datas[3]);
	oled_show_string(3,2,msg);
	sprintf(msg, "Humi : %d.%d %%", datas[0], datas[1]);
	oled_show_string(4,2,msg);;
	HAL_Delay(500);
}

void init() {
	//开启串口中断蓝牙在用
	HAL_UART_Receive_IT(&huart1, &buf, 1);
	//开启pwm，并旋转至最前方
	sg90_init();
	//初始化oled
	oled_init();
	oled_clear_all();
	oled_show_string(1,2,"mode : ready");
	oled_show_string(2,2, "speed:   0cm/s");
	oled_show_string(3,2, "Temp :--.--");
	oled_show_string(4,2, "Temp :--.--");
}

void reset() {
	if(runMode == followMode || runMode == tracingMode) {
		HAL_TIM_Base_Start_IT(&htim3);
	}
	if(runMode != tracingMode) {
		//切换到其它模式，将舵机指向正前方
		turn_90_degree();
	}
}

