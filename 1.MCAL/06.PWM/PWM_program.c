/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:PWM               ******************/
/****************    Version:1.00          ******************/
/************************************************************/

#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "PWM_interface.h"
#include "PWM_register.h"
#include "PWM_private.h"
#include "PWM_config.h"

void PWM_Timer0_voidInit(PWM_t * PWM)
{
	if(PWM->PWM_mode==FAST_PWM)
	{
		SET_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		if(PWM->PWM_mode_type==REVERSED_FAST_PWM)
		{
			SET_BIT(TCCR0,TCCR0_COM01);
			CLR_BIT(TCCR0,TCCR0_COM00);
			PWM_Timer0_voidSetOCR(RESOLUTION-OCR0_VAL);

		}
		else if (PWM->PWM_mode_type==NON_REVERSED_FAST_PWM)
		{
			SET_BIT(TCCR0,TCCR0_COM01);
			SET_BIT(TCCR0,TCCR0_COM00);
			PWM_Timer0_voidSetOCR(OCR0_VAL);
		}
	}
	else if(PWM->PWM_mode==PHASE_CORRECT_PWM)
	{
		SET_BIT(TCCR0,TCCR0_WGM00);  //non reversed phase correct
		CLR_BIT(TCCR0,TCCR0_WGM01);
		PWM_Timer0_voidSetOCR(OCR0_VAL);

	}
	TCCR0&=PRESCALER_MASK;
	if(PWM->Prescaler==DIVIDE_BY_8)
	{
		TCCR0|=DIVIDE_BY_8;
	}
	else if (PWM->Prescaler==PRESCALE_DIVIDE_BY_64)
	{
		TCCR0|=PRESCALE_DIVIDE_BY_64;
	}
	else if(PWM->Prescaler==PRESCALE_DIVIDE_BY_256)
	{
		TCCR0|=PRESCALE_DIVIDE_BY_256;
	}
	else if(PWM->Prescaler==PRESCALE_DIVIDE_BY_1024)
	{
		TCCR0|=PRESCALE_DIVIDE_BY_1024;
	}
}
void PWM_Timer1_voidInit(PWM_t * PWM)
{
	/*Fast PWM Set on top clear on compare*/
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	/*CTC mode TOP ICR editing*/
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1A_WGM10);

	/*Set Prescaler*/
	TCCR1B&=PRESCALER_MASK;
	TCCR1B|=DIVIDE_BY_8;

}
void PWM_Timer0_voidSetOCR(u8 Copy_u8OCRVal)
{
	OCR0=Copy_u8OCRVal;
}
void PWM_Timer1_voidSetICR(u16 Copy_u16ICRTop)
{
	ICR1=Copy_u16ICRTop;
}

void PWM_Timer1_voidSetOCRA(u16 Copy_u16OCRAVal)
{
	OCR1A=Copy_u16OCRAVal;
}
void PWM_Timer1_voidSetOCRB(u16 Copy_u16OCRBVal)
{
	OCR1B=Copy_u16OCRBVal;
}
