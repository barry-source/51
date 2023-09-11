#include "UART.h"
#include "reg52.h"
#include "motor.h"
#include <string.h>

#define SIZE 12

sbit AUXR = 0X8E;

char buffer[SIZE];

void sendByte(char a) {
	SBUF = a;
	while(!TI);
	TI = 0;
}

void sendString(char *a) {
		char *p = a;
		while(*p != '\0') {
			sendByte(*p);
			p ++;
		}
}

void uart_init() {
	AUXR = 0x01;
	TMOD &= 0X0F;
	TMOD |= 0X20;
	SCON = 0X50;
	TH1 = 0XFD;
	TL1 = 0XFD;
	TR1 = 1;
	EA = 1;
	ES = 1;
}

void UART_Handle() interrupt 4 {
	static i = 0;
	char temp;
	if(RI) {
		RI = 0;
		temp = SBUF;
		if(temp == 'm') {
			i = 0;
			memset(buffer, '\0', 12);
		}
		buffer[i++] = temp;

		if(buffer[0] == 'm') {
			switch(buffer[1]) {
				case '1':
					forward();
					break;
				case '2':
					backward();
					break;
				case '3':
					leftwards();
					break;
				case '4':
					rightward();
					break;
				default:
					stop();
					break;
			}
		}

		if (i >= SIZE) {
			i = 0;
		}
	}
}
