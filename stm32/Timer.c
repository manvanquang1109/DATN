#include	"Timer.h"

//init Timer2 -> stepper X va Y
void initTimer2(void){

	TIM2->CR1 &= ~(TIM_CR1_CEN);	
	TIM2->PSC = 9 - 1;
	TIM2->ARR = 25600 - 1;
	TIM2->CR1 |= TIM_CR1_URS;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->EGR |= TIM_EGR_UG;
	
	NVIC_EnableIRQ(TIM2_IRQn);
}


//init Timer 3 -> PWM Channel 2 PA7 -> servo
void initTimer3(void){

	TIM3->CCER |= TIM_CCER_CC2E;	//enable capture, compare
	TIM3->CR1	|= TIM_CR1_ARPE;
	
	//pwm mode 1
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
	TIM3->CCMR1	&= ~TIM_CCMR1_OC2M_0;
	
	TIM3->CCMR1 |= TIM_CCMR1_OC2PE;	//enable preload
		
	//freq = 1kHz
	TIM3->PSC = 72 - 1;
	TIM3->ARR	= 1000 - 1;
	TIM3->CCR2 = 300 - 1;
	
	TIM3->EGR |= TIM_EGR_UG;
	TIM3->CR1	|= TIM_CR1_CEN;	//enable counter	
}


//for delayUs function
void initTimer4(void){

	TIM4->CR1 &= ~(TIM_CR1_CEN);	
	TIM4->PSC = 9 - 1;
	TIM4->ARR = 8 - 1;
	TIM4->CR1 |= TIM_CR1_URS;
	TIM4->DIER |= TIM_DIER_UIE;
	TIM4->EGR |= TIM_EGR_UG;
	
	NVIC_EnableIRQ(TIM4_IRQn);
}
