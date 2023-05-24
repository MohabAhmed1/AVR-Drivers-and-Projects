/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:ADC               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_
/*choose the required ADC resolution 8 or 10 bits*/
#define ADC_RES ADC_RES_EIGHT_BITS

/*choose the reference voltage (external with cap,internal ,internal to 2.56v)*/
#define ADC_REF ADC_AREF_EXTERNAL


/*Prescaler divsion from 2 to 128 */
#define PRESCALER DVISION_BY_128

/*
  choose ADC trigger source:
 1.Free running mode  ->FREE_RUNNING
 2.Analog Comparator  ->ANALOG_COMPARATOR
 3.External Interrupt ->EXTERNAL_INTERRUPT
 */
#define TRIGGER_SOURCE FREE_RUNNING

/*choose to enable or disable the ADC Auto trigger*/
#define ADC_AUTO_TRIGGER DISABLE
/*ADC asynch conversion time out*/
#define ADC_u32TIMEOUT 50000
#endif /* ADC_CONFIG_H_ */
