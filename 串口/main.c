#include "reg52.h"
#include <intrins.h>
#include <string.h>

sfr AUXR = 0x8E;
sbit led = P3^7;
sbit led1 = P3^6;
char buffer[12];

code char LJWL[]  = "AT+CWJAP=\"tsc000\",\"010203123\"\r\n";
code char LJFWQ[] = "AT+CIPSTART=\"TCP\",\"192.168.0.104\",8880\r\n"; 

char TCMS[]  = "AT+CIPMODE=1\r\n";
char SJCS[]  = "AT+CIPSEND\r\n";
char RESET[] = "AT+RST\r\n";

int AT_OK_Flag = 0;
int AT_Connect_OK_Flag = 0;
int failed = 0;

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

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

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

void connectWifi() {
	Delay1000ms();
	sendString(LJWL);
	while(!AT_OK_Flag);
	AT_OK_Flag = 0;
	sendString(LJFWQ);
	while(!AT_OK_Flag);
	AT_OK_Flag = 0;
	sendString(TCMS);
	while(!AT_OK_Flag);
	AT_OK_Flag = 0;
	sendString(SJCS);
	while(!AT_OK_Flag);
}


void main() {
	uart_init();
	label:
	connectWifi();
	if(AT_Connect_OK_Flag) {
		led = 0;
	} 
	
	if(AT_OK_Flag) {
		led1 = 0;
	}
	while(1) {
		if(failed) {
			failed = 0;
			goto label;
		}
		Delay1000ms();
		sendString("jump");
	}
}

void UART_Handle() interrupt 4 {
	static i = 0;
	char temp;
	if(RI) {
		RI = 0;
		temp = SBUF;
		if(temp == 'W' || temp == 'O' || temp == 'L' || temp == 'F') {
			i = 0;
		}
		buffer[i++] = temp;
		if(buffer[0] == 'O' && buffer[1] == 'K') {
			AT_OK_Flag = 1;
			memset(buffer,'\0', 12);
		}
		if(buffer[0] == 'W' && buffer[5] == 'G') {
			AT_Connect_OK_Flag = 1;
			memset(buffer,'\0', 12);
		}
		if(buffer[0] == 'L' && buffer[2] == '1') {
			led= 0;
			memset(buffer,'\0', 12);
		}
		if(buffer[0] == 'L' && buffer[2] == '0') {
			led= 1;
			memset(buffer,'\0', 12);
		}
		if(buffer[0] == 'F' && buffer[1] == 'A'){
				for(i=0;i<5;i++){
					led = 0;
					Delay1000ms();
					led = 1;
					Delay1000ms();
				}
				failed = 1;
				AT_OK_Flag = 0;
				AT_Connect_OK_Flag =0;
				sendString(RESET);
				memset(buffer, '\0', 12);
			}
		if (i >= 12) {
			i = 0;
		}
	}
}
