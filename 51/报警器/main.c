#include "reg52.h"
#include <intrins.h>

sbit led1 = P3^7;
sbit led2 = P3^6;
sbit key1 = P2^1;
sbit key2 = P2^0;
sbit vibrate = P3^3;
sbit electriRelay = P1^1;
sbit wire1 = P1^2;
sbit wire2 = P1^3;
 
int alarmOpened = 0;

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);   
}

void Delay2000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 15;
	j = 2;
	k = 235;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}


/*
void twinking() {
	while(1) {
		led1 = 0;
		Delay500ms();
		led1 = 1;
		Delay500ms();
	}
}
*/

/*
void ledControledByKey() {
	led1 = 1;
	while(1) {
		if (!key1) {
			Delay100ms();
			if(!key1) {
				led1 = !led1;
			}
		}
	}
}
*/

void ledControledByVibration() {
	while(1) {
		if(!vibrate) {
			led1 = 0;
			Delay2000ms();
			led1 = 1;
		} else {
			led1 = 1;
		}
	}
}

void electricRelayByVibration() {
	while(1) {
		if(!vibrate) {
			electriRelay = 0;
			Delay2000ms();
			electriRelay = 1;
		} else {
			electriRelay = 1;
		}
	}
}

void relayControlledByWireless() {
	while(1) {
		if(wire1) {
			electriRelay = 0;
		} 
		if(wire2){
			electriRelay = 1;
		}
	}
} 

void simpleAlarm() {
	while(1) {
		if(wire1) {
			electriRelay = 0;
			Delay2000ms();
			electriRelay = 1;
			alarmOpened = 1;
		}
		if(wire2) {
			electriRelay = 0;
			Delay500ms();
			electriRelay = 1;
			alarmOpened  = 0;
		}
		if(alarmOpened) {
			electriRelay = vibrate;
		}
	}
}


void main() {
	simpleAlarm();
}
