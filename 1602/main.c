#include "reg52.h"
#include <intrins.h>
#include <string.h>

#define dataBuffer P0;

sbit led = P3^7;
sbit RS = P1^0;
sbit RW = P1^1;
sbit EN = P1^4;

void Delay15ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 27;
	j = 226;
	do
	{
		while (--j);
	} while (--i);
}

void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 9;
	j = 244;
	do
	{
		while (--j);
	} while (--i);
}

// 忙检测
void busy_check() {
	char temp = 0x80;
	P0 = 0X80;
	while(temp & 0x80) {
		RS = 0;
		RW = 1;
		EN = 0;
		_nop_(); // tscp
		EN = 1;
		_nop_(); // td
		temp = P0;
		EN = 0;
	}
}

void write_cmd(char cmd) {
	busy_check();
	RS = 0; // 写地址
	RW = 0;
	EN = 0;
	P0 = cmd;
	_nop_();
	_nop_();
	_nop_();
	EN = 1;
	_nop_();
	EN = 0;
}

void write_data(char d) {
	busy_check();
	RS = 1;
	RW = 0;
	EN = 0;
	P0 = d;
	_nop_();
	EN = 1;
	_nop_();
	_nop_();
	_nop_();
	EN = 0;
}

void init() {
	
	
	Delay15ms();
	write_cmd(0x38);
	Delay5ms();
	write_cmd(0x38);
	write_cmd(0x08);
	write_cmd(0x01);
	write_cmd(0x06);
	write_cmd(0x0c);
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



void main() {
	char temp[] = "hello everyone!"; 
	char position = 0x80;
	char dataShow = 'C';
	int i = 0;
	init();
	write_cmd(position);//选择要显示的地址
	for(i = 0; i < 15;i ++) {
		write_data(temp[i]);
		Delay1000ms();
		
	}
	//write_data(dataShow);//发送要显示的字符
	while(1);
}
