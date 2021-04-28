#ifndef _UART_H
#define _UART_H

//usart1: esp8266 	APB2	72MHz		Tx: PA9		Rx: PA10
//usart1: pc				APB1	36MHz		Tx: PB10	Rx: PB11

#include "stm32f10x.h"                  // Device header
#include <stdint.h>
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include <stdio.h>
#include "_HAL_GPIO.h"
#include "main.h"

#define DEBUG_UART	UART1
#define BUFF_LEN 240

extern volatile uint8_t rx_char;
extern volatile uint8_t rx_string[BUFF_LEN];
extern volatile uint16_t idx;

extern volatile uint8_t tx_string[BUFF_LEN];

extern volatile uint8_t usart3_char;


//function prototypes giao tiep voi esp8266: usart1
void initUSART1(void);
void USART1_IRQHandler(void);

void storeChar(uint8_t c, volatile uint8_t *str);
void sendString(char *str, ...);
uint8_t receiveChar(void);

void transmitWhatReceived(void);
uint8_t waitFor(uint8_t *str);


//function prototypes de giao tiep voi pc: usart3
void initUSART3(void);
void USART3_IRQHandler(void);
void sendStringToPC(char *str, ...);

#endif
