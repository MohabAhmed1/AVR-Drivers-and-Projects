/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:ADC               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX *((volatile u8*)0x27)

#define ADCSRA *((volatile u8*)0x26)

#define ADCH *((volatile u8*)0x25)

#define ADCL *((volatile u8*)0x24)


#endif /* ADC_REGISTER_H_ */
