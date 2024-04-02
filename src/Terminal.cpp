#include "Terminal.h"

#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"

Terminal *Terminal::instance()
{
    static Terminal terminal;
    return &terminal;
}

Terminal::Terminal()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOA->MODER |= GPIO_MODER_MODE2_1;
    GPIOA->AFR[0] |= (0b0111 << GPIO_AFRL_AFSEL2_Pos);

    USART2->BRR = 16000000 / 9600;
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_UE);
}

void Terminal::sendMessage(const std::string &msg)
{
    for (auto &symbol : msg)
    {
        while ((USART2->SR & USART_SR_TC) == 0)
        {
        }
        USART2->DR = symbol;
    }
}
