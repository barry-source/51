#include "dht11.h"
#include "time.h"

#define DHT_W_1()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)
#define DHT_W_0()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)
#define DHT_R() HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)

char datas[5];

 void delay_us(__IO uint32_t delay) {
    int last, curr, val;
    int temp;

    while (delay != 0) { 
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - 72 * temp;
        if (curr >= 0){
            do{
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        } else{
            curr += 72 * 1000;
            do{
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}
 
void dht_mode(uint32_t mode)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = mode;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

int8_t trig_dht() {
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
	return 0;
}

void receive_data() {
	char value;
	char tmp;
	int i, j;
	dht_mode(GPIO_MODE_INPUT);
	for(i = 0; i < 5;i ++) {
		for(j = 0; j < 8; j ++) {
			// 检测是否从50us的低电平拉高
			while(!DHT_R());
			delay_us(40); // 0 是26-28us， 1 是70us，选择中间值，另外40-26 < 50us,未越过数据开始的低电平范围
			if(DHT_R() == 1) {
				value = 1;
				// 检测到1 检测下一次数据
				while(DHT_R());
			} else {
				value = 0;
			} 
			tmp <<= 1;
			tmp += value;
		}
		datas[i] = tmp;
	}
}
