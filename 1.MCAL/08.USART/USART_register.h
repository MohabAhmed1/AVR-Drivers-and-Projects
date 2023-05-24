/*
 * USART_register.h
 *
 *  Created on: Oct 27, 2022
 *      Author: speedTECH
 */

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

#define UDR 	*((volatile u8*)0x2C)  /* I/O data register */

#define UCSRA 	*((volatile u8*)0x2B)
#define UCSRA_RXC 	7 		/*USART receive complete*/
#define UCSRA_TXC 	6		/*USART transmit complete*/
#define UCSRA_UDRE  5		/*USART Data register empty*/
#define UCSRA_FE	4		/*USART frame error*/
#define UCSRA_DOR	3		/*USART data overrun*/
#define UCSRA_PE	2		/*USART parity error*/
#define UCSRA_U2X	1		/*USART double communication speed*/
#define UCSRA_MPCM	0		/*USART Multiprocessors communication mode*/

#define UCSRB	*((volatile u8*)0x2A)
#define UCSRB_RXCIE 7 		/*USART RX completed interrupt enable*/
#define UCSRB_TXCIE 6		/*USART TX completed interrupt enable*/
#define UCSRB_UDRIE 5		/*USART Data register empty interrupt enable*/
#define UCSRB_RXEN  4		/*USART RX enable*/
#define UCSRB_TXEN  3		/*USART TX enable*/
#define UCSRB_UCSZ2 2		/*USART bit no 2 in the character size select bits*/
#define UCSRB_RXB8 	1		/*USART bit no 9 if the receiving is 9 bits*/
#define UCSRB_TXB8  0		/*USART bit no 9 if the transmitting is 9 bits*/

#define UCSRC	*((volatile u8*)0x40)
#define UCSRC_URSEL 7  		/*USART register select*/
#define UCSRC_UMSEL 6		/*USART Mode select*/
#define UCSRC_UPM1  5		/*USART Parity mode 1 */
#define UCSRC_UPM0  4		/*USART Parity mode 0 */
#define UCSRC_USBS  3       /*USART stop bit select */
#define UCSRC_UCSZ1 2		/*USART bit no 1 in the character size select bits*/
#define UCSRC_UCSZ0 1		/*USART bit no 0 in the character size select bits*/
#define UCSRC_UCPOL 0		/*USART clock parity in Synchronous mode only*/


#define UBRRH	*((volatile u8*)0x40)
#define UBRRH_URSEL 7		/*USART register select*/
#define UBRRH_UBRR3	3		/*USART baud rate first register*/
#define UBRRH_UBRR2	2
#define UBRRH_UBRR1	1
#define UBRRH_UBRR0 0

#define UBRRL	*((volatile u8*)0x29)  /*USART baud rate second register*/

#endif /* USART_REGISTER_H_ */
