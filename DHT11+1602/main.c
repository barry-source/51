#include "reg52.h"
#include <string.h>
#include "time.h"
#include "DHT.h"
#include "LCD.h"
#include "UART.h"

sbit led = P3^7;

char temp[8];
char huma[8];

void Build_Datas()
{
	huma[0] = 'H';
	huma[1] = datas[0]/10 + 0x30;
	huma[2] = datas[0]%10 + 0x30;
	huma[3] = '.';
	huma[4] = datas[1]/10 + 0x30;
	huma[5] = datas[1]%10 + 0x30;
	huma[6] = '%';
	huma[7] = '\0';
	
	temp[0] = 'T';
	temp[1] = datas[2]/10 + 0x30;
	temp[2] = datas[2]%10 + 0x30;
	temp[3] = '.';
	temp[4] = datas[3]/10 + 0x30;
	temp[5] = datas[3]%10 + 0x30;
	temp[6] = 'C';
	temp[7] = '\0';
	
}

void main() {
	char temp1[] = "hello everyone!"; 
	char position = 0x80;
	int i = 0;
	
	uart_init();
	lcd_init();
	
	Delay1000ms();
	Delay1000ms();
	/*
	write_cmd(position);
	for(i = 0; i < 15;i ++) {
		write_data(temp1[i]);
		delay_ms(10);
		
	}
	*/
	//check_DHT();
	while(1) {
		delay_ms(500);
		
		trigDHT();
		receiveData();
		Build_Datas();
		
		sendString(huma);
		sendString("\r\n");
		sendString(temp);
		sendString("\r\n");
		
		write_cmd(position);
		for(i = 0; i < 7;i ++) {
			write_data(huma[i]);
		}
		write_cmd(position + 0x40);
		for(i = 0; i < 7;i ++) {
			write_data(temp[i]);
		}
	}
	
}
