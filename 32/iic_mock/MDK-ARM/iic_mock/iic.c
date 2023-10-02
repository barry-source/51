#include "iic.h"
 
 void delay_us(__IO uint32_t delay) {
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
	delay_us(1);
}

// SCL���ָߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��ɵ͵�ƽ������һ���½��ء�
void iic_start(void) {
	IIC_SDA_1();
	IIC_SCL_1();
	iic_delay_1us();
	IIC_SDA_0();
	iic_delay_1us();
}
  
// SCL���ָߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ɸߵ�ƽ������һ�������ء�
void iic_stop(void){
	IIC_SDA_0();
	IIC_SCL_1();
	iic_delay_1us();
	IIC_SDA_1();
	iic_delay_1us();
}

void iic_send_byte(uint8_t byte){
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

void iic_ack(void){
	IIC_SDA_0();	
	iic_delay_1us();
	IIC_SCL_1();	
	iic_delay_1us();
	IIC_SCL_0();
	iic_delay_1us();
	IIC_SDA_1();	
}
 
 
uint8_t iic_CheckDevice(uint8_t _Address){
	uint8_t ucAck;
 
	if (IIC_SDA_READ() && IIC_SCL_READ()){
		iic_start();		/* ���������ź� */
 
		/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
		iic_send_byte(_Address | 0);
		ucAck = iic_wait_ack();	
 
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




