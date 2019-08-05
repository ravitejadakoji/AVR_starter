#ifndef LCD_H_
#define	LCD_H_

#include "stdutils.h"
#include "gpio.h"

/*****************************
 LCD API's Enable or Disable
 ***************************/

#define Enable_LCD_SetCursor        1
#define Enable_LCD_DisplayString    1
#define Enable_LCD_ScrollMsg        1
#define Enable_LCD_DisplayNumber    1
#define Enable_LCD_DisplayFloat     1
#define Enable_LCD_Printf           1


/***************************
 Commonly used LCD Commands
 ***************************/

#define CMD_LCD_CLEAR                       0x01u
#define CMD_LCD_RETURN_HOME                 0x02u
#define CMD_LCD_DISPLAY_ON_CURSOR_OFF       0x0Cu
#define CMD_LCD_DIPSLAY_ON_CURSOR_ON        0x0Eu
#define CMD_LCD_DIPSLAY_ON_CURSOR_BLINK     0x0Fu
#define CMD_LCD_4_BIT_MODE                  0x28u
#define CMD_LCD_8_BIT_MODE                  0x38u


/**************
 LCD Constants
 ***************/

#define C_EightBitMode  8u
#define C_FourBitMode   4u

#define C_ScrollDelay   200

#define C_DisplayDefaultDigits      0xFFu
#define C_MaxDigitsToDisplay        10u
#define C_NumOfBinDigitsToDisplay   16u
#define C_MaxDigitsToDisplayPrintf  C_DisplayDefaultDigits

#define C_LCDLineZero     0x00
#define C_LCDLineOne      0x01
#define C_LCDLineTwo      0x02
#define C_LCDLineThree    0x03
#define C_LCDMaxLines     0x04


/**************************
 LCD Structures and Enums
 **************************/

typedef struct
{
    uint8_t v_maxSuppLines;
    uint8_t v_maxSuppChars;
    uint8_t v_LCDMode;
    gpioPins_et RS;
    gpioPins_et RW;
    gpioPins_et EN;
    gpioPins_et D0;
    gpioPins_et D1;
    gpioPins_et D2;
    gpioPins_et D3;
    gpioPins_et D4;
    gpioPins_et D5;
    gpioPins_et D6;
    gpioPins_et D7;
}LCDConfig_st;


/************************
 LCD Function Prototypes
 ************************/

void LCD_Setup(gpioPins_et RS,
               gpioPins_et RW,
               gpioPins_et EN,
               gpioPins_et D0,
               gpioPins_et D1,
               gpioPins_et D2,
               gpioPins_et D3,
               gpioPins_et D4,
               gpioPins_et D5,
               gpioPins_et D6,
               gpioPins_et D7);

void LCD_Init(uint8_t var_LCDNoOfLines, uint8_t var_maxCharsPerLine);
void LCD_CMDWrite(uint8_t var_LCDCMD);
void LCD_Clear();

void LCD_DisplayChar(char var_LCDData);
void LCD_DisplayString(const char *ptr_strptr);

void LCD_DisplayNumber(uint8_t var_numSystem, uint32_t var_number_32, uint8_t var_numOfDigitsToDisplay);
void LCD_DisplayFloat(double var_floatNum_32);

void LCD_ScrollMsg(uint8_t var_lineNum, char *ptr_msgPtr);

void LCD_SetCursor(uint8_t var_lineNum, uint8_t var_charNum);
void LCD_GoToLine(uint8_t var_lineNum);
void LCD_GoToNextLine();

void LCD_Printf(const char *argList, ...);

#endif
