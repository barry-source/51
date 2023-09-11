#include "reg52.h"
#include <intrins.h>
#include <string.h>

#define dataBuffer P0;

sbit led = P3^7;
sbit SDA = P0^3;
sbit SCL = P0^1;

void iic_start() {
	SDA = 1;
	SCL = 1;
	_nop_();
	SDA = 0;
	_nop_();
}

void iic_stop() {
	SDA = 0;
	SCL = 1;
	_nop_();
	SDA = 1;
	_nop_();
}

char iic_ack() {
	char flag;
	SDA = 1;
	_nop_();
	SCL = 1;
	flag = SDA;
	_nop_();
	SCL = 0;
	_nop_();
	return flag;
}


void iic_send_byte(char sendData) {
	int i;
	int temp = sendData;
	for(i = 0; i < 8; i ++) {
		SCL = 0;
		SDA = temp & 0x80;
		_nop_();
		SCL = 1;
		_nop_();
		// 这个忘拉低了
		SCL = 0;
		_nop_();
		temp <<= 1;
	}
}

void iic_write_cmd(char cmd) {
	iic_start();
	iic_send_byte(0x78);
	iic_ack();
	iic_send_byte(0x00);
	iic_ack();
	iic_send_byte(cmd);
	iic_ack();
	iic_stop();
}

void iic_write_data(char d) {
	iic_start();
	iic_send_byte(0x78);
	iic_ack();
	iic_send_byte(0x40);
	iic_ack();
	iic_send_byte(d);
	iic_ack();
	iic_stop();
}

void oled_clear() {
	int i, j;
	for(i = 0; i < 8; i ++) {
		iic_write_cmd(0xB0+i);
		iic_write_cmd(0x00);
		iic_write_cmd(0x10);
		for(j = 0; j < 128; j ++) {
			iic_write_data(0);
		}
	}
}

void iic_init() {

}

void Oled_Init(void){
	iic_write_cmd(0xAE);//--display off
	iic_write_cmd(0x00);//---set low column address
	iic_write_cmd(0x10);//---set high column address
	iic_write_cmd(0x40);//--set start line address  
	iic_write_cmd(0xB0);//--set page address
	iic_write_cmd(0x81); // contract control
	iic_write_cmd(0xFF);//--128   
	iic_write_cmd(0xA1);//set segment remap 
	iic_write_cmd(0xA6);//--normal / reverse
	iic_write_cmd(0xA8);//--set multiplex ratio(1 to 64)
	iic_write_cmd(0x3F);//--1/32 duty
	iic_write_cmd(0xC8);//Com scan direction
	iic_write_cmd(0xD3);//-set display offset
	iic_write_cmd(0x00);//
	
	iic_write_cmd(0xD5);//set osc division
	iic_write_cmd(0x80);//
	
	iic_write_cmd(0xD8);//set area color mode off
	iic_write_cmd(0x05);//
	
	iic_write_cmd(0xD9);//Set Pre-Charge Period
	iic_write_cmd(0xF1);//
	
	iic_write_cmd(0xDA);//set com pin configuartion
	iic_write_cmd(0x12);//
	
	iic_write_cmd(0xDB);//set Vcomh
	iic_write_cmd(0x30);//
	
	iic_write_cmd(0x8D);//set charge pump enable
	iic_write_cmd(0x14);//
	
	iic_write_cmd(0xAF);//--turn on oled panel		
}


void main() {
	Oled_Init();
	
	iic_write_cmd(0x20);
	iic_write_cmd(0x02);

	oled_clear();

	
	iic_write_cmd(0xB0);
	iic_write_cmd(0x00);
	iic_write_cmd(0x10);
	iic_write_data(0xff);
	iic_write_data(0xff);
	iic_write_data(0xff);
	iic_write_data(0xff);
	iic_write_data(0xff);
	
	iic_write_cmd(0xB5);
	iic_write_cmd(0x00);
	iic_write_cmd(0x10);
	iic_write_data(0x08);
	iic_write_data(0x08);
	iic_write_data(0x08);
	iic_write_data(0x08);
	iic_write_data(0x08);

	while(1);
}
