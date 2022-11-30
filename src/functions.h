#ifndef FUNCTIONS_H
#define FUNCTIONS_H

FUNCTIONS_H

#include "types.h"

static void setup_led(int gpio_pin);
static void setup_button(int gpio_pin);
static boolean is_pressed(int button);
static boolean is_only_pressed(int button);
static int get_button_for_led(int led_pin);
static int led_pin_at_position(int pos);
static void delay(uint32_t milliseconds);
static boolean delay_with_any_button_interrupt(uint32_t milliseconds);
static boolean delay_with_specific_button_interrupt(uint32_t milliseconds, int button);
static unsigned int nearly_random_number(void);

/* led functions */
static void all_led_blink_short(void);
static void enable_led(int led, boolean state);
static void enabled_all_leds(boolean state);
static void display_number_binary(uint_t number);

/* game functions  */
static boolean game_ready(void);
static void game_demonstrate_start(void);
static void game_demonstration_main(int step_count, int on_milliseconds, int led_pins []);
static boolean game_imitation(int step_count, int waiting_time, const int led_pins[]);
static void game_evaluate_round(int level, int* demonstration_led_count, int* demonstration_on_millis);
static void game_transition(void);
static void game_lost(int reached_level);
static void game_end(void);

/* main functions  */
static void setup(void);
static void reset_game(void);
static void loop(void);

#endif
