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
 
// IIC ����0.6us��1us����
void iic_delay_1us(void) {
	iic_delay_us(1);
}

// SCL���ָߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��ɵ͵�ƽ������һ���½���
void iic_start(void) {
	IIC_SDA_1();
	IIC_SCL_1();
	iic_delay_1us();
	IIC_SDA_0();
	iic_delay_1us();
}
  
// SCL���ָߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ɸߵ�ƽ������һ��������
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
		byte <<= 1;		// ����һ��bit 
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

// I2C�������ߵ�SDA��SCL�����ź���ͬʱ���ڸߵ�ƽʱ���涨Ϊ���ߵĿ���״̬��
// ��ʱ�����������������ЧӦ�ܾ����ڽ�ֹ״̬�����ͷ����ߣ��������ź��߸��Ե���������ѵ�ƽ����
uint8_t iic_check_device(uint8_t address){
	uint8_t ucAck;
	if (IIC_SDA_READ() && IIC_SCL_READ()){
		iic_start();		// ���������ź� 
		iic_send_byte(address | 0);
		ucAck = iic_wait_ack();	// �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ�
		iic_stop();			
		return ucAck;
	}
	return 1;	
}
 
void Device_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size){
    int count=size;
		uint8_t *pData=Data;
		//��ʼ�ź�
    iic_start();    
    //����������ַ                         
    iic_send_byte(DeciveAddr);       
    //�ȴ�Ӧ��
    iic_wait_ack();                          
    while(count--)
		{
			//��������
			iic_send_byte(*pData++);                     
			//�ȴ�Ӧ��
			iic_wait_ack();   
		}			 
                       
    //�����ź�
    iic_stop();     
}


/************************************Oled*****************************************/
/*
void iic_write_cmd(char cmd) {
	iic_start();
	// 01111100 + R/W(0��д����)
	iic_send_byte(0x78);
	iic_wait_ack();
	// C0 + D/C + XXXXXX  ==> D/C = 1 ��ʾ����  = 0 ��ʾ����  
	iic_send_byte(0x00);
	iic_wait_ack();
	iic_send_byte(cmd);
	iic_wait_ack();
	iic_stop();
}

void iic_write_data(char d) {
	iic_start();
	// 01111100 + R/W(0��д����)
	iic_send_byte(0x78);
	iic_wait_ack();
	// C0 + D/C + XXXXXX  ==> D/C = 1 ��ʾ����  = 0 ��ʾ����  
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
