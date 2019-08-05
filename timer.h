#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include "stdutils.h"

/**********************************
Constants and Macros for Timers
***********************************/

#define TIMER_0 0
#define TIMER_1 1
#define TIMER_2 2
#define MAX_TIMERS 3

#define TIMER0_MIN 1
#define TIMER0_MAX 16384

#define TIMER1_MIN 1
#define TIMER1_MAX 4194304

#define TIMER2_MIN 1
#define TIMER2_MAX 16384

typedef void (*isrFunPtr_t)(void);

/**********************************/

/**********************************
Timer Function Prototypes
**********************************/

void TIMER_Init(uint8_t timerNum, uint32_t timerIntvl);

void TIMER_Start(uint8_t timerNum);
void TIMER_Stop(uint8_t timerNum);

void TIMER_AttachINT(uint8_t timerNum, isrFunPtr_t funPtr);

void TIMER_SetTime(uint8_t timerNum, uint32_t timerIntvl);
uint32_t TIMER_GetTime(uint8_t timerNum);

#endif
