#ifndef FUNCTIONS_H
#define FUNCTIONS_H

FUNCTIONS_H

#include "types.h"

static void setup_led(uint32_t gpio_pin);
static void setup_button(uint32_t gpio_pin);
static boolean is_pressed(uint32_t button);
static boolean is_only_pressed(uint32_t button);
static int get_button_for_led(uint32_t led_pin);
static uint32_t led_pin_at_position(uint_t pos);
static void delay(uint32_t milliseconds);
static boolean delay_with_any_button_interrupt(uint32_t milliseconds);
static boolean delay_with_specific_button_interrupt(uint32_t milliseconds, uint32_t button);
static unsigned int nearly_random_number(void);

/* led functions */
static void all_led_blink_short(void);
static void enable_led(uint32_t led, boolean state);
static void enabled_all_leds(boolean state);
static void display_number_binary(uint_t number);

/* game functions  */
static boolean game_ready(void);
static void game_demonstrate_start(void);
static void game_demonstration_main(uint_t step_count, uint32_t on_milliseconds, uint32_t led_pins []);
static boolean game_imitation(uint_t step_count, uint32_t waiting_time, const uint32_t led_pins[]);
static void game_evaluate_round(uint_t level, uint_t* demonstration_led_count, uint32_t* demonstration_on_millis);
static void game_transition(void);
static void game_lost(uint_t reached_level);
static void game_end(void);

/* main functions  */
static void setup(void);
static void reset_game(void);
static void loop(void);

#endif
