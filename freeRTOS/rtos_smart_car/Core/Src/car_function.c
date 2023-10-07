#include "car_function.h"
#include "stm32f1xx_hal.h"
#include "su03.h"
//#include "sg90.h"
//#include "sr04.h"
#include "motor.h"
#include "tim.h"
//#include "sensor.h"
//#include "oled.h"
//#include "dht11.h"
#include "stdio.h"
#include "usart.h"
//#include "iic_paj7620.h"

#define MIDDLE 0
#define LEFT 1
#define RIGHT 2

// С��ͷ��3.5cm
#define FRONT_DIS 3.5
// С��ͷ��7cm
#define LEFT_DIS 7

double disLeft = 0;
double disMiddle = 0;
double disRight = 0;
char dir = MIDDLE;

enum Mode lastMode = stopMode;

// ��ʪ�Ȳ���Ƶ��ˢ�£�Ӱ��С�������У��ƴ�ˢ��һ��
uint32_t count = 0;

void follow() {
	/*
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		
		// ����oled
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
	*/
}

void avoid() {
	/*
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		// ����oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : avoid");
		HAL_Delay(500);
	}

	if(dir != MIDDLE) {
		dir = MIDDLE;
		turn_90_degree();
		HAL_Delay(300);
	}
	distance = 0;
	trig();
	while(!distance);
	disMiddle = distance - FRONT_DIS;
	printf("front:%f\r\n", distance);
	if(disMiddle > 35) {
		forward();
	} else if(disMiddle < 10) {
		backward();
	} else {
		stop();
		turn_180_degree();
		HAL_Delay(300);
		distance = 0;
		trig();
		while(!distance);
		disLeft = distance - FRONT_DIS;
		printf("left:%f\r\n", distance);
		
		turn_90_degree();
		HAL_Delay(300);
		distance = 0;
		trig();
		while(!distance);
		disMiddle = distance - LEFT_DIS;
		if(disMiddle < 10) 
			backward();
		turn_0_degree();
		dir = RIGHT;
		HAL_Delay(300);
		distance = 0;
		trig();
		while(!distance);
		disRight = distance - LEFT_DIS;
		printf("right:%f\r\n", distance);
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
*/
}

void traceing() {
	/*
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(PWM);
		HAL_Delay(500);
		// ����oled
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
	*/
}

void stop_car() {
	/*
	if(runMode != lastMode) {
		lastMode = runMode;
		oled_clear_1_line();
		oled_show_string(1,2, "mode : stop");
		// ��Ҫ�Ǹ�ԭ�����ǰ��
		reset();
	}
	*/
}

void gesture() {
	/*
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		// ����oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : gesture");
		HAL_Delay(500);
	}
	paj7620_action();
	*/
}

void test() { 
	/*
	if(runMode != lastMode) {
		lastMode = runMode;
		changeMode(NORMAL);
		// ����oled
		oled_clear_1_line();
		oled_show_string(1,2,"mode : test");
		HAL_Delay(500);
	}
	*/
}
	
/*
void display_temp_humi() {
	
	if(runMode != stopMode) {
		return;
	} 
	count = 0;
	//�ǵù��жϣ������Ӱ��DHT11�ɼ�����
	HAL_TIM_Base_Stop_IT(&htim3);
	char msg[16];
	
	uint8_t result = trig_dht();
	//printf("result: %d\r\n", result);
	receive_data();
	
	oled_clear(4, 8, 56, 128);
	sprintf(msg, "Temp : %d.%d C", datas[2], datas[3]);
	oled_show_string(3,2,msg);
	sprintf(msg, "Humi : %d.%d %%", datas[0], datas[1]);
	oled_show_string(4,2,msg);;
	HAL_Delay(500);
}

void init() {
	//���������ж���������
	HAL_UART_Receive_IT(&huart1, &buf, 1);
	//����pwm������ת����ǰ��
	sg90_init();
	paj7620_init();
	//��ʼ��oled
	oled_init();
	oled_clear_all();
	oled_show_string(1,2,"mode : stop");
	oled_show_string(2,2, "speed: ----");
	oled_show_string(3,2, "Temp :--.--");
	oled_show_string(4,2, "Humi :--.--");
	
}

void reset() {
	if(runMode == followMode || runMode == tracingMode || runMode == avoidMode || runMode == gestureMode) {
		HAL_TIM_Base_Start_IT(&htim3);
	} else {
		HAL_TIM_Base_Stop_IT(&htim3);
	}
	if(runMode != tracingMode) {
		//�л�������ģʽ�������ָ����ǰ��
		turn_90_degree();
	}
}

*/
