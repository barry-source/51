#include "reg52.h"
#include <intrins.h>


sbit pulse = P1^1; // sg90 signal
sbit trig = P1^5; // 超声波触发引脚
sbit echo = P1^6; // 超声波回应引脚

sbit beep = P2^0; // 蜂鸣器
sbit key = P2^1;  // 按键
sbit vibrateData = P3^2; // 振动DO口（hm-sensor）
sbit led2 = P3^6; // 蓝灯
sbit led1 = P3^7; // 黄灯

int cnt = 0;
int phase = 1;
int vibrate;

void Delay2000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

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

void Delay200ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 2;
	j = 103;
	k = 147;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay150ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 2;
	j = 13;
	k = 237;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay300ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 3;
	j = 26;
	k = 223;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}


////////////////舵机/////////////////////////
void sg90Init() {
	Delay300ms();
	TMOD &= 0XF0;
	TMOD |= 0X01;
	TL0 = 0X33;
	TH0 = 0XFE;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

/////////////////振动/////////////////////////
void initExInt0() {
	IT0 = 0; // 低电平触发
	EX0 = 1; // 开启外部中断0
}

/////////////////蜂鸣器/////////////////////////
void beep300ms() {
	int n;
	beep = 0;
	for(n=0;n<2;n++)
		Delay150ms();
	beep = 1;
}

/////////////////led/////////////////////////
void ledStatusWhenOpend() {
	led1 = 1;
	led2 = 0;
}

void ledStatusWhenClosed() {
	led1 = 0;
	led2 = 1;
}

/////////////////超声波/////////////////////////

// 声波使用timer 1
void initTimer1() {
	TMOD &= 0X0F;
	TMOD |= 0X10;
	TL1 = 0;
	TH1 = 0;
}

void uart_init() {
	TMOD &= 0X0F;
	TMOD |= 0X20;
	SCON = 0X40;
	TH1 = 0XFD;
	TL1 = 0XFD;
	TR1 = 1;
}

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

void main() {
	double distance;
	double lastPhase;
	initExInt0();
	sg90Init();
	initTimer1();
	while(1) {
		Delay200ms();
		startUltrasonicWave();
		distance = getDistance();
		if (distance < 10 || !key || vibrate) {
			ledStatusWhenOpend();
			
			phase = 3;
			if(lastPhase != phase) {
				cnt = 0;
				beep300ms();
				Delay2000ms();
			}  
			
			vibrate  = 0;
		} else {
			ledStatusWhenClosed();
			phase = 1;
			cnt = 0;
			Delay150ms();
		}
		lastPhase = phase;
		TL1 = 0;
		TH1 = 0;
	}
}

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

void exteral0() interrupt 0 {
	vibrate = vibrateData;
}