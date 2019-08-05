#include <avr/io.h>
#include "i2c.h"
#include "delay.h"

/************************************/

void I2C_Init()
{
	TWSR = 0x00;
	TWBR = 0x46;
	TWCR = 0x04;
}

/***********************************/

void I2C_Start()
{
	TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));
	while(!(TWCR & (1<<TWINT)));
}

/**********************************/

void I2C_Stop()
{
	TWCR = ((1<<TWINT) | (1<<TWEN) | (1<<TWSTO));
	delay_us(100);
}

/*********************************/

void I2C_Write(uint8_t var_i2cData)
{
	TWDR = var_i2cData;
	TWCR = ((1<<TWINT) | (1<<TWEN));
	while(!(TWCR & (1<<TWINT)));
}

/*******************************/

uint8_t I2C_Read(uint8_t var_i2cAck)
{
		TWCR = ((1<<TWINT) | (1<<TWEN) | (var_i2cAck<<TWEA));
		while(!(TWCR & (1<<TWINT)));
		return TWDR;
}

