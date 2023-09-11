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
	while(DHT); // 80us���͵�ƽ��DHT��Ӧ��Ϣ��
	while(!DHT); //80us���ߵ�ƽ��DHT���ߣ�
	while(DHT); // �ȴ���ʼ��������
}

void receiveData() {
	
	char value;
	char tmp;
	int i, j;
	for(i = 0; i < 5;i ++) {
		for(j = 0; j < 8; j ++) {
			while(!DHT); // ����Ƿ��50us�ĵ͵�ƽ����
			Delay40us(); // 0 ��26-28us�� 1 ��70us��ѡ���м�ֵ������40-26 < 50us,δԽ�����ݿ�ʼ�ĵ͵�ƽ��Χ
			if(DHT == 1) {
				value = 1;
				while(DHT); // ��⵽1 �����һ������
			} else {
				value = 0;
			}
			tmp <<= 1;
			tmp += value;
		}
		datas[i] = tmp;
	}
}