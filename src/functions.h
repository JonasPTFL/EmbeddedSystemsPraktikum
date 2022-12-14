#ifndef FUNCTIONS_H
#define FUNCTIONS_H

FUNCTIONS_H

#include "types.h"

/* main functions  */
static void setup(void);
static void loop(void);
static void delay(double milliseconds);

/* buzzer */
static void setup_buzzer(void);
static void play_tone(uint_t tone_frequency, float tone_duration);
void play_frequency(uint32_t milliseconds, uint_t tone_frequency);

/* led stripe */
static void setup_led_stripe(void);
static void enable_led_stripe(void);

#endif
