#include "reg52.h"
#include "sg90.h"

int cnt = 0;
int phase = 1;
sbit pulse = P1^1; // sg90 signal

void reset() {
	cnt = 0;
	//TL0 = 0;
	//TH0 = 0;
}

void sg90Init() {
	TMOD &= 0XF0;
	TMOD |= 0X01;
	TL0 = 0X33;
	TH0 = 0XFE;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void turn0degree() {
	phase = 1;
	reset();
}

void turn90degree() {
	reset();
	phase = 3;
}

void turn180degree() {
	phase = 5;
	reset();
}

/*
void timer0_pwm() interrupt 1 {
	cnt ++;
	TL0 = 0X33;
	TH0 = 0XFE;
	if (cnt < phase) {
		pulse = 1;
	} else {
		pulse = 0;
	}
	if (cnt == 40) {
		pulse = 1;
		cnt = 0;
	}
}
*/
