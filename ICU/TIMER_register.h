/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:Timer             ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR0 			*((volatile u8*)0x53)   /*Timer0 control register*/
#define TCNT0			*((volatile u8*)0x52)
#define TCCR0_COM00     4
#define TCCR0_COM01		5
#define TCCR0_WGM00		6						/*Waveform generation mode bit 0*/
#define TCCR0_WGM01		3						/*Waveform generation mode bit 1*/
#define TCCR0_CS02 		2						/*Prescaler bit 2*/
#define TCCR0_CS01 		1						/*Prescaler bit 1*/
#define TCCR0_CS00 		0						/*Prescaler bit 0*/

#define OCR0 			*((volatile u8*)0x5C) 	/*output compare register 0*/
#define TIMSK			*((volatile u8*)0x59)	/*Timer Interrupt mask register*/
#define TIMSK_OCIE0     1						/*Output Compare 0 Match interrupt enable*/
#define TIMSK_TOIE0     0						/*Timer overflow interrupt enable */
#define TIMSK_TICIE1    5						/*Timer 1 input capture*/
#define TIMSK_OCIE1A    4
#define TIMSK_OCIE1B   	3
#define TIMSK_TOIE1    	2


#define TCCR1A 	*((volatile u8*)0x4F)	/*Timer1 A control register*/
#define TCCR1A_COM1A1 7
#define TCCR1A_COM1A0 6
#define TCCR1A_COM1B1 5
#define TCCR1A_COM1B0 4
#define TCCR1A_WGM11  1
#define TCCR1A_WGM10  0


#define TCCR1B 	*((volatile u8 *)0x4E)	/*Timer1 B control register*/
#define TCCR1B_WGM13    4
#define TCCR1B_WGM12 	3
#define TCCR1B_CS10  	0
#define TCCR1B_CS11  	1
#define TCCR1B_CS12  	2
#define TCCR1B_ICES1    6 /*input capture edge select*/

#define OCR1A 	*((volatile u16 *)0x4A)	/*Output compare register A*/

#define OCR1B 	*((volatile u16 *)0x48)	/*Output compare register B*/

#define TCNT1 	*((volatile u16 *)0x4C)	/*Counter register of Timer 1*/

#define ICR1  	*((volatile u16 *)0x46)	/*Input capture register*/



#endif /* TIMER_REGISTER_H_ */
