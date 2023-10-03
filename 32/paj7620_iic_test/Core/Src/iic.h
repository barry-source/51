// Ŀǰֻ��8λ��ַ����16��ַ����


#include "stdint.h"
#include "gpio.h"

#ifndef __IIC_H__
#define	__IIC_H__

#define ACK			  0
#define NACK			1

/*********************���ź���Ƶ�����������*****************************/
#define CPU_FREQUENCY_MHZ  72		 			 // STM32ʱ����Ƶ

#define IIC_GPIO_PORT	GPIOB			    	 // GPIO�˿� 
#define IIC_SCL_PIN		GPIO_PIN_6			 // ���ӵ�SCLʱ���ߵ�GPIO����
#define IIC_SDA_PIN		GPIO_PIN_7			 // ���ӵ�SDA�����ߵ�GPIO����
 
#define IIC_SCL_1()  IIC_GPIO_PORT->BSRR = IIC_SCL_PIN											// SCL = 1 
#define IIC_SCL_0()  IIC_GPIO_PORT->BSRR = (uint32_t)IIC_SCL_PIN << 16U  		// SCL = 0 
 
#define IIC_SDA_1()  IIC_GPIO_PORT->BSRR = IIC_SDA_PIN   										// SDA = 1 
#define IIC_SDA_0()  (IIC_GPIO_PORT->BSRR = (uint32_t)IIC_SDA_PIN << 16U)   // SDA = 0 
 
#define IIC_SDA_READ()  (IIC_GPIO_PORT->IDR & IIC_SDA_PIN)									// ��SDA���� 
#define IIC_SCL_READ()  (IIC_GPIO_PORT->IDR & IIC_SCL_PIN)									// ��SCL����
 
/************************************IIC*****************************************/
void iic_start(void); //��ʼ�ź�

void iic_stop(void); //ֹͣ�ź�

void iic_send_byte(uint8_t byte); //����һ���ֽ�

void iic_send_ack(uint8_t ack); //����Ӧ���ź�

uint8_t iic_read_byte(void); //��ȡһ���ֽ�

uint8_t iic_wait_ack(void); //�ȴ�Ӧ���ź�

uint8_t iic_check_device(uint8_t address);

void delay_us(__IO uint32_t delay);

void iic_delay_1us(void);

/************************************Oled*****************************************/
void iic_write_cmd(char cmd);

void iic_write_data(char d);

/************************************PAJ7620*****************************************/
uint8_t iic_write_7620(uint8_t devAddress, uint8_t regAddress, uint8_t *data, uint16_t length);

uint8_t iic_read_7620(uint8_t devAddress, uint8_t regAddress, uint8_t *data, uint16_t length);

#endif
