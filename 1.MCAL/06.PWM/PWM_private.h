/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:PWM               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef PWM_PRIVATE_H_
#define PWM_PRIVATE_H_

#define PRESCALER_MASK 0b11111000

#define FAST_PWM 		   1
#define PHASE_CORRECT_PWM  2

#define REVERSED_FAST_PWM      	1
#define NON_REVERSED_FAST_PWM	2

#define RESOLUTION 255

#define NO_CLOCK_SRC				    0
#define NO_PRESCALING 					1
#define DIVIDE_BY_8  					2
#define PRESCALE_DIVIDE_BY_64 			3
#define PRESCALE_DIVIDE_BY_256 		    4
#define PRESCALE_DIVIDE_BY_1024 		5
#define EXTERNAL_CLOCK_SOURCE_FALLING 	6
#define EXTERNAL_CLOCK_SOURCE_RISING 	7
#endif /* PWM_PRIVATE_H_ */
