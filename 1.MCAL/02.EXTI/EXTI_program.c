/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:EXTI              ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "EXTI_interface.h"
#include "EXTI_register.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
/*Global pointer to function to hold INT ISR address*/
void (*EXTI_pvInt0Func) (void)= NULL;
void (*EXTI_pvInt1Func) (void)= NULL;
void (*EXTI_pvInt2Func) (void)= NULL;
void EXTI_voidInt0Init(void)
{
#if INT0_SENSE==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC01);
	CLR_BIT(MCUCR,MCUCR_ISC00);
#elif INT0_SENSE==ON_CHANGE
	CLR_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(MCUCR,MCUCR_ISC00);
#elif INT0_SENSE==FALLING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC01);
	CLR_BIT(MCUCR,MCUCR_ISC00);
#elif INT0_SENSE==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(MCUCR,MCUCR_ISC00);
#else
#error "Wrong INT0_SENSE configuration option"
#endif
	/*check peripheral interrupt enable initial state (SIE)*/
#if INT0_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT0);
#elif INT0_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT0);
#else
#error "Wrong INT0_INITIAL_STATE configuration option"
#endif

	/*//Sense control to INT0*
	switch (Local_u8InterruptSenseControl)
	{
	case FALLING:SET_BIT(MCUCR,MCUCR_ISC01);CLR_BIT(MCUCR,MCUCR_ISC00); break;
	case RISING:SET_BIT(MCUCR,MCUCR_ISC01);SET_BIT(MCUCR,MCUCR_ISC00);break;
	case LOW:CLR_BIT(MCUCR,MCUCR_ISC01);CLR_BIT(MCUCR,MCUCR_ISC00); break;
	case CHANGE:CLR_BIT(MCUCR,MCUCR_ISC01);SET_BIT(MCUCR,MCUCR_ISC00); break;
	default:break;
	}
	//Peripheral interrupt (SIE) enable for INT0
	SET_BIT(GICR,GICR_INT0);
	 */
}

void EXTI_voidInt1Init(void)
{


#if INT1_SENSE==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);
#elif INT1_SENSE==ON_CHANGE
	CLR_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);
#elif INT1_SENSE==FALLING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);
#elif INT1_SENSE==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);
#else
#error "Wrong INT1_SENSE configuration option"
#endif
	/*check peripheral interrupt enable initial state (SIE)*/
#if INT1_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT1);
#elif INT1_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT1);
#else
#error "Wrong INT1_INITIAL_STATE configuration option"
#endif


	/*
	//Sense control to INT1
	switch (Local_u8InterruptSenseControl)
		{
		case FALLING:SET_BIT(MCUCR,MCUCR_ISC11);CLR_BIT(MCUCR,MCUCR_ISC10); break;
		case RISING:SET_BIT(MCUCR,MCUCR_ISC11);SET_BIT(MCUCR,MCUCR_ISC10);break;
		case LOW:CLR_BIT(MCUCR,MCUCR_ISC11);CLR_BIT(MCUCR,MCUCR_ISC10); break;
		case CHANGE:CLR_BIT(MCUCR,MCUCR_ISC11);SET_BIT(MCUCR,MCUCR_ISC10); break;
		default:break;
		}

	//Peripheral interrupt(SIE) enable for INT1
	SET_BIT(GICR,GICR_INT1);
	 */
}

void EXTI_voidInt2Init(void)
{

#if INT2_SENSE==FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_INT2);
#elif 	INT2_SENSE==RISING_EDGE
	SET_BIT(MCUCR,MCUCSR_INT2);
#else
#error "Wrong INT2_SENSE configuration option"
#endif

#if INT2_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT2);
#elif 	INT2_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT2);
#else
#error "Wrong INT2_INITIAL_STATE configuration option"
#endif

	/*
	//Sense control to INT2
switch (Local_u8InterruptSenseControl)
{
case FALLING:CLR_BIT(MCUCSR,MCUCSR_INT2);break;
case RISING:SET_BIT(MCUCR,MCUCSR_INT2);break;
default:break;
}
	//Peripheral interrupt(SIE) enable for INT2
	SET_BIT(GICR,GICR_INT2);
	 */

}

