#include "UART.h"

//baud rate = 115200 for 72MHz on APB1 bus
//usart1 TC & RXNE interrupt
void initUSART1(){
	idx = 0;
	
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

void USART1_IRQHandler(void){
	
	//togglePin(GPIOC, 13);
	
	if (USART1->SR & USART_SR_RXNE){	//rx flag
		rx_char = (uint8_t)USART1->DR;
		//writePin(GPIOC, 13, 1);
		
//		rx_string[idx] = rx_char;
//		idx++;
		storeChar(rx_char, rx_string);
		
		USART1->SR &= ~USART_SR_RXNE;
	}
	
	else if (USART1->SR & USART_SR_TC){	//tx flag
		//togglePin(GPIOC, 13);
		USART1->SR &= ~USART_SR_TC;
	}
}

void storeChar(uint8_t c, volatile uint8_t *str){
	str[idx] = c;
	idx++;
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

void sendString(char *str, ...){
	
	char buff[80];
	idx = 0;
	for (volatile int i = 0; i < BUFF_LEN; i++){
		rx_string[i] = 0;
	}
	
	va_list args;
	va_start(args, str);
	vsprintf(buff, str, args);
	
	for (uint8_t i = 0; i < strlen(buff); i++){
		volatile unsigned char temp = buff[i];
		USART1->DR = temp;
		delayUs(50);
	}
	
	return;
}

uint8_t receiveChar(void){
	uint8_t c = 'A';
	
	USART1->CR1	|= USART_CR1_UE;	//enable usart1
	
	c = (uint8_t)USART1->DR;
	
	USART1->CR1	&= ~USART_CR1_UE;	//disable usart1
	
	return c;
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

uint8_t waitFor(uint8_t *str){
	uint8_t* ret = strstr(rx_string, str);
	
	if (ret){
		return 1;
	}
	
	return 0;
}
