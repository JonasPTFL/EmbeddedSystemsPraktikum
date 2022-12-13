#ifndef FUNCTIONS_H
#define FUNCTIONS_H

FUNCTIONS_H

#include "types.h"

/* main functions  */
static void setup(void);
static void loop(void);
static void delay(uint32_t milliseconds);

/* buzzer */
static void setup_buzzer(void);
static void play_tone(uint_t tone_frequency, float tone_duration);
static void play_frequency(uint_t tone_frequency);
static void delay_tone_frequency(uint32_t f_milliseconds);

/* led stripe */
static void setup_led_stripe(void);
static void enable_led_stripe(void);

#endif
