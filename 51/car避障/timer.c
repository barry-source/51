#include "reg52.h"
#include "timer.h"
#include "motor.h"

int leftSpeed = Phase;
int timer0Cnt = 0;

int rightSpeed = Phase;
int timer1Cnt = 0;

void timer0Init() {
	TMOD &= 0XF0;
	TMOD |= 0X01;
	TL0 = 0X33;
	TH0 = 0XFE;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void timer1Init() {
	TMOD &= 0X0F;
	TMOD |= 0X10;
	TL1 = 0X33;
	TH1 = 0XFE;
	TR1 = 1;
	ET1 = 1;
	EA = 1;
}


/*
void timer0_pwm() interrupt 1 {
	timer0Cnt ++;
	TL0 = 0X33;
	TH0 = 0XFE;
	if (timer0Cnt < leftSpeed) {
		leftForward();
	} else {
		leftStop();
	}
	if (timer0Cnt == Phase) {
		timer0Cnt = 0;
	}
}

void timer1_pwm() interrupt 3 {
	timer1Cnt ++;
	TL1 = 0X33;
	TH1 = 0XFE;
	if (timer1Cnt < rightSpeed) {
		rightForward();
	} else {
		rightStop();
	}
	if (timer1Cnt == Phase) {
		timer1Cnt = 0;
	}
}
*/