#include "reg52.h"
#include "UART.h"
#include "timer.h"
#include "motor.h"
#include "hc04.h"
#include "sg90.h"
#include "time.h"

sbit leftTracing = P2^7;
sbit rightTracing = P2^6;
sbit leftIdentify = P2^5;
sbit rightIdentify = P2^4;

#define MIDDLE 0
#define LEFT 1
#define RIGHT 2

/*
void trace() {
	timer0Init();
	timer1Init();

	while(1) {
		if(leftTracing == 0 && rightTracing == 0) {
			leftSpeed = Phase;
			rightSpeed = Phase-10;
			//forward();
		}
		
		if(leftTracing == 1 && rightTracing == 0) {
			leftSpeed = Phase - 70;
			rightSpeed = Phase;
			//leftward();
		} 
		
		if(leftTracing == 0 && rightTracing == 1) {
			leftSpeed = Phase;
			rightSpeed = Phase - 70;
			//rightward();
		}
		
		if(leftTracing == 1 && rightTracing == 1) {
			stop();
		}
		
	}
}


void identify() {
	while(1) {
		if(leftIdentify == 0 && rightIdentify == 0) {
			forward();
		}
		
		if(leftIdentify == 1 && rightIdentify == 0) {
			rightward();
		} 
		
		if(leftIdentify == 0 && rightIdentify == 1) {
			leftward();
		}
		
		if(leftIdentify == 1 && rightIdentify == 1) {
			stop();
		}
		
	}
}

*/

void main() {
	double disLeft = 0;
	double disMiddle = 0;
	double disRight = 0;
	
	char dir;
	sg90Init();
	initTimer1();
	
	turn90degree();
	Delay300ms();
	Delay300ms();
	dir = MIDDLE;
	
	while(1) {
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
}

