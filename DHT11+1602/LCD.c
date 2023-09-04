
#include "LCD.h"
#include "reg52.h"
#include "time.h"
#include <intrins.h>

sbit RS = P1^0;
sbit RW = P1^1;
sbit EN = P1^4;

// ????
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
	RS = 0; // §Õ???
	RW = 0;
	EN = 0;
	P0 = cmd;
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
	EN = 0;;
}

void lcd_init() {
	
	
	Delay15ms();
	write_cmd(0x38);
	Delay5ms();
	write_cmd(0x38);
	write_cmd(0x08);
	write_cmd(0x01);
	write_cmd(0x06);
	write_cmd(0x0c);
}