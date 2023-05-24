/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:Timer             ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*
 Options:
 1.Timer0 ->8bit
 2.Timer1 ->16 bit
 3.Timer2 ->8bit
 */
#define TIMER_TYPE TIMER0
/*
 Options:
 1.Normal Mode
 2. Compare match Mode
 */
#define TIMER_MODE CTC_MODE

/*
 Options:
 1.no clock source
 2.no prescaling
 3.prescale by 8
 4.prescale by 64
 5.prescale by 256
 6.prescale by 1024
 7.External clock connected to T0 at falling edge
 8.External clock connected to T0 at rising edge
 */

#define CLOCK_SELECT PRESCALE_DIVIDE_BY_8


#define TIMER_RESOLUTION _8_BIT_RES

#define OCR0_VAL   64
#define OCR1A_VAL  64
#define OCR1B_VAL  64

#define TCNT0_VAL  0
#define TCNT1_VAL  0

#endif /* TIMER_CONFIG_H_ */
