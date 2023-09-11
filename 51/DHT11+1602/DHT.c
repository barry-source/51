#include "DHT.h"
#include "time.h"
#include "reg52.h"

sbit DHT = P3^3;

char datas[5];

void check_DHT() {
	DHT = 1;
	DHT = 0;
	Delay30ms();
	DHT = 1;
	Delay60us();
	while(DHT);
}

void trigDHT() {
	DHT = 1;
	DHT = 0;
	Delay30ms();
	DHT = 1;
	Delay60us();
	while(DHT); // 80us拉低电平（DHT响应信息）
	while(!DHT); //80us拉高电平（DHT拉高）
	while(DHT); // 等待开始传输数据
}

void receiveData() {
	
	char value;
	char tmp;
	int i, j;
	for(i = 0; i < 5;i ++) {
		for(j = 0; j < 8; j ++) {
			while(!DHT); // 检测是否从50us的低电平拉高
			Delay40us(); // 0 是26-28us， 1 是70us，选择中间值，另外40-26 < 50us,未越过数据开始的低电平范围
			if(DHT == 1) {
				value = 1;
				while(DHT); // 检测到1 检测下一次数据
			} else {
				value = 0;
			}
			tmp <<= 1;
			tmp += value;
		}
		datas[i] = tmp;
	}
}