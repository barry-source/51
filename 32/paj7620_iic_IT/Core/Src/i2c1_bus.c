/**
  ******************************************************************************
  * @file    User/i2c1_bus.c
  * @date    18-Mar-2018
  * @brief   gpio config and simulation i2c1 operating functions
  ******************************************************************************
  */
  
#include "i2c1_bus.h"
#include "gpio.h"
#include "iic.h"


uint8_t I2C1_ReadData_16B_Addr(uint8_t devAddress, uint16_t command, uint8_t *data, uint16_t length)
{
	uint16_t cnt;
	iic_start();
	iic_send_byte(devAddress << 1 | 0);
	if(iic_wait_ack() == NACK_SIGNAL)
	{
		iic_stop();
		return 1;
	}
	iic_send_byte((command >> 8) & 0xff);
	if(iic_wait_ack() == NACK_SIGNAL)
	{
		iic_stop();
		return 2;
	}
	iic_send_byte(command & 0xff);
	if(iic_wait_ack() == NACK_SIGNAL)
	{
		iic_stop();
		return 2;
	}
	iic_start();
	iic_send_byte(devAddress << 1 | 1);
	if(iic_wait_ack() == NACK_SIGNAL)
	{
		iic_stop();
		return 3;
	}
	for(cnt = 0; cnt < length; cnt++)
	{
		data[cnt] = iic_read_byte();
		if(cnt == length-1)
		{

			iic_send_ack(NACK_SIGNAL);
		}
		else
		{
			iic_send_ack(ACK_SIGNAL);
		}
	}
	iic_stop();
	return 0;
}

uint8_t I2C1_ReadData_8B_Addr_NHMM(uint8_t devAddress, uint8_t regAddress, uint8_t *data, uint16_t length)
{
	uint16_t cnt;
	iic_start();
	iic_send_byte(devAddress << 1 | 0);
	if(iic_wait_ack() == NACK_SIGNAL)
	{
		iic_stop();
		return 1;
	}
	iic_send_byte(regAddress);
	if(iic_wait_ack() == NACK_SIGNAL)
	{
		iic_stop();
		return 2;
	}
	iic_start();
	iic_send_byte(devAddress << 1 | 1);
	// TODO:待优化，去除循环等待
	while(iic_wait_ack() == NACK_SIGNAL)
	{
		iic_start();
		iic_send_byte(devAddress << 1 | 1);
		//iic_stop();
		//return 3;
	}
	for(cnt = 0; cnt < length; cnt++)
	{
		data[cnt] = iic_read_byte();
		if(cnt == length-1)
		{

			iic_send_ack(NACK_SIGNAL);
		}
		else
		{
			iic_send_ack(ACK_SIGNAL);
		}
	}
	iic_stop();
	return 0;
}
