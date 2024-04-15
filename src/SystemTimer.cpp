#include "SystemTimer.h"

extern "C" void SysTick_Handler()
{
    SystemTimer::instance()->incTick();
}

SystemTimer *SystemTimer::instance()
{
    static SystemTimer timer;
    return &timer;
}

SystemTimer::SystemTimer()
{
    SysTick->LOAD = RCC_FREQUENCY / 1000 - 1;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SystemTimer::delay(int ms)
{
    int start = m_tickCount;
    while ((m_tickCount - start) < ms)
        ;
}

void SystemTimer::incTick()
{
    m_tickCount++;
}