#include "dht11.h"
#include "time.h"

#define DHT_W_1()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)
#define DHT_W_0()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)
#define DHT_R() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)

char datas[5];

void dht_mode(uint32_t mode)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = mode;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

 
void check_dht() {
	dht_mode(GPIO_MODE_OUTPUT_PP);
	DHT_W_1();
	DHT_W_0();
	delay_us(30000);
	DHT_W_1();
	delay_us(60);
	dht_mode(GPIO_MODE_INPUT);
	while(!DHT_R());
}

void trig_dht() {
	dht_mode(GPIO_MODE_OUTPUT_PP);
	DHT_W_1();
	DHT_W_0();
	delay_us(30000);
	DHT_W_1();
	delay_us(60);
	dht_mode(GPIO_MODE_INPUT);
	while(DHT_R());
	while(!DHT_R());
	while(DHT_R());
}

void receive_data() {
	char value;
	char tmp;
	int i, j;
	dht_mode(GPIO_MODE_INPUT);
	for(i = 0; i < 5;i ++) {
		for(j = 0; j < 8; j ++) {
			while(!DHT_R()); // ����Ƿ��50us�ĵ͵�ƽ����
			delay_us(40); // 0 ��26-28us�� 1 ��70us��ѡ���м�ֵ������40-26 < 50us,δԽ�����ݿ�ʼ�ĵ͵�ƽ��Χ
			if(DHT_R() == 1) {
				value = 1;
				while(DHT_R()); // ��⵽1 �����һ������
			} else {
				value = 0;
			} 
			tmp <<= 1;
			tmp += value;
		}
		datas[i] = tmp;
	}
}
