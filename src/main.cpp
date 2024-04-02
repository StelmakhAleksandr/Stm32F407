#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"

#include "Terminal.h"
#include "Rcc.h"

void cmsisLedoN()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= GPIO_MODER_MODER12_0;
    GPIOD->BSRR = GPIO_BSRR_BS_12;
}

int main()
{
    Rcc::instance()->enableMaxClockSpeed();
    cmsisLedoN();

    while (true)
    {
        Terminal::instance()->sendMessage("YEAH \r\n");
        GPIOD->ODR ^= GPIO_ODR_OD12;
        for (volatile int i = 0; i < 1000000; i++)
        {
        }
    }
    return 0;
}