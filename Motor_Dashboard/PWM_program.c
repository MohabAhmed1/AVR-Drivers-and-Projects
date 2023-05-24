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
void Timer1_voidInit(void)
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
void Timer1_voidSetICR(u16 Copy_u16ICRTop)
{
	ICR1=Copy_u16ICRTop;
}

void Timer1_voidSetOCR(u16 Copy_u16OCRVal)
{
	OCR1A=Copy_u16OCRVal;
}
