/*************************************************************/
/**
 *  @file TWIDriver.c
 *  @brief Simple driver for using TWI on AVR ATMEGA8
 *  @author Timo Bayer
 *
 *  @date 25.05.2016
 *  @version 1.0
 *************************************************************/

#include <avr/io.h>

/**
 * @brief Initialise the TWI
 *
 * This function initialises the TWI registers by setting the prescaler, bit rate and enable bit
 */
void TWI_Init(void){
	TWSR = 0;               //Prescaler for TWI frequency -> No prescaler
	TWBR = 32;	        //Set bit rate to 100khz with 8Mhz CPU
	TWCR |= (1<<TWEN);	//Enable I2C module
}

/**
 * @brief Sends the start signal to initiate the TWI communication
 *
 * This function sends the start signal and waits until the answer bit is set
 */
void TWI_Start(void){
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

/**
 * @brief Writes a byte on the TWI channel
 *
 * This function writes a byte passed as argument on the TWI channel
 *
 * @param[in] data Specifies the data to be sent
 */
void TWI_Write(char data){
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

/**
 * @brief Reads a byte from the TWI channel
 *
 * This function reads a byte from the TWI channel which can be accessed by the pointer passed to the function
 *
 * @param[out] ptr Specifies the adress which is used to store the data
 */
void TWI_Read(char* ptr){
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	*ptr = TWDR;
}

/**
 * @brief Sends the stop signal to end the TWI communication
 *
 * This function sends the stop signal
 */
void TWI_Stop(void){
	TWCR = (1<<TWSTO) | (1<<TWEN) | (1<<TWINT);
}
