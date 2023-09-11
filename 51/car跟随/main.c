#include "reg52.h"
#include <intrins.h>
#include "UART.h"
#include "timer.h"
#include "motor.h"

sbit leftTracing = P2^7;
sbit rightTracing = P2^6;
sbit leftIdentify = P2^5;
sbit rightIdentify = P2^4;

void trace() {
	timer0Init();
	timer1Init();
	//uart_init();

	
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

void main() {
	
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

