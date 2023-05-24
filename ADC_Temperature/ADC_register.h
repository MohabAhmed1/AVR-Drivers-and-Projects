/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:ADC               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX 		*((volatile u8*)0x27) //ADC multiplexer selection register
#define ADMUX_REFS1 7					  //Reference selection bit1
#define ADMUX_REFS0 6					  //Reference selection bit0
#define ADMUX_ADLAR 5					  //ADC left adjust result


#define ADCSRA 		*((volatile u8*)0x26) //ADC Control and Status Register A

#define ADCSRA_ADEN 	7					//ADC enable
#define ADCSRA_ADSC 	6					//ADC start conversion
#define ADCSRA_ADATE	5					//ADC auto trigger enable
#define ADCSRA_ADIF     4					//ADC Interrupt flag
#define ADCSRA_ADIE		3     				//ADC Interrupt enable
#define ADCSRA_ADPS2	2					//ADC prescaler bit2
#define ADCSRA_ADPS1	1					//ADC prescaler bit1
#define ADCSRA_ADPS0	0					//ADC prescaler bit0

#define ADCH		*((volatile u8*)0x25)   //ADC high register

#define ADCL 		*((volatile u8*)0x24)	//ADC low register

#define ADC			*((volatile u16*)0x24) //ADC high and low registers


#define SFIOR       *((volatile u8 *)0x50)
#define SFIOR_ADTS2  7
#define SFIOR_ADTS1  6
#define SFIOR_ADTS0  5


#endif /* ADC_REGISTER_H_ */
