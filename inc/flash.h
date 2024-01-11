


#ifndef		__FLASH__

#define	__FLASH__

#include <stm32f10x.h>
#include "timer.h" 
#include "string.h" 

extern int check; 

void configFlash(void); 
uint16_t Flash_Read_Int(uint32_t addr); 
void Flash_Write_Char(uint32_t addr, char* data); 
void Flash_ReadChar(char* dataOut, uint32_t addr1, uint32_t addr2); 
void Flash_ProgramPage(char* dataIn, uint32_t addr1, uint32_t addr2); 
void Flash_Write_Int(uint32_t addr, int16_t data); 
void Flash_Erase(uint32_t addr); 
void Flash_Unlock(); 
void deleteBuffer(char* data); 
void configFlash(void); 

#endif