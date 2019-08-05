#include <util/delay.h>
#include "delay.h"

void delay_us(uint16_t var_count_us)
{
	while(var_count_us != 0)
	{
		_delay_us(1);
		var_count_us--;
	}
}

void delay_ms(uint16_t var_count_ms)
{
	while(var_count_ms != 0)
	{
		_delay_us(1000);
		var_count_ms--;
	}
}


#if (enable_Delay_Sec == 1)

void delay_sec(uint16_t var_count_sec)
{
	while(var_count_sec != 0)
	{
		delay_ms(1000);
		var_count_sec--;
	}
}
#endif
