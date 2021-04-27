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
#define BUFF_LEN 240
#define WIFI_SSID	"MVMinh"
#define	WIFI_PASS	"15061980"

extern volatile uint8_t rx_char;
extern volatile uint8_t rx_string[BUFF_LEN];
extern volatile uint16_t idx;

extern volatile uint8_t wifi_info[BUFF_LEN];

void initUSART1(void);
void USART1_IRQHandler(void);
void storeChar(uint8_t c, volatile uint8_t *str);
void printMsg(char *msg, ...);
void sendString(char *str, ...);
uint8_t receiveChar(void);

void transmitWhatReceived(void);
uint8_t waitFor(uint8_t *str);

#endif
