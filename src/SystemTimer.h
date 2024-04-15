#include "Config.h"

extern "C" void SysTick_Handler();

class SystemTimer
{
public:
    static SystemTimer *instance();
    void delay(int ms);
    friend void SysTick_Handler();

private:
    SystemTimer();
    void incTick();

    volatile uint32_t m_tickCount = 0;
};