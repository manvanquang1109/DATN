#include "UART.h"

void initUSART1(void){
	
	idx = 0;
	
	//baud rate = 115200 for 72MHz on APB2 bus
	//usart1 TC & RXNE interrupt
	//BRR = 72000000 / (16 * 115200)
	USART1->BRR = 0x0271;
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;	//transmitter & receiver enable
	USART1->CR1	|= USART_CR1_UE;	//enable usart1
	
	USART1->CR1 |= USART_CR1_TCIE | USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void){
	
	//togglePin(GPIOC, 13);
	
	if (USART1->SR & USART_SR_RXNE){	//rx flag
		rx_char = (uint8_t)USART1->DR;
		storeChar(rx_char, rx_string);
		
		USART1->SR &= ~USART_SR_RXNE;
	}
	
	else if (USART1->SR & USART_SR_TC){	//tx flag
//		togglePin(GPIOC, 13);

		USART1->SR &= ~USART_SR_TC;
	}
}

void storeChar(uint8_t c, volatile uint8_t *str){
	str[idx] = c;
	idx++;
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




void initUSART3(void){
	
	//baud rate = 115200 for 36MHz on APB1 bus
	//usart1 TC & RXNE interrupt
	USART3->BRR = 0x0138;
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;	//transmitter & receiver enable
	USART3->CR1	|= USART_CR1_UE;	//enable usart3
	
	USART3->CR1 |= USART_CR1_TCIE | USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART3_IRQn);
}

void USART3_IRQHandler(void){
	
	if (USART3->SR & USART_SR_RXNE){	//rx flag
		
		usart3_char = (uint8_t)USART3->DR;		
//		USART3->DR = usart3_char;
		
		USART3->SR &= ~USART_SR_RXNE;
	}
	
	else if (USART3->SR & USART_SR_TC){	//tx flag
		USART3->SR &= ~USART_SR_TC;
	}
}

void sendStringToPC(char *str, ...){
	
	char buff[80];
	
	va_list args;
	va_start(args, str);
	vsprintf(buff, str, args);
	
	for (uint8_t i = 0; i < strlen(buff); i++){
		volatile unsigned char temp = buff[i];
		USART3->DR = temp;
		delayUs(50);
	}
	
	return;
}
