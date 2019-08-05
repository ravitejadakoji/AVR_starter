/*
 * i2c.h
 *
 * Created: 20-02-2019 02:11:50 PM
 *  Author: TrailBlazer
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "stdutils.h"


/***********************
 I2C Function Prototypes
 **********************/

void I2C_Init(void);
void I2C_Start(void);
//void I2C_Restart(void);
void I2C_Stop(void);
void I2C_Write(uint8_t var_i2cData);
uint8_t I2C_Read(uint8_t var_i2cAck);



#endif /* I2C_H_ */