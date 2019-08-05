/*
 * pwm.c
 *
 * Created: 20-02-2019 03:37:15 PM
 *  Author: TrailBlazer
 */ 
#include <avr/io.h>
#include "pwm.h"
#include "stdutils.h"

void PWM_Init(uint8_t pwmChannel)
{
	switch(pwmChannel)
	{
		case 0:
			TCNT0 = 0x00;
			BitSet(DDRB,3);
			break;
			
		case 1:
			TCNT1 = 0x00;
			BitSet(DDRD,5);
			break;
			
		case 2:
			TCNT1 = 0x00;
			BitSet(DDRD,4);
			break;
			
		case 3:
			TCNT2 = 0x00;
			BitSet(DDRD,7);
			break;
	}
	
}

/***************************************************/

void PWM_SetDutyCycle(uint8_t pwmChannel, uint8_t dutyCycle)
{
	dutyCycle *= 2.55;
	switch(pwmChannel)
	{
		case 0:
			OCR0 = dutyCycle;
			break;
			
		case 1:
			OCR1A = dutyCycle;
			break;
			
		case 2:
			OCR1B = dutyCycle;
			break;
		
		case 3:
			OCR2 = dutyCycle;
			break;
	}
}

/**********************************************/

void PWM_Start(uint8_t pwmChannel)
{
	switch(pwmChannel)
	{
		case 0:
			TCCR0 = ((1<<WGM00)|(1<<COM01)|(CS00));
			break;
		
		case 1:
			BitSet(TCCR1A,COM1A1);
			BitSet(TCCR1A,WGM10);
			BitSet(TCCR1A,CS10);
			break;
		
		case 2:
			BitSet(TCCR1A,COM1B1);
			BitSet(TCCR1B,CS10);
			break;
		
		case 3:
			TCCR2 = ((1<<WGM20)|(1<<COM21)|(CS20));
			break;
	}
}

/****************************************************/

void PWM_Stop(uint8_t pwmChannel)
{
	switch(pwmChannel)
	{
		case 0:
			BitClear(TCCR0,COM00);
			break;
		
		case 1:
			BitClear(TCCR1A,COM1A1);
			break;
		
		case 2:
			BitClear(TCCR1A,COM1B1);
			break;
		
		case 3:
			BitClear(TCCR2,COM21);
			break;
	}
	
}
