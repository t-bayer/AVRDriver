/*************************************************************/
/**
 *  @file EEPROMDriver.c
 *  @brief Simple driver for using a EEPROM over I2C on AVR ATMEGA8
 *  @author Timo Bayer
 *
 *  @date 25.05.2016
 *  @version 1.0
 *************************************************************/

#include <stdint.h>
#include "TWIDriver.h"

char deviceAddress = 0xA;

/**
 * @brief Initialises the EEPROM
 *
 * This function initialises the EEPROM by setting the device address and the TWI registers
 *
 * @param[in] data Specifies the device address
 */
void EEPROM_Init(char address){
	deviceAddress = (deviceAddress << 4) | address;
	TWI_Init();
}

/**
 * @brief Reads a byte from the EEPROM
 *
 * This function reads a byte from the EEPROM on the specified address
 *
 * @param[in] address The address to be read
 * @param[in] ptr Contains the data which is read from the EEPROM
 */
void EEPROM_Read(uint16_t address, char* ptr){
	TWI_Start();
	TWI_Write(deviceAddress);
	TWI_Write(address & 0xFF);
	TWI_Write(address >> 8);
	TWI_Start();
	TWI_Write(deviceAddress | (1<<0));
	TWI_Read(ptr);
	TWI_Stop();
}
/**
 * @brief Writes a byte on the EEPROM
 *
 * This function writes a byte on the specified EEPROM address
 *
 * @param[in] data Specifies the data to be stored
 * @param[in] address Specifies the target address 
 */
void EEPROM_Write (char data, uint16_t address){
	TWI_Start();
	TWI_Write(deviceAddress); 
	TWI_Write(address & 0xFF);
	TWI_Write(address >> 8);
	TWI_Write(data);
	TWI_Stop();
}
