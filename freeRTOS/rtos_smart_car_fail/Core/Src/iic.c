#include "iic.h"
 
void iic_delay_us(__IO uint32_t delay) {
	int last, curr, val;
	int temp;

	while (delay != 0) { 
		temp = delay > 900 ? 900 : delay;
		last = SysTick->VAL;
		curr = last - CPU_FREQUENCY_MHZ * temp;
		if (curr >= 0){
				do{
						val = SysTick->VAL;
				}
				while ((val < last) && (val >= curr));
		} else{
				curr += CPU_FREQUENCY_MHZ * 1000;
				do{
						val = SysTick->VAL;
				}
				while ((val <= last) || (val > curr));
		}
		delay -= temp;
	}
}
 
// IIC 至少0.6us，1us即可
void iic_delay_1us(void) {
	iic_delay_us(1);
}

// SCL保持高电平期间，SDA由高电平变成低电平，产生一个下降沿
void iic_start(void) {
	IIC_SDA_1();
	IIC_SCL_1();
	iic_delay_1us();
	IIC_SDA_0();
	iic_delay_1us();
}
  
// SCL保持高电平期间，SDA由低电平变成高电平，产生一个上升沿
void iic_stop(void){
	IIC_SDA_0();
	IIC_SCL_1();
	iic_delay_1us();
	IIC_SDA_1();
	iic_delay_1us();
}

void iic_send_byte(uint8_t byte) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		IIC_SCL_0();
		(byte & 0x80) ? (IIC_SDA_1()) : (IIC_SDA_0());
		iic_delay_1us();
		IIC_SCL_1();
		iic_delay_1us();
		IIC_SCL_0();
		iic_delay_1us();
		byte <<= 1;		// 左移一个bit 
	}
}

uint8_t iic_read_byte(void){
	uint8_t i;
	uint8_t value = 0;
	for (i = 0; i < 8; i++) {
		value <<= 1;
		IIC_SCL_1();
		iic_delay_1us();
		if (IIC_SDA_READ()) {
			value++;
		}
		IIC_SCL_0();
		iic_delay_1us();
	}
	return value;
}

uint8_t iic_wait_ack(void){
	uint8_t result;

	IIC_SCL_1();	
	iic_delay_1us();
	result = IIC_SDA_READ() ? 1 :0;
	IIC_SCL_0();
	iic_delay_1us();
	return result;
}

void iic_send_ack(uint8_t ack){
	IIC_SCL_0();
	iic_delay_1us();
	ack ? IIC_SDA_1():IIC_SDA_0();
	iic_delay_1us();
	IIC_SCL_1();
	iic_delay_1us();
	IIC_SCL_0();
	iic_delay_1us();
}

// I2C总线总线的SDA和SCL两条信号线同时处于高电平时，规定为总线的空闲状态。
// 此时各个器件的输出级场效应管均处在截止状态，即释放总线，由两条信号线各自的上拉电阻把电平拉高
uint8_t iic_check_device(uint8_t address){
	uint8_t ucAck;
	if (IIC_SDA_READ() && IIC_SCL_READ()){
		iic_start();		// 发送启动信号 
		iic_send_byte(address | 0);
		ucAck = iic_wait_ack();	// 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传
		iic_stop();			
		return ucAck;
	}
	return 1;	
}
 
void Device_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size){
    int count=size;
		uint8_t *pData=Data;
		//起始信号
    iic_start();    
    //发送器件地址                         
    iic_send_byte(DeciveAddr);       
    //等待应答
    iic_wait_ack();                          
    while(count--)
		{
			//发送数据
			iic_send_byte(*pData++);                     
			//等待应答
			iic_wait_ack();   
		}			 
                       
    //结束信号
    iic_stop();     
}


/************************************Oled*****************************************/
/*
void iic_write_cmd(char cmd) {
	iic_start();
	// 01111100 + R/W(0是写操作)
	iic_send_byte(0x78);
	iic_wait_ack();
	// C0 + D/C + XXXXXX  ==> D/C = 1 表示数据  = 0 表示命令  
	iic_send_byte(0x00);
	iic_wait_ack();
	iic_send_byte(cmd);
	iic_wait_ack();
	iic_stop();
}

void iic_write_data(char d) {
	iic_start();
	// 01111100 + R/W(0是写操作)
	iic_send_byte(0x78);
	iic_wait_ack();
	// C0 + D/C + XXXXXX  ==> D/C = 1 表示数据  = 0 表示命令  
	iic_send_byte(0x40);
	iic_wait_ack();
	iic_send_byte(d);
	iic_wait_ack();
	iic_stop();
}
*/
/************************************PAJ7620*****************************************/

uint8_t iic_write_7620(uint8_t devAddress, uint8_t regAddress, uint8_t *data, uint16_t length) {
	uint16_t cnt;
	iic_start();
	iic_send_byte(devAddress << 1 | 0);
	if(iic_wait_ack() == NACK){
		iic_stop();
		return 1;
	}
	iic_send_byte(regAddress);
	if(iic_wait_ack() == NACK) {
		iic_stop();
		return 2;
	}
	for(cnt = 0; cnt < length; cnt++){
		iic_send_byte(data[cnt]);
		if(iic_wait_ack() == NACK) {
			iic_stop();
			return 3;
		}
	}
	iic_stop();
	return ACK;
}


uint8_t iic_read_7620(uint8_t devAddress, uint8_t regAddress, uint8_t *data, uint16_t length) {
	uint16_t cnt;
	iic_start();
	iic_send_byte(devAddress << 1 | 0);
	if(iic_wait_ack() == NACK) {
		iic_stop();
		return 1;
	}
	iic_send_byte(regAddress);
	if(iic_wait_ack() == NACK) {
		iic_stop();
		return 2;
	}
	iic_start();
	iic_send_byte(devAddress << 1 | 1);
	if(iic_wait_ack() == NACK) {
		iic_stop();
		return 3;
	}
	for(cnt = 0; cnt < length; cnt++){
		data[cnt] = iic_read_byte();
		if(cnt == length - 1) {
			iic_send_ack(NACK);
		} else {
			iic_send_ack(ACK);
		}
	}
	iic_stop();
	return 0;
}
