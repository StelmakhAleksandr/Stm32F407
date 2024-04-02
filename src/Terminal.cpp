#include "Terminal.h"

#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"

#include "Config.h"

Terminal *Terminal::instance()
{
    static Terminal terminal;
    return &terminal;
}

Terminal::Terminal()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    GPIOD->MODER |= GPIO_MODER_MODE8_1;
    GPIOD->AFR[1] |= (0b0111 << GPIO_AFRH_AFSEL8_Pos);

    USART3->BRR = RCC_FREQUENCY / RCC_APB1DIV / TERMINAL_BAUD;
    USART3->CR1 |= (USART_CR1_TE | USART_CR1_UE);
}

void Terminal::sendMessage(const std::string &msg)
{
    for (auto &symbol : msg)
    {
        while ((USART3->SR & USART_SR_TC) == 0)
        {
        }
        USART3->DR = symbol;
    }
}
