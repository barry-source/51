#include "hc04.h"
#include "reg52.h"
#include "time.h"

sbit trig = P2^3; // 超声波触发引脚
sbit echo = P2^2; // 超声波回应引脚


/*
void uart_init() {
	TMOD &= 0X0F;
	TMOD |= 0X20;
	SCON = 0X40;
	TH1 = 0XFD;
	TL1 = 0XFD;
	TR1 = 1;
}

*/

// 保持10us高电平
void trigWave() {
	trig = 0;
	trig = 1;
	Delay10us();
	trig = 0;
}

void startUltrasonicWave() {
	trigWave();
	while(echo == 0);
	TR1 = 1;
	while(echo == 1);
	TR1= 0;
}

double getDistance() {
	return (TH1 * 256 + TL1) * 1.085 * 0.017;
}

double getDistanceByUltrasonicWave() {
	TH1 = 0;
	TL1 = 0;
	startUltrasonicWave();
	return getDistance();
}





