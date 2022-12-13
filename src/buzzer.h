#ifndef BUZZER_H
#define BUZZER_H

#include "types.h"

BUZZER_H


void setup_buzzer(){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << BUZZER);
}

void delay_tone_frequency(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 1000.0 * SIMULATOR_MILLIS_MULTIPLIER);
    while (*now < then);
}

void play_frequency(uint_t tone_frequency){
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << BUZZER);
    delay_tone_frequency(1000/(tone_frequency*2));
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << BUZZER);
    delay_tone_frequency(1000/(tone_frequency*2));
}

void play_tone(uint_t tone_frequency, float tone_duration){
    for (double i = 0; i < tone_duration; i++)
    {
        for (uint_t j = 0; j < 550; j++)
        {   
            play_frequency(550);
        }
    }
}

#endif