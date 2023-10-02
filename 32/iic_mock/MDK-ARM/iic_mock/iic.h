
#include "stdint.h"
#include "gpio.h"

#ifndef __IIC_H__
#define	__IIC_H__


/*********************引脚和主频根据情况更换*****************************/
#define CPU_FREQUENCY_MHZ  72		 			 // STM32时钟主频

#define IIC_GPIO_PORT	GPIOB			    	 // GPIO端口 
#define IIC_SCL_PIN		GPIO_PIN_6			 // 连接到SCL时钟线的GPIO引脚
#define IIC_SDA_PIN		GPIO_PIN_7			 // 连接到SDA数据线的GPIO引脚
 
#define IIC_SCL_1()  IIC_GPIO_PORT->BSRR = IIC_SCL_PIN											// SCL = 1 
#define IIC_SCL_0()  IIC_GPIO_PORT->BSRR = (uint32_t)IIC_SCL_PIN << 16U  		// SCL = 0 
 
#define IIC_SDA_1()  IIC_GPIO_PORT->BSRR = IIC_SDA_PIN   										// SDA = 1 
#define IIC_SDA_0()  IIC_GPIO_PORT->BSRR = (uint32_t)IIC_SDA_PIN << 16U  		// SDA = 0 
 
#define IIC_SDA_READ()  (IIC_GPIO_PORT->IDR & IIC_SDA_PIN)									// 读SDA引脚 
#define IIC_SCL_READ()  (IIC_GPIO_PORT->IDR & IIC_SCL_PIN)									// 读SCL引脚
 
 
void iic_start(void); //开始信号

void iic_stop(void); //停止信号

void iic_send_byte(uint8_t _ucByte); //发送一个字节

void iic_ack(void); //应答信号

uint8_t iic_read_byte(void); //读取一个字节

uint8_t iic_wait_ack(void); //等待应答信号

#endif
