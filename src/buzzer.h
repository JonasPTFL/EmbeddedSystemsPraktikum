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

void play_frequency(uint_t tone_frequency){
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) ^= (1U << BUZZER);
    delay(1000/(tone_frequency*2) * SIMULATOR_MILLIS_MULTIPLIER);
    // TODO rundungsfehler in delay ode rbei der berechnung hier?!
}

void play_tone(uint_t tone_frequency, float tone_duration){
    for (double i = 0; i < tone_duration; i++)
    {
        for (uint_t j = 0; j < tone_frequency*2; j++)
        {   
            play_frequency(tone_frequency);
        }
    }
}

#endif