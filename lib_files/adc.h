
#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include "stdutils.h"


/************************
 ADC Function Prototypes
 ************************/

void ADC_Init();
uint16_t ADC_GetADCValue(uint8_t var_adcChann);



#endif
