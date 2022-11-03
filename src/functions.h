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
void all_led_blink_short();
void led_demonstration_start();
void led_demonstration_main();
boolean led_blink_ready();
void delay(int);
boolean delay_with_interrupt(int, int);
unsigned nearly_random_number();


#endif
