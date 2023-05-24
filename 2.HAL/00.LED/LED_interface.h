

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#define SINK 0
#define SOURCE 1

u8 LED_u8TurnON(u8 Copy_u8Port,u8 Copy_u8Pin,u8 ConnType);
u8 LED_u8TurnOFF(u8 Copy_u8Port,u8 Copy_u8Pin,u8 ConnType);

#endif /* LED_INTERFACE_H_ */