u8 EXTI_u8Int0SenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;

	switch (Copy_u8Sense)
	{
	case FALLING_EDGE:SET_BIT(MCUCR,MCUCR_ISC01);CLR_BIT(MCUCR,MCUCR_ISC00); break;
	case RISING_EDGE:SET_BIT(MCUCR,MCUCR_ISC01);SET_BIT(MCUCR,MCUCR_ISC00);break;
	case LOW_LEVEL:CLR_BIT(MCUCR,MCUCR_ISC01);CLR_BIT(MCUCR,MCUCR_ISC00); break;
	case ON_CHANGE:CLR_BIT(MCUCR,MCUCR_ISC01);SET_BIT(MCUCR,MCUCR_ISC00); break;
	default:Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
u8 EXTI_u8Int1SenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;

	switch (Copy_u8Sense)
	{
	case FALLING_EDGE:SET_BIT(MCUCR,MCUCR_ISC11);CLR_BIT(MCUCR,MCUCR_ISC10); break;
	case RISING_EDGE:SET_BIT(MCUCR,MCUCR_ISC11);SET_BIT(MCUCR,MCUCR_ISC10);break;
	case LOW_LEVEL:CLR_BIT(MCUCR,MCUCR_ISC11);CLR_BIT(MCUCR,MCUCR_ISC10); break;
	case ON_CHANGE:CLR_BIT(MCUCR,MCUCR_ISC11);SET_BIT(MCUCR,MCUCR_ISC10); break;
	default:Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
u8 EXTI_u8Int2SenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;

	switch (Copy_u8Sense)
	{
	case FALLING_EDGE:CLR_BIT(MCUCSR,MCUCSR_INT2);break;
	case RISING_EDGE:SET_BIT(MCUCR,MCUCSR_INT2);break;
	default:Local_u8ErrorState=NOK;
	return Local_u8ErrorState;

	}
}

u8 EXTI_u8IntEnable(u8 Copy_u8Int)
{
	u8 Local_u8ErrorState=OK;

	switch(Copy_u8Int)
	{
	case INT0:SET_BIT(GICR,GICR_INT0);break;
	case INT1:SET_BIT(GICR,GICR_INT1);break;
	case INT2:SET_BIT(GICR,GICR_INT2);break;
	default:Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
u8 EXTI_u8IntDisable(u8 Copy_u8Int)
{
	u8 Local_u8ErrorState=OK;

	switch(Copy_u8Int)
	{
	case INT0:CLR_BIT(GICR,GICR_INT0);break;
	case INT1:CLR_BIT(GICR,GICR_INT1);break;
	case INT2:CLR_BIT(GICR,GICR_INT2);break;
	default:Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8Int0SetCallBack(void (*Copy_pvInt0Func) (void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvInt0Func!=NULL)
	{
		EXTI_pvInt0Func=Copy_pvInt0Func;
	}
	else
		Local_u8ErrorState=NULL_POINTER;
	return Local_u8ErrorState;
}

u8 EXTI_u8Int1SetCallBack(void (*Copy_pvInt1Func) (void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvInt1Func!=NULL)
	{
		EXTI_pvInt1Func=Copy_pvInt1Func;
	}
	else
		Local_u8ErrorState=NULL_POINTER;
	return Local_u8ErrorState;
}

u8 EXTI_u8Int2SetCallBack(void (*Copy_pvInt2Func) (void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvInt2Func!=NULL)
	{
		EXTI_pvInt2Func=Copy_pvInt2Func;
	}
	else
		Local_u8ErrorState=NULL_POINTER;
	return Local_u8ErrorState;
}

void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(EXTI_pvInt0Func!=NULL)
	{
	EXTI_pvInt0Func();
	}
	else
	{
		//do nothing
	}
}
