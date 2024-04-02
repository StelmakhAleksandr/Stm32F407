#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"

#include "Terminal.h"

void cmsisLedoN()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= GPIO_MODER_MODER12_0;
    GPIOD->BSRR = GPIO_BSRR_BS_12;
}

int main()
{
    // Terminal::instance()->sendMessage("Hello \r\n");
    cmsisLedoN();
    while (true)
    {
        Terminal::instance()->sendMessage("Hello \r\n");
        GPIOD->ODR ^= GPIO_ODR_OD12;
        for (volatile int i = 0; i < 1000000; i++)
        {
        }
    }
    return 0;
}

void halLedOn()
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef led = {};
    led.Pin = GPIO_PIN_12;
    led.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOD, &led);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
}

void cmssRCC()
{
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY))
    {
    }
}