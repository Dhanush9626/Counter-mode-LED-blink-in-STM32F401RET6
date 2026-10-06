#include "stm32f401xe.h"
#include "stdint.h"

void TIM2_COUNTER(void);
void TIM2_COUNT_INIT(void);

int main(void)
{
    RCC->AHB1ENR |= (1U<<0);
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    GPIOA->MODER &= ~((3U<<(2*5)) | (3U<<(2*6)));
    GPIOA->MODER |=  (1U<<(2*5)) | (1U<<(2*6));

    GPIOA->MODER &= ~(3U<<(2*1));
    GPIOA->MODER |=  (2U<<(2*1));
    GPIOA->AFR[0] &= ~(0xF<<4);
    GPIOA->AFR[0] |=  (0x1<<4);

    TIM2_COUNT_INIT();

    while(1)
    {

        GPIOA->ODR |= (1U<<5) | (1U<<6);
        TIM2_COUNTER();

        GPIOA->ODR &= ~((1U<<5) | (1U<<6));
        TIM2_COUNTER();
    }
}

void TIM2_COUNT_INIT(void)
{
    TIM2->ARR = 5;
    TIM2->CNT = 0;

    TIM2->SMCR &= ~(TIM_SMCR_SMS);
    TIM2->SMCR |= (0x7<<0);
    TIM2->SMCR |= (0x3<<5);

    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_COUNTER(void)
{
    while(!(TIM2->SR & TIM_SR_UIF));
    TIM2->SR &= ~TIM_SR_UIF;
}
