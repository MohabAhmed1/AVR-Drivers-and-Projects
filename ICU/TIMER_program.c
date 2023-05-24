/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:Timer             ******************/
/****************    Version:1.00          ******************/
/************************************************************/

#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "TIMER_interface.h"
#include "TIMER_register.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

static void (*TIMER0_CTC_pvCallBackFunc)(void)=NULL;
static void (*TIMER0_Normal_pvCallBackFunc)(void)=NULL;

static void (*TIMER1_Normal_pvCallBackFunc)(void)=NULL;
static void (*TIMER1_CTCA_pvCallBackFunc)(void)=NULL;
static void (*TIMER1_CTCB_pvCallBackFunc)(void)=NULL;
static void (*ICU_pv_CallBackFunc)(void)=NULL;

void TIMER0_voidInit(void)
{
#if TIMER_MODE==NORMAL_MODE
	/*Choose Normal mode*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
	/*Normal mode interrupt enable */
	SET_BIT(TIMSK,TIMSK_TOIE0);
	TIMER0_voidSetTimerVal(TCNT0_VAL);

#elif TIMER_MODE==CTC_MODE
	/*Choose CTC mode*/
	//	CLR_BIT(TCCR0,TCCR0_WGM00);
	//	SET_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	/*Output match interrupt enable */
	SET_BIT(TIMSK,TIMSK_OCIE0);
	Timer0_voidSetOCR(OCR0_VAL);

#endif


	TCCR0 &=CLOCK_SELCET_MASK;
#if CLOCK_SELECT== NO_CLOCK_SRC
	TCCR0|=NO_CLOCK_SRC;
#elif CLOCK_SELECT== NO_PRESCALING
	TCCR0|=NO_PRESCALING;
#elif CLOCK_SELECT== PRESCALE_DIVIDE_BY_8
	TCCR0|=PRESCALE_DIVIDE_BY_8;
#elif CLOCK_SELECT== PRESCALE_DIVIDE_BY_64
	TCCR0|=PRESCALE_DIVIDE_BY_64;
#elif CLOCK_SELECT== PRESCALE_DIVIDE_BY_256
	TCCR0|=PRESCALE_DIVIDE_BY_256;
#elif CLOCK_SELECT== PRESCALE_DIVIDE_BY_1024
	TCCR0|=PRESCALE_DIVIDE_BY_1024;
#error "Wrong Clock select Specifications"
#endif

}
void TIMER1_voidInit(Timer1_t * Timer1)
{
	if (Timer1->Timer1_Mode==NORMAL_MODE)
	{
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1A,TCCR1A_WGM10);

		SET_BIT(TIMSK,TIMSK_TOIE1);
//		TIMER1_voidSetTimerVal(TCNT1_VAL);
	}
	else if(Timer1->Timer1_Mode==CTC_MODE)
	{
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TIMSK,TIMSK_OCIE1A);
		SET_BIT(TIMSK,TIMSK_OCIE1B);
		Timer1_voidSetOCR1A(OCR1A_VAL);
		Timer1_voidSetOCR1B(OCR1B_VAL);
	}

	TCCR1B&=CLOCK_SELCET_MASK;
	if(Timer1->Prescaler==PRESCALE_DIVIDE_BY_8)
	{
		TCCR1B|=PRESCALE_DIVIDE_BY_8;
	}
	else if(Timer1->Prescaler==PRESCALE_DIVIDE_BY_64)
	{
		TCCR1B|=PRESCALE_DIVIDE_BY_64;
	}
	else if(Timer1->Prescaler==PRESCALE_DIVIDE_BY_256)
	{
		TCCR1B|=PRESCALE_DIVIDE_BY_256;
	}
	else if(Timer1->Prescaler==PRESCALE_DIVIDE_BY_1024)
	{
		TCCR1B|=PRESCALE_DIVIDE_BY_1024;
	}
}

