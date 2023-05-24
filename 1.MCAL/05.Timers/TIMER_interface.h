/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:Timer             ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
#define ICU_Rising  1
#define ICU_Falling 2
typedef struct
{
	u8 Timer1_Mode;
	u8 Prescaler;
}Timer1_t;
void TIMER0_voidInit(void);
void TIMER0_voidSetTimerVal(u8 Copy_u8TimerVal);
void Timer0_voidSetOCR(u8 Copy_u8OCRVal);


void TIMER1_voidInit(Timer1_t * Timer1);
void TIMER1_voidSetTimerVal(u16 Copy_u16TimerVal);
u16 TIMER1_voidGetTimer1Reading(void);
void Timer1_voidSetOCR1A(u16 Copy_u16OCRAVal);
void Timer1_voidSetOCR1B(u16 Copy_u16OCRBVal);

u8 TIMER0_u8CalculateTime(u16 Copy_u8TimeInSec);
u8 TIMER0_CTC_u8SetCallBack(void (*Copy_pvCallbackFunc) (void));
u8 TIMER0_Normal_u8SetCallBack(void (*Copy_pvCallbackFunc) (void));

u8 TIMER1_Normal_u8SetCallBack(void (*Copy_pvCallbackFunc) (void));
u8 TIMER1_CTCA_u8SetCallBack(void (*Copy_pvCallbackFunc) (void));
u8 TIMER1_CTCB_u8SetCallBack(void (*Copy_pvCallbackFunc) (void));

void ICU_voidInit(void);
u8 ICU_u8SetTriggerEdge(u8 Copy_u8TrigEdge);
void ICU_voidEnableInterrupt(void);
void ICU_voidDisableInterrupt(void);
u16 ICU_u16ReadICR(void);
u8 ICU_u8SetCallback(void (*Copy_pvCallBackFunc)(void));



//void TIMER0_voidSetCompaMatchVal(u8 Copy_u8Value);


#endif /* TIMER_INTERFACE_H_ */
