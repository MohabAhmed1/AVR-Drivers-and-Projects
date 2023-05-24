/*
 * USART_config.h
 *
 *  Created on: Oct 27, 2022
 *      Author: speedTECH
 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#define CHAR_SIZE 8   /*Character size: 5 , 6  , 7 , 8 , 9	*/
#define STOP_BIT  1
#define PARITY	  DISABLE

#define PARITY_MODE	EVEN_PARITY

#define USART_SYNCH_METHOD ASYNCH

#define TX 		  ENABLE
#define RX 		  ENABLE
#define BAUD_RATE 9600L /*BaudRate: 2400,4800,9600,14.4k,19.2k,28.8k*/





#endif /* USART_CONFIG_H_ */
