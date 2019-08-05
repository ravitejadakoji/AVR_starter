#include "adc.h"
#include "delay.h"

/***************************************/

void ADC_Init()
{
	ADCSRA = ((1<<ADEN) | (1<<ADPS2) | (1<<ADPS1));
	ADMUX = 0x00;
}

/*****************************************/
uint16_t ADC_GetADCValue(uint8_t var_adcChann)
{
	ADMUX = var_adcChann;
	delay_us(10);
	BitSet(ADCSRA,ADSC);
	
	while(IsBitCleared(ADCSRA,ADIF));
	return (ADCW);
}

/********************************************/
