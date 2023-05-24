/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:PWM               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

void Timer1_voidInit(void);
void Timer1_voidSetICR(u16 Copy_u16ICRVal);
void Timer1_voidSetOCR(u16 Copy_u16OCRVal);

#endif /* PWM_INTERFACE_H_ */
