#include "time.h"
#include <intrins.h>

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


void delay_ms(int n) {
	int i, j;
	for(i = n; i > 0; i --) 
		for(j = 110; j > 0; j --);
}

void Delay60us()		//@11.0592MHz
{
	unsigned char i;

	i = 25;
	while (--i);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 20;
	while (--i);
}


void Delay40us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 15;
	while (--i);
}


void Delay30ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}
