/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:Timer             ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TIMER0 1  /*8 bits timer*/
#define TIMER1 2  /*16 bits timer*/
#define TIMER2 3  /*8 bits timer*/


#define NORMAL_MODE 1  /*Overflow mode*/
#define CTC_MODE    2	/*Compare match mode*/


#define NO_CLOCK_SRC				    0
#define NO_PRESCALING 					1
#define PRESCALE_DIVIDE_BY_8 			2
#define PRESCALE_DIVIDE_BY_64 			3
#define PRESCALE_DIVIDE_BY_256 		    4
#define PRESCALE_DIVIDE_BY_1024 		5
#define EXTERNAL_CLOCK_SOURCE_FALLING 	6
#define EXTERNAL_CLOCK_SOURCE_RISING 	7

#define CLOCK_SELCET_MASK 0b11111000
#define _8_BIT_RES  256
#define _10_BIT_RES  1024
#define SYSTEM_FREQ 8000000




#endif /* TIMER_PRIVATE_H_ */
