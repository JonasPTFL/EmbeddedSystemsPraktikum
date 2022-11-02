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
int led_pin_at_position(int);
void led_blink_initial();
boolean led_blink_ready();
void delay(int);
boolean delay_with_interrupt(int, int);


#endif
