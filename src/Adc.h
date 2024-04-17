#pragma once

#include "stm32f407xx.h"
#include "CircularBuffer.h"

extern "C" void ADC_IRQHandler();

class Adc
{
    friend void ADC_IRQHandler();

public:
    uint32_t value();
    static Adc *instance();

private:
    Adc();
    void setValue(uint32_t value);
    CircularBuffer<uint32_t, 1024> m_adcBuffer;
    uint32_t m_value = 0;
};