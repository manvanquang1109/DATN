#include "UART.h"


//baud rate = 115200 for 72MHz on APB1 bus
//usart1 TC & RXNE interrupt
void initUSART1(){
	USART1->BRR = 0x0271;
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;	//transmitter & receiver enable
	USART1->CR1	|= USART_CR1_UE;	//enable usart1
	
	USART1->CR1 |= USART_CR1_TCIE | USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART1_IRQn);
	
//	//xoa cac co
//	USART1->SR &= ~USART_SR_RXNE;
//	USART1->SR &= ~USART_SR_TC;
//	USART1->SR &= ~USART_SR_TXE;
}

void printMsg(char *msg, ...){
	char buff[80];
	
	#ifdef DEBUG_UART
	
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);
	
	for (uint8_t i = 0; i < strlen(buff); i++){
		volatile unsigned char temp = buff[i];
		USART1->DR = temp;
//		for (volatile uint16_t j = 0; j < 550; j++);
		delayUs(50);
	}
	
	#endif
}

void transmitWhatReceived(void){
	char temp;
	while(1){
		if (USART1->SR & USART_SR_RXNE){
			temp = (uint8_t) USART1->DR;
			USART1->DR = temp + 1;
			while ( !(USART1->SR & USART_SR_TC) );
		}
	}
}
