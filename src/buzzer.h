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

void play_frequency(uint32_t milliseconds, uint_t tone_frequency){
    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
    volatile uint64_t then = *now + (uint64_t)milliseconds*((uint64_t)RTC_FREQ / (uint64_t)MILLISECONDS_PER_SECOND);
    
    while ((*now) < then){
        REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << BUZZER);
        delay(((double)1000)/(((double)tone_frequency)*((double)2))); // *SIMULATOR_MILLIS_MULTIPLIER
        REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << BUZZER);
        delay(((double)1000)/(((double)tone_frequency)*((double)2))); // *SIMULATOR_MILLIS_MULTIPLIER
    }
}

void play_tone(uint_t tone_frequency, float tone_duration){
    play_frequency(tone_duration*500, tone_frequency);
}

#endif