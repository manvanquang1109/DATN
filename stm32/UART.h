#ifndef _UART_H
#define _UART_H

#include "stm32f10x.h"                  // Device header
#include <stdint.h>
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include <stdio.h>
#include "_HAL_GPIO.h"
#include "main.h"

#define DEBUG_UART	UART1

extern volatile uint8_t rx_char;
extern volatile uint8_t rx_string[80];
extern volatile uint16_t idx;

void initUSART1(void);
void USART1_IRQHandler(void);
void storeChar(uint8_t c, volatile uint8_t *str);
void printMsg(char *msg, ...);
void sendString(char *str, ...);
uint8_t receiveChar(void);

void transmitWhatReceived(void);

#endif
