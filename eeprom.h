#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include "stdutils.h"

/****************
 EEPROM Constants
 ***************/

#define C_MaxEEPROMSize 1024

/*************************************
Configs to enable/disable EEPROM API's
**************************************/

#define Enable_EEPROM_WriteNBytes   1
#define Enable_EEPROM_ReadNBytes 	1
#define Enable_EEPROM_WriteString   1
#define Enable_EEPROM_ReadString 	1
#define Enable_EEPROM_Erase 		1


/**********************************
EEPROM Function Prototypes
**********************************/

void EEPROM_WriteByte(uint16_t var_eepromAdd, uint8_t var_eepromData);
uint8_t EEPROM_ReadByte(uint16_t var_eepromAdd);

void EEPROM_WriteNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes);
void EEPROM_ReadNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes);

void EEPROM_WriteString(uint16_t var_eepromAdd, char *ptr_strptr);
void EEPROM_ReadString(uint16_t var_eepromAdd, char *ptr_strAdd);

void EEPROM_Erase(void);

#endif
