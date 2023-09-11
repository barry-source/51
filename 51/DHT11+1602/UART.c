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
	SCON = 0x40; //���ô��ڹ�����ʽ1��REN��ʹ�ܽ���
	TMOD &= 0xF0;
	TMOD |= 0x20;//��ʱ��1������ʽλ8λ�Զ���װ
	
	TH1 = 0xFD;
	TL1 = 0xFD;//9600�����ʵĳ�ֵ
	TR1 = 1;//������ʱ��
	*/
	
	AUXR = 0x01;
	TMOD &= 0X0F;
	TMOD |= 0X20;
	SCON = 0X50;
	TH1 = 0XFD;
	TL1 = 0XFD;
	TR1 = 1;
}