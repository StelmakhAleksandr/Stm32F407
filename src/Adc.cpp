#include "Adc.h"
#include "Terminal.h"

extern "C" void ADC_IRQHandler()
{
    if (ADC1->SR & ADC_SR_EOC)
    {
        Adc::instance()->setValue(ADC1->DR);
        ADC1->SR &= ~ADC_SR_EOC;
    }
}

Adc *Adc::instance()
{
    static Adc adc;
    return &adc;
}

Adc::Adc()
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER |= (0b11 << GPIO_MODER_MODE0_Pos);
    GPIOA->OTYPER |= GPIO_OTYPER_OT_0;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;

    NVIC_EnableIRQ(ADC_IRQn);

    ADC1->SMPR2 = ADC_SMPR2_SMP0_0;
    ADC1->SQR3 = 0;
    ADC1->CR1 |= ADC_CR1_EOCIE;
    ADC1->SR &= ~ADC_SR_EOC;
}

void Adc::start()
{
    ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_SWSTART;
}

uint32_t Adc::value()
{
    return m_value;
}

void Adc::setValue(uint32_t value)
{
    // if (std::abs(long(m_value - value)) < 10)
    //  {
    //      return;
    //  }
    m_value = value;
    Terminal::instance()->sendMessage("New ADC value = " + std::to_string(m_value) + "\r\n");
}