void ICU_voidInit(void)
{
	/*Set trigger source to rising edge initially*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);
	/*enable input capture interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}
u8 ICU_u8SetTriggerEdge(u8 Copy_u8TrigEdge)
{
	u8 Local_u8ErrorStatus=OK;
	if(Copy_u8TrigEdge==ICU_Rising)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}

	else if(Copy_u8TrigEdge==ICU_Falling)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else
	{
		Local_u8ErrorStatus=NOK;
	}
	return Local_u8ErrorStatus;
}
void ICU_voidEnableInterrupt(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}
void ICU_voidDisableInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);

}
u16 ICU_u16ReadICR(void)
{
	return ICR1;
}

u8 ICU_u8SetCallback(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorStatus=OK;
	if (Copy_pvCallBackFunc==NULL)
	{
		Local_u8ErrorStatus=NULL;
	}
	else
	{
		ICU_pv_CallBackFunc=Copy_pvCallBackFunc;
	}
	return Local_u8ErrorStatus;
}
void TIMER0_voidSetTimerVal(u8 Copy_u8TimerVal)
{
	TCNT0=Copy_u8TimerVal;
}
void Timer0_voidSetOCR(u8 Copy_u8OCRVal)
{
	OCR0=Copy_u8OCRVal;
}

u16 TIMER1_voidGetTimer1Reading(void)
{
	return TCNT1;
}
void TIMER1_voidSetTimerVal(u16 Copy_u16TimerVal)
{
	TCNT1=Copy_u16TimerVal;
}
void Timer1_voidSetOCR1A(u16 Copy_u16OCRVal)
{
	OCR1A=Copy_u16OCRVal;
}

void Timer1_voidSetOCR1B(u16 Copy_u16OCRVal)
{
	OCR1B=Copy_u16OCRVal;
}
//Timer 0 CTC mode Set callback
u8 TIMER0_CTC_u8SetCallBack(void (*Copy_pvCallbackFunc) (void))
{
	u8 Local_u8ErrorStatus=OK;
	if(Copy_pvCallbackFunc==NULL)
		Local_u8ErrorStatus=NULL_POINTER;
	else
	{
		TIMER0_CTC_pvCallBackFunc=Copy_pvCallbackFunc;
	}
	return Local_u8ErrorStatus;
}
//Timer 0 Normal mode Set callback
u8 TIMER0_Normal_u8SetCallBack(void (*Copy_pvCallbackFunc) (void))
{
	u8 Local_u8ErrorStatus=OK;
		if(Copy_pvCallbackFunc==NULL)
			Local_u8ErrorStatus=NULL_POINTER;
		else
		{
			TIMER0_Normal_pvCallBackFunc=Copy_pvCallbackFunc;
		}
		return Local_u8ErrorStatus;
}
//Timer 1 Normal mode Set callback
u8 TIMER1_Normal_u8SetCallBack(void (*Copy_pvCallbackFunc) (void))
{
	u8 Local_u8ErrorStatus=OK;
	if(Copy_pvCallbackFunc==NULL)
		Local_u8ErrorStatus=NULL_POINTER;
	else
	{
		TIMER1_Normal_pvCallBackFunc=Copy_pvCallbackFunc;
	}
	return Local_u8ErrorStatus;
}
//Timer 1 CTCA mode Set callback
u8 TIMER1_CTCA_u8SetCallBack(void (*Copy_pvCallbackFunc) (void))
{
	u8 Local_u8ErrorStatus=OK;
	if(Copy_pvCallbackFunc==NULL)
		Local_u8ErrorStatus=NULL_POINTER;
	else
	{
		TIMER1_CTCA_pvCallBackFunc=Copy_pvCallbackFunc;
	}
	return Local_u8ErrorStatus;
}
//Timer 1 CTCB mode Set callback
u8 TIMER1_CTCB_u8SetCallBack(void (*Copy_pvCallbackFunc) (void))
{
	u8 Local_u8ErrorStatus=OK;
	if(Copy_pvCallbackFunc==NULL)
		Local_u8ErrorStatus=NULL_POINTER;
	else
	{
		TIMER1_CTCB_pvCallBackFunc=Copy_pvCallbackFunc;
	}
	return Local_u8ErrorStatus;
}


//Compare match timer 0 interrupt
void __vector_10 (void)  __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_CTC_pvCallBackFunc!=NULL)
	{
		TIMER0_CTC_pvCallBackFunc();
	}
}
//Normal mode timer 0 interrupt
void __vector_11 (void)  __attribute__((signal));
void __vector_11 (void)
{
	if(TIMER0_Normal_pvCallBackFunc!=NULL)
	{
		TIMER0_Normal_pvCallBackFunc();
	}
}
//Normal mode timer 1 interrupt
void __vector_9 (void)  __attribute__((signal));
void __vector_9 (void)
{
	if(TIMER1_Normal_pvCallBackFunc!=NULL)
	{
		TIMER1_Normal_pvCallBackFunc();
	}
}

//Compare match A timer 1 interrupt
void __vector_7 (void)  __attribute__((signal));
void __vector_7 (void)
{
	if(TIMER1_CTCA_pvCallBackFunc!=NULL)
	{
		TIMER1_CTCA_pvCallBackFunc();
	}
}
//Compare match B timer 1 interrupt
void __vector_8 (void)  __attribute__((signal));
void __vector_8 (void)
{
	if(TIMER1_CTCB_pvCallBackFunc!=NULL)
	{
		TIMER1_CTCB_pvCallBackFunc();
	}
}
//Input capture unit ISR
void __vector_6 (void)  __attribute__((signal));
void __vector_6 (void)
{
	if(ICU_pv_CallBackFunc!=NULL)
	{
		ICU_pv_CallBackFunc();
	}
}
