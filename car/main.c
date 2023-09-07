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
			leftSpeed = 40;
			rightSpeed = 35;
			//forward();
		}
		
		if(leftTracing == 1 && rightTracing == 0) {
			leftSpeed = 10;
			rightSpeed = 40;
			//leftward();
		} 
		
		if(leftTracing == 0 && rightTracing == 1) {
			leftSpeed = 40;
			rightSpeed = 10;
			//rightward();
		}
		
		if(leftTracing == 1 && rightTracing == 1) {
			stop();
		}
		
		
	}
}

