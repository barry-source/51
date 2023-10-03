/**
  ******************************************************************************
  * @file    User/i2c1_bus.h
  * @date    18-Mar-2018
  * @brief   all the functions prototypes for simulation i2c1
  ******************************************************************************
  */
#include "stdint.h"

#ifndef __I2C1_BUS_H
#define __I2C1_BUS_H


/*
#define IIC_GPIO_PORT	GPIOB			    	 // GPIO端口 
#define IIC_SCL_PIN		GPIO_PIN_6			 // 连接到SCL时钟线的GPIO引脚
#define IIC_SDA_PIN		GPIO_PIN_7			 // 连接到SDA数据线的GPIO引脚

#define IIC_SCL_1()  IIC_GPIO_PORT->BSRR = IIC_SCL_PIN											// SCL = 1 
#define IIC_SCL_0()  IIC_GPIO_PORT->BSRR = (uint32_t)IIC_SCL_PIN << 16U  		// SCL = 0 

#define IIC_SDA_1()  IIC_GPIO_PORT->BSRR = IIC_SDA_PIN   										// SDA = 1 
#define IIC_SDA_0()  (IIC_GPIO_PORT->BSRR = (uint32_t)IIC_SDA_PIN << 16U)  		// SDA = 0 


#define IIC_SDA_READ()  (IIC_GPIO_PORT->IDR & IIC_SDA_PIN)									// 读SDA引脚 
#define IIC_SCL_READ()  (IIC_GPIO_PORT->IDR & IIC_SCL_PIN)									// 读SCL引脚
*/


/*
#define I2C1_SCL_PORT				GPIOB
#define I2C1_SCL_PIN				GPIO_PIN_6
#define I2C1_SDA_PORT				GPIOB
#define I2C1_SDA_PIN				GPIO_PIN_7
#define I2C1_GPIO_CLK				RCC_APB2Periph_GPIOB
#define I2C1_GPIO_CLK_CMD		RCC_APB2PeriphClockCmd
*/

//#define I2C1_SCL(x)		GPIO_WriteBit(I2C1_SCL_PORT, I2C1_SCL_PIN, (BitAction)(x))
//#define I2C1_SCL(x)		HAL_GPIO_WritePin(I2C1_SCL_PORT, I2C1_SCL_PIN, (x))
//#define I2C1_SDA(x)		HAL_GPIO_WritePin(I2C1_SDA_PORT, I2C1_SDA_PIN, (x))
//#define I2C1_SDA(x)		GPIO_WriteBit(I2C1_SDA_PORT, I2C1_SDA_PIN, (BitAction)(x))

#define I2C1_SCL_LOW	HAL_GPIO_WritePin(I2C1_SCL_PORT, I2C1_SCL_PIN, GPIO_PIN_RESET)
#define I2C1_SCL_HIGH	HAL_GPIO_WritePin(I2C1_SCL_PORT, I2C1_SCL_PIN, GPIO_PIN_SET)
#define I2C1_SDA_LOW	HAL_GPIO_WritePin(I2C1_SDA_PORT, I2C1_SDA_PIN, GPIO_PIN_RESET)
#define I2C1_SDA_HIGH	HAL_GPIO_WritePin(I2C1_SDA_PORT, I2C1_SDA_PIN, GPIO_PIN_SET)

// ------
#define I2C1_SDA_READ	(HAL_GPIO_ReadPin(I2C1_SDA_PORT, I2C1_SDA_PIN) & 0x01)
#define I2C1_SDAin																			\
{																												\
	i2c1GPIOInitStruct.Pin = I2C1_SDA_PIN;						\
	i2c1GPIOInitStruct.Mode = GPIO_MODE_INPUT;	\
	HAL_GPIO_Init(I2C1_SDA_PORT, &i2c1GPIOInitStruct);				\
}
#define I2C1_SDAout																	\
{																										\
	i2c1GPIOInitStruct.Pin = I2C1_SDA_PIN;				\
	i2c1GPIOInitStruct.Mode = GPIO_MODE_OUTPUT_OD;	\
	HAL_GPIO_Init(I2C1_SDA_PORT, &i2c1GPIOInitStruct);		\
}

#define I2C1_DELAY			3
#define ACK_SIGNAL			0
#define NACK_SIGNAL			1

//void I2c1_Bus_Init(void);
//static void I2C1_Init(uint32_t clkSpeed);
//static void I2C1_Start(void);
//static void I2C1_Stop(void);
//static void I2C1_SendACK(uint8_t ack);
//static uint8_t I2C1_WaitACK(void);
//static void I2C1_SendByte(uint8_t data);
//static uint8_t I2C1_RecvByte(void);
//uint8_t I2C1_WriteData(uint8_t devAddress, uint8_t regAddress, uint8_t *data, uint16_t length);
//uint8_t I2C1_ReadData_8B_Addr(uint8_t devAddress, uint8_t regAddress, uint8_t *data, uint16_t length);
uint8_t I2C1_ReadData_16B_Addr(uint8_t devAddress, uint16_t command, uint8_t *data, uint16_t length);
uint8_t I2C1_ReadData_8B_Addr_NHMM(uint8_t devAddress, uint8_t regAddress, uint8_t *data, uint16_t length);
//uint8_t I2C1_CheckDev(uint8_t devAddress);

//void delay_us(uint32_t delay);

#endif
