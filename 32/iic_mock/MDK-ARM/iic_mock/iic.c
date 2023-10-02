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
 
// IIC 至少0.6us，1us即可
void iic_delay_1us(void) {
	delay_us(1);
}

// SCL保持高电平期间，SDA由高电平变成低电平，产生一个下降沿。
void iic_start(void) {
	IIC_SDA_1();
	IIC_SCL_1();
	iic_delay_1us();
	IIC_SDA_0();
	iic_delay_1us();
}
  
// SCL保持高电平期间，SDA由低电平变成高电平，产生一个上升沿。
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
		iic_start();		/* 发送启动信号 */
 
		/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
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




