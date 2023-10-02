
#include "stdint.h"
#include "gpio.h"

#ifndef __IIC_H__
#define	__IIC_H__


/*********************���ź���Ƶ�����������*****************************/
#define CPU_FREQUENCY_MHZ  72		 			 // STM32ʱ����Ƶ

#define IIC_GPIO_PORT	GPIOB			    	 // GPIO�˿� 
#define IIC_SCL_PIN		GPIO_PIN_6			 // ���ӵ�SCLʱ���ߵ�GPIO����
#define IIC_SDA_PIN		GPIO_PIN_7			 // ���ӵ�SDA�����ߵ�GPIO����
 
#define IIC_SCL_1()  IIC_GPIO_PORT->BSRR = IIC_SCL_PIN											// SCL = 1 
#define IIC_SCL_0()  IIC_GPIO_PORT->BSRR = (uint32_t)IIC_SCL_PIN << 16U  		// SCL = 0 
 
#define IIC_SDA_1()  IIC_GPIO_PORT->BSRR = IIC_SDA_PIN   										// SDA = 1 
#define IIC_SDA_0()  IIC_GPIO_PORT->BSRR = (uint32_t)IIC_SDA_PIN << 16U  		// SDA = 0 
 
#define IIC_SDA_READ()  (IIC_GPIO_PORT->IDR & IIC_SDA_PIN)									// ��SDA���� 
#define IIC_SCL_READ()  (IIC_GPIO_PORT->IDR & IIC_SCL_PIN)									// ��SCL����
 
 
void iic_start(void); //��ʼ�ź�

void iic_stop(void); //ֹͣ�ź�

void iic_send_byte(uint8_t _ucByte); //����һ���ֽ�

void iic_ack(void); //Ӧ���ź�

uint8_t iic_read_byte(void); //��ȡһ���ֽ�

uint8_t iic_wait_ack(void); //�ȴ�Ӧ���ź�

#endif
