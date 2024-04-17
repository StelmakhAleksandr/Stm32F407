#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"

#include "Terminal.h"
#include "Rcc.h"
#include "SystemTimer.h"
#include "Adc.h"

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
    Adc::instance();

    int n = 0;
    while (true)
    {
        // auto adc = Adc::instance()->value();
        std::string msg = "YEAH " + std::to_string(n++) + "\r\n";
        Adc::instance()->start();
        Terminal::instance()->sendMessage(msg);
        SystemTimer::instance()->delay(1000);
    }
    return 0;
}