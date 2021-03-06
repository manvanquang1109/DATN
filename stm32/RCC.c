#include "RCC.h"

void enableClockForAltFunc(){
	GPIO_CLOCK_ENABLE_AF;
}

void enableClockForPort(GPIO_TypeDef *port){
	if (port == GPIOA)
		GPIO_CLOCK_ENABLE_PORTA;
	
	else if (port == GPIOB)
		GPIO_CLOCK_ENABLE_PORTB;
	
	else if (port == GPIOC)
		GPIO_CLOCK_ENABLE_PORTC;
	
	else if (port == GPIOD)
		GPIO_CLOCK_ENABLE_PORTD;
}

void enableClockForUSART1(void){
	CLOCK_ENABLE_USART1;
}

void enableClockForUSART3(void){
	CLOCK_ENABLE_USART3;
}

void enableClockForTimer2(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
}

void enableClockForTimer3(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
}

void enableClockForTimer4(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
}
