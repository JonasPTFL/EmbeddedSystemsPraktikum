#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void setup_led(int);
void setup_button(int);
void enable_led(int, boolean);
void enabled_all_leds(boolean);
boolean is_pressed(int);
void setup(void);
void loop();
void led_blink_initial();
void delay();


#endif
