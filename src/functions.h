#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void setup_led(int gpio_pin);
void setup_button(int gpio_pin);
boolean is_pressed(int button);
boolean is_only_pressed(int button);
int get_button_for_led(int led_pin);
int led_pin_at_position(int pos);
void delay(int milliseconds);
boolean delay_with_any_button_interrupt(int milliseconds);
boolean delay_with_specific_button_interrupt(int milliseconds, int button);
unsigned int nearly_random_number(void);

/* led functions */
void all_led_blink_short(void);
void enable_led(int led, boolean state);
void enabled_all_leds(boolean state);
void display_number_binary(int number);

/* game functions  */
boolean game_ready(void);
void game_demonstrate_start(void);
void game_demonstration_main(int step_count, int on_milliseconds, int led_pins []);
boolean game_imitation(int step_count, int waiting_time, const int led_pins[]);
void game_evaluate_round(int level, int* demonstration_led_count, int* demonstration_on_millis);
void game_transition(void);
void game_lost(int reached_level);
void game_end(void);

#endif
