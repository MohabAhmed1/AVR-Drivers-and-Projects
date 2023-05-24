/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:PWM               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef PWM_REGISTER_H_
#define PWM_REGISTER_H_

#define TCCR0  	*((volatile u8*)0x53)   /*Timer0 control register*/

#define TCCR1A 	*((volatile u8*)0x4F)	/*Timer1 A control register*/
#define TCCR1A_COM1A1 7
#define TCCR1A_COM1A0 6
#define TCCR1A_COM1B1 5
#define TCCR1A_COM1B0 4
#define TCCR1A_WGM11  1
#define TCCR1A_WGM10  0

#define TCCR1B 	*((volatile u8 *)0x4E)	/*Timer1 B control register*/
#define TCCR1B_WGM13  4
#define TCCR1B_WGM12  3
#define TCCR1B_CS10  0
#define TCCR1B_CS11  1
#define TCCR1B_CS12  2

#define OCR1A 	*((volatile u16 *)0x4A)	/*Output compare register A*/

#define OCR1B 	*((volatile u16 *)0x48)	/*Output compare register B*/

#define ICR1  	*((volatile u16 *)0x46)	/*Input capture register*/

#endif /* PWM_REGISTER_H_ */
