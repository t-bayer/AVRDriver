#ifndef _TWI_Driver
#define _TWI_Driver

void TWI_Init(void);
void TWI_Start(void);
void TWI_Write(char data);
void TWI_Read(char* ptr);
void TWI_Stop(void);

#endif
