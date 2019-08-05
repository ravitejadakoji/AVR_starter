#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "stdutils.h"

const uint16_t Arr_PrescalerTableZeroOne[6] = {0,1,8,64,256,1024};
const uint16_t Arr_PrescalerTableTwo[8] = {0,1,8,32,64,128,256,1024};

uint8_t v_T0Prescaler = 0;
uint8_t v_T0ReloadVal = 0;
uint16_t v_T0OVFCount = 0;
isrFunPtr_t T0_User_ISR = NULL;

uint8_t v_T1Prescaler = 0;
uint16_t v_T1ReloadVal = 0;
uint16_t v_T1OVFCount = 0;
isrFunPtr_t T1_User_ISR = NULL;

uint8_t v_T2Prescaler = 0;
uint8_t v_T2ReloadVal = 0;
uint16_t v_T2OVFCount = 0;
isrFunPtr_t T2_User_ISR = NULL;

uint8_t F_OSC = F_CPU/1000000UL;

/*******************************
Timer Local Function Prototype
*******************************/

uint8_t getPrescalarVal(uint32_t reqDel, uint32_t regVal, const uint16_t *ptrPrescalar, uint8_t maxArrEnt);

/*****************************
Timer Local Function
*****************************/	 

uint8_t getPrescalarVal(uint32_t reqDel, uint32_t regVal, const uint16_t *ptrPrescalar, uint8_t maxArrEnt)
{
	uint32_t delay = 0;
	uint8_t i;
	
	for(i=1;i<maxArrEnt;i++)
	{
		delay = ((regVal*ptrPrescalar[i])/F_OSC);
		if (delay>=reqDel)
		{
			break;
		}
	}
	return i;
}

/**********************************/

/*************************
	Timer Functions
*************************/

void TIMER_Init(uint8_t timerNum, uint32_t timerIntvl)
{
	TIMER_SetTime(timerNum, timerIntvl);
}

/**********************************************************/

void TIMER_Start(uint8_t timerNum)
{
	switch(timerNum)
	{
		case 0:
			v_T0OVFCount = 0;
			TCNT0 = v_T0ReloadVal;
			BitSet(TIMSK,TOIE0);
			TCCR0 = v_T0Prescaler;
			break;
			
		case 1:
			v_T1OVFCount = 0;
			TCNT1 = v_T0ReloadVal;
			BitSet(TIMSK,TOIE1);
			TCCR1A = 0x00;
			TCCR1B = v_T1Prescaler;
			break;
			
		case 2:
			v_T2OVFCount = 0;
			TCNT2 = v_T0ReloadVal;
			BitSet(TIMSK,TOIE2);
			TCCR2 = v_T2Prescaler;
			break;
	}
}

/**********************************************************/

void TIMER_Stop(uint8_t timerNum)
{
	switch(timerNum)
	{
		case 0:
			BitSet(TIMSK,TOIE0);
			TCCR0 = v_T0Prescaler;
			break;
		
		case 1:
			BitSet(TIMSK,TOIE1);
			TCCR1B = v_T1Prescaler;
			break;
		
		case 2:
			BitSet(TIMSK,TOIE2);
			TCCR2 = v_T2Prescaler;
		break;
	}
}

/**********************************************************/

void TIMER_AttachINT(uint8_t timerNum, isrFunPtr_t funPtr)
{
	switch(timerNum)
	{
		case 0:
			T0_User_ISR = funPtr;
			break;
		
		case 1:
			T1_User_ISR = funPtr;
			break;
		
		case 2:
			T2_User_ISR = funPtr;
			break;
	}
}


/**********************************************************/

void TIMER_SetTime(uint8_t timerNum, uint32_t timerIntvl)
{
	switch(timerNum)
	{
		case 0:
			if((timerIntvl >= TIMER0_MIN) && (timerIntvl <= TIMER0_MAX))
			{
				v_T0Prescaler = getPrescalarVal(timerIntvl,256,Arr_PrescalerTableZeroOne,6);
				v_T0ReloadVal = (uint8_t)256-(uint8_t)((timerIntvl*F_OSC)/Arr_PrescalerTableZeroOne[v_T0Prescaler]);
			}
			break;
			
		case 1:
			if((timerIntvl >= TIMER1_MIN) && (timerIntvl <= TIMER1_MAX))
			{
				v_T1Prescaler = getPrescalarVal(timerIntvl,65536,Arr_PrescalerTableTwo,8);
				v_T1ReloadVal = (uint32_t)65536-((timerIntvl*F_OSC)/Arr_PrescalerTableTwo[v_T1Prescaler]);
			}
			break;
			
		case 2:
			if((timerIntvl >= TIMER2_MIN) && (timerIntvl <= TIMER2_MAX))
			{
				v_T2Prescaler = getPrescalarVal(timerIntvl,256,Arr_PrescalerTableZeroOne,6);
				v_T2ReloadVal = 256-((timerIntvl*F_OSC)/Arr_PrescalerTableZeroOne[v_T2Prescaler]);
			}
			break;
	}
}

extern volatile uint8_t value;

/**********************************************************************/

uint32_t TIMER_GetTime(uint8_t timerNum)
{
	uint32_t timerDelay = 0;
	uint16_t prescalar;
	switch(timerNum)
	{
		case 0:
			prescalar = Arr_PrescalerTableZeroOne[v_T0Prescaler];
			timerDelay = (((uint32_t)prescalar * (uint32_t)(256-v_T0ReloadVal))/F_OSC) * v_T0OVFCount;
			if(TCNT0 > v_T0ReloadVal)
			{
				timerDelay = timerDelay + (((uint32_t)prescalar * (uint32_t)(TCNT0-v_T0ReloadVal))/F_OSC);
			}
			break;
		
		case 1:
			prescalar = Arr_PrescalerTableTwo[v_T1Prescaler];
			timerDelay = ((prescalar * (65536-v_T1ReloadVal))/F_OSC) * v_T1OVFCount;
			if(TCNT1 > v_T1ReloadVal)
			{
				timerDelay = timerDelay + ((prescalar * (TCNT1-v_T1ReloadVal))/F_OSC);
			}
			break;
			
		case 2:
			prescalar = Arr_PrescalerTableZeroOne[v_T2Prescaler];
			timerDelay = (((uint32_t)prescalar * (uint32_t)(256-v_T2ReloadVal))/F_OSC) * v_T2OVFCount;
			if(TCNT2 > v_T2ReloadVal)
			{
				timerDelay = timerDelay + (((uint32_t)prescalar * (uint32_t)(TCNT2-v_T2ReloadVal))/F_OSC);
			}
			break;
	}
	
	return timerDelay;
	
}


/*****************************************
			TIMER ISR
*****************************************/

ISR (TIMER0_OVF_vect)
{
	TCNT0 = v_T0ReloadVal;
	v_T0OVFCount++;
	
	if(T0_User_ISR != NULL)
	{
		T0_User_ISR();
	}
}

ISR (TIMER1_OVF_vect)
{
	TCNT1 = v_T1ReloadVal;
	v_T1OVFCount++;
	
	if(T1_User_ISR != NULL)
	{
		T1_User_ISR();
	}
}

ISR (TIMER2_OVF_vect)
{
	TCNT2 = v_T2ReloadVal;
	v_T2OVFCount++;
	
	if(T2_User_ISR != NULL)
	{
		T2_User_ISR();
	}
}

/*******************************************
			End of ISR
*******************************************/
