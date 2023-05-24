/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:EXTI              ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_
#define LOW_LEVEL    		1
#define ON_CHANGE  			2
#define FALLING_EDGE       	3
#define RISING_EDGE    		4

#define INT0    			1
#define INT1 				2
#define INT2				3


/*functions by using prebuild configurations*/
void EXTI_voidInt0Init(void);

void EXTI_voidInt1Init(void);

void EXTI_voidInt2Init(void);

/*functions by using postbuild configurations*/
u8 EXTI_u8Int0SenseControl(u8 Copy_u8Sense);
u8 EXTI_u8Int1SenseControl(u8 Copy_u8Sense);
u8 EXTI_u8Int2SenseControl(u8 Copy_u8Sense);

u8 EXTI_u8IntEnable(u8 Copy_u8Int);
u8 EXTI_u8IntDisable(u8 Copy_u8Int);

u8 EXTI_u8Int0SetCallBack(void (*Copy_pvInt0Func) (void));

#endif /* EXTI_INTERFACE_H_ */
