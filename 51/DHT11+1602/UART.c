#include "UART.h"
#include "reg52.h"

sbit AUXR = 0X8E;

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
	/*
	AUXR = 0x01;
	SCON = 0x40; //配置串口工作方式1，REN不使能接收
	TMOD &= 0xF0;
	TMOD |= 0x20;//定时器1工作方式位8位自动重装
	
	TH1 = 0xFD;
	TL1 = 0xFD;//9600波特率的初值
	TR1 = 1;//启动定时器
	*/
	
	AUXR = 0x01;
	TMOD &= 0X0F;
	TMOD |= 0X20;
	SCON = 0X50;
	TH1 = 0XFD;
	TL1 = 0XFD;
	TR1 = 1;
}