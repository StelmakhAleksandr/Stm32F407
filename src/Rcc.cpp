#include "Rcc.h"

#include "stm32f407xx.h"

namespace
{
    constexpr int RCCMaxSpeedPLLN = 168;
    constexpr int RCCMaxSpeedPLLM = 4;
};

Rcc *Rcc::instance()
{
    static Rcc instance;
    return &instance;
}

void Rcc::enableMaxClockSpeed()
{
    runHSE();
    setupPLL();
    runPLL();
    setupBusPrescalers();
    setupFLASH();
    runPLLCLK();
}

void Rcc::runHSE()
{
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0)
    {
    };
}

void Rcc::runPLL()
{
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    };
}

void Rcc::runPLLCLK()
{
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0)
    {
    };
}

void Rcc::setupPLL()
{
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLQ);
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
    RCC->PLLCFGR |= (RCCMaxSpeedPLLN << RCC_PLLCFGR_PLLN_Pos);
    RCC->PLLCFGR |= (RCCMaxSpeedPLLM << RCC_PLLCFGR_PLLM_Pos);
    RCC->PLLCFGR |= (7 << RCC_PLLCFGR_PLLQ_Pos);
}

void Rcc::setupBusPrescalers()
{
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;
}

void Rcc::setupFLASH()
{
    FLASH->ACR |= FLASH_ACR_LATENCY_7WS;
}
