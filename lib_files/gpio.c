#include <avr/io.h>
#include "stdutils.h"
#include "gpio.h"

/***************************
 GPIO Pin Direction Function
 ***************************/

void GPIO_PinDir(gpioPins_et enm_pinNum, uint8_t var_pinDir)
{
    uint8_t v_portNum;
    
    v_portNum = (enm_pinNum >> 3);
    enm_pinNum = (enm_pinNum & 0x07);
    
    switch(v_portNum)
    {
        #ifdef DDRA
		case 0:
            UpdateBit(DDRA,enm_pinNum,var_pinDir);
            break;
        #endif
		
		#ifdef DDRB
        case 1:
            UpdateBit(DDRB,enm_pinNum,var_pinDir);
            break;
        #endif    
			
        #ifdef DDRC
        case 2:
			UpdateBit(DDRC,enm_pinNum,var_pinDir);
			break;
        #endif
		
		#ifdef DDRD
		case 3:
			UpdateBit(DDRD,enm_pinNum,var_pinDir);
			break;
		#endif
		
		#ifdef DDRE
		case 4:
			UpdateBit(DDRE,enm_pinNum,var_pinDir);
			break;
		#endif
		
		#ifdef DDRF	
		case 5:
			UpdateBit(DDRF,enm_pinNum,var_pinDir);
			break;
		#endif
		
		#ifdef DDRG
		case 6:
			UpdateBit(DDRG,enm_pinNum,var_pinDir);
			break;
		#endif
		
		
	}
}

/************************
 GPIO Pin Write Function
 *************************/

void GPIO_PinWrite(gpioPins_et enm_pinNum, uint8_t var_pinVal)
{
    uint8_t v_portNum;
    
    v_portNum = (enm_pinNum >> 3);
    enm_pinNum = (enm_pinNum & 0x07);
    
    switch(v_portNum)
    {
        #ifdef PORTA
        case 0:
			UpdateBit(PORTA,enm_pinNum,var_pinDir);
			break;
        #endif
        
        #ifdef PORTB
        case 1:
			UpdateBit(PORTB,enm_pinNum,var_pinDir);
			break;
        #endif
        
        #ifdef PORTC
        case 2:
			UpdateBit(PORTC,enm_pinNum,var_pinDir);
			break;
        #endif
        
        #ifdef PORTD
        case 3:
			UpdateBit(PORTD,enm_pinNum,var_pinDir);
			break;
        #endif
        
        #ifdef PORTE
        case 4:
			UpdateBit(PORTE,enm_pinNum,var_pinDir);
			break;
        #endif
        
        #ifdef PORTF
        case 5:
			UpdateBit(PORTF,enm_pinNum,var_pinDir);
			break;
        #endif
        
        #ifdef PORTG
        case 6:
			UpdateBit(PORTG,enm_pinNum,var_pinDir);
			break;
        #endif
    }
}

/**********************
 GPIO Pin Read Function
 **********************/

uint8_t GPIO_PinRead(gpioPins_et enm_pinNum)
{
    uint8_t v_portNum;
    uint8_t pinStatus = 0;
    
    v_portNum = (enm_pinNum >> 3);
    enm_pinNum = (enm_pinNum & 0x07);
    
    switch(v_portNum)
    {
		#ifdef PINA
		case 0:
            pinStatus = GetBitStatus(PINA,enm_pinNum);
            break;
		#endif
            
        #ifdef PINB
        case 1:
			pinStatus = GetBitStatus(PINB,enm_pinNum);
			break;
        #endif
		
		#ifdef PINC
		case 2:
			pinStatus = GetBitStatus(PINC,enm_pinNum);
			break;
		#endif
		
		#ifdef PIND
		case 3:
			pinStatus = GetBitStatus(PIND,enm_pinNum);
			break;
		#endif
		
		#ifdef PINE
		case 4:
			pinStatus = GetBitStatus(PINE,enm_pinNum);
			break;
		#endif
		
		#ifdef PINF
		case 5:
			pinStatus = GetBitStatus(PINF,enm_pinNum);
			break;
		#endif
		
		#ifdef PING
		case 6:
			pinStatus = GetBitStatus(PING,enm_pinNum);
			break;
		#endif
    }
    return pinStatus;
}

