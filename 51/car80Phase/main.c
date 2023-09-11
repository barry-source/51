#include "reg52.h"
#include <intrins.h>
#include "UART.h"
#include "timer.h"
#include "motor.h"

sbit leftTracing = P2^7;
sbit rightTracing = P2^6;
void main() {
	
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

