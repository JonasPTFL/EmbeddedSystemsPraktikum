#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

void setup_led(int);
void setup_button(int);
boolean is_pressed(int);
boolean is_only_pressed(int);
int get_button_for_led(int);
int led_pin_at_position(int);
void delay(int);
boolean delay_with_any_button_interrupt(int);
boolean delay_with_specific_button_interrupt(int, int);
unsigned nearly_random_number();

/* led functions */
void all_led_blink_short();
void enable_led(int, boolean);
void enabled_all_leds(boolean);
void display_number_binary(int);

/* game functions  */
boolean game_ready();
void game_demonstrate_start();
void game_demonstration_main(int, int, int[]);
boolean game_imitation(int, int, int[]);
void game_evaluate_round(int, int*, int*);
void game_transition();
void game_lost(int);
void game_end();

#endif
