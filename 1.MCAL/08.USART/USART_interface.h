/*
 * USART_interface.h
 *
 *  Created on: Oct 27, 2022
 *      Author: speedTECH
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


void USART_voidInit(void);

u8 USART_u8SendAsync(u8 Copy_pu8Data,void(*Copy_pvNotificationFunc)(void));
u8 USART_u8ReceiveAsync(u8 *Copy_pu8Data,void(*Copy_pvNotificationFunc)(void));

void USART_voidSendSync(u8 Copy_u8Data);
u8 USART_u8ReceiveSync(void);

#endif /* USART_INTERFACE_H_ */
