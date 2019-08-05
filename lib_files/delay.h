#ifndef DELAY_H_
#define DELAY_H_

#include "stdutils.h"

#define C_OneMSDelayCount 300u

#define Enable_Delay_Sec 1


void delay_us(uint16_t var_count_us);
void delay_ms(uint16_t var_count_ms);
void delay_sec(uint16_t var_count_sec);



#endif
