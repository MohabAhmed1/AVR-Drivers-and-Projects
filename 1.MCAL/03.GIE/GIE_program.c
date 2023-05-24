/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:GIE               ******************/
/****************    Version:1.00          ******************/
/************************************************************/

#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "GIE_interface.h"
#include "GIE_register.h"

void GIE_voidEnable(void)
{
	/*Set SREG_I bit to enable GIE */
	SET_BIT(SREG,SREG_I);
}
void GIE_voidDisable(void)
{
	/*Clear SREG_I bit to disable GIE */
	CLR_BIT(SREG,SREG_I);
}
