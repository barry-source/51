#include "carFunction.h"
#include "reg52.h"
#include "motor.h"
#include "sg90.h"
#include "timer.h"
#include "time.h"
#include "hc04.h"
#include "su03t.h"
#include "oled.h"
#include "UART.h"

#define MIDDLE 0
#define LEFT 1
#define RIGHT 2

//跟随
sbit leftFollow = P2^5;
sbit rightFollow = P2^4;
// 寻迹
sbit leftTracing = P2^7;
sbit rightTracing = P2^6;

double disLeft = 0;
double disMiddle = 0;
double disRight = 0;
char dir = MIDDLE;

enum Mode lastMode = stop;

void follow() {
		if(mode != lastMode) {
			lastMode = mode;
			oled_clear();
			Oled_Show_Str(2, 0, "----follow----");
		}
		if(leftFollow == 0 && rightFollow == 0) {
			forward();
		}
		
		if(leftFollow == 1 && rightFollow == 0) {
			rightward();
		} 
		
		if(leftFollow == 0 && rightFollow == 1) {
			leftward();
		}
		
		if(leftFollow == 1 && rightFollow == 1) {
			stop();
		}
}

void avoid() {	
	if(mode != lastMode) {
		lastMode = mode;
		oled_clear();
		Oled_Show_Str(2, 0, "----avoid----");
	}
	if(dir != MIDDLE) {
			dir = MIDDLE;
			turn90degree();
			Delay300ms();
		}
		disMiddle = getDistanceByUltrasonicWave();
		
		if(disMiddle > 35) {
			forward();
		} else if(disMiddle < 10) {
			backward();
		} else {
			stop();
			turn180degree();
			Delay300ms();
			disLeft = getDistanceByUltrasonicWave();
			
			turn90degree();
			Delay300ms();
			
			turn0degree();
			dir = RIGHT;
			Delay300ms();
			disRight = getDistanceByUltrasonicWave();
			
			if(disLeft < disRight) {
				rightward();
				Delay150ms();
				stop();
			} 
			if(disLeft > disRight){
				leftward();
				Delay150ms();
				stop();
			}
		}
}

void traceing() {
	if(mode != lastMode) {
		lastMode = mode;
		oled_clear();
		Oled_Show_Str(2, 0, "----trace----");
	}
	
	if(leftTracing == 0 && rightTracing == 0) {
		/*
		leftSpeed = Phase;
		rightSpeed = Phase-10;
		*/
		forward();
	}
	
	if(leftTracing == 1 && rightTracing == 0) {
		/*
		leftSpeed = Phase - 70;
		rightSpeed = Phase;
		*/
		leftward();
	} 
	
	if(leftTracing == 0 && rightTracing == 1) {
		/*
		leftSpeed = Phase;
		rightSpeed = Phase - 70;
		*/
		rightward();
	}
	
	if(leftTracing == 1 && rightTracing == 1) {
		stop();
	}
}


void init() {
	
	// timer0(舵机，测速)
	timer0Init();
	// 避障
	timer1InitWithoutInterrupt();
	Delay300ms();
	Delay300ms();
	// 舵机转成正方向
	turn90degree();
	Delay300ms();
	oled_init();
	oled_clear();
	Oled_Show_Str(2, 0, "----ready----");
	//uart_init();
}


void timer0_handler() interrupt 1 {
	sg90_timer0();
}

/*
void timer1_handler() interrupt 3 {
	
}
*/