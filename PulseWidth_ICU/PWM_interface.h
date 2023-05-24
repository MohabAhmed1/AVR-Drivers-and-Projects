/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:PWM               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_
typedef struct
{
	u8 PWM_mode;
	u8 PWM_mode_type;
	u8 Prescaler;
}PWM_t;
void PWM_Timer1_voidInit(PWM_t * PWM);
void PWM_Timer0_voidInit(PWM_t * PWM);

void PWM_Timer0_voidSetOCR(u8 Copy_u8OCRVal);
void PWM_Timer1_voidSetICR(u16 Copy_u16ICRVal);
void PWM_Timer1_voidSetOCRA(u16 Copy_u16OCRAVal);
void PWM_Timer1_voidSetOCRB(u16 Copy_u16OCRBVal);

#endif /* PWM_INTERFACE_H_ */
