#include "detectSpeed.h"
#include "reg52.h"

int count = 0;
int overflow = 0;
int speed;
int speedCount;

void initExt0() {
	EX0 = 1;
	EA = 1;
	IT0 = 1;
}

// ¼ÆÊ±1s
void timer0_pwm() interrupt 1 {
	count ++;
	TL0 = 0X33;
	TH0 = 0XFE;
	if (count == 2000) {
		overflow = 1;
		speed = speedCount;
		speedCount = 0;
		count = 0;
	}
}

void ex0_handler() interrupt 0 {
	speedCount ++;
}