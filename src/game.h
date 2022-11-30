#ifndef GAME_H
#define GAME_H

GAME_H

#include "functions.h"
#include "types.h"


/* ready game step  */
boolean game_ready(void){
    boolean result = FALSE;
    for (int i = 0; i < LED_COUNT; i++){
        enabled_all_leds(FALSE);
        enable_led(led_pin_at_position(i), TRUE);
        boolean interrupted = delay_with_specific_button_interrupt(T_SHORT, GREEN_BUTTON);
        if (interrupted && is_pressed(GREEN_BUTTON)){
            enabled_all_leds(FALSE);
            result = TRUE;
            break;
        }
        
    }
    return result;
}

/* demonstration game step  */
void game_demonstrate_start(void){
    enabled_all_leds(TRUE);
    for (int i = (int)LED_COUNT-1; i >= 0; i--){
        delay(T_SHORT);
        enable_led(led_pin_at_position(i), FALSE);
    }
    delay(T_SHORT);
}

/* demonstration game step  */
void game_demonstration_main(uint_t step_count, uint32_t on_milliseconds, uint32_t led_pins []){
    enabled_all_leds(FALSE);
    for (int i = 0; i < step_count; i++){
        uint32_t random_led_pin = led_pin_at_position((int)((int)nearly_random_number() % 5));
        led_pins[i] = random_led_pin;
        enable_led(random_led_pin, TRUE);
        delay(on_milliseconds);
        enable_led(random_led_pin, FALSE);
        delay(T_SHORT);
    }
}

/* imitation game step  */
boolean game_imitation(uint_t step_count, uint32_t waiting_time, const uint32_t led_pins[]){
    boolean result = TRUE;
    for (int i = 0; i < step_count; i++){
        boolean button_pressed_in_time = delay_with_any_button_interrupt(waiting_time);
        uint32_t current_led_pin = led_pins[i];
        
        if (button_pressed_in_time && is_only_pressed(get_button_for_led(current_led_pin))){
            enable_led(current_led_pin, TRUE);
            delay(T_SHORT);
            enable_led(current_led_pin, FALSE);
        } else {
            result = FALSE;
            break;
        }
        
    }
    return result;
}

/* game lost step  */
void game_lost(uint_t reached_level){
    for (int i = 0; i < 5; i++){
        enable_led(RED_LED, TRUE);
        delay(T_SHORT);
        
        enable_led(RED_LED, FALSE);
        delay(T_SHORT);
    }

    display_number_binary(reached_level);
    delay(T_VERY_LONG); 
}

/* transition game step  */
void game_transition(void){
    for (int i = 0; i < 5; i++){
        display_number_binary(BINNARY_TRANSITION_NUMBER_1); 
        delay(T_SHORT);

        display_number_binary(BINNARY_TRANSITION_NUMBER_2);
        delay(T_SHORT);
    }
    enabled_all_leds(FALSE);
}

/* evaluation game step  */
void game_evaluate_round(uint_t level, uint_t* demonstration_led_count, uint32_t* demonstration_on_millis){
    if ((level <= 4) || ( (level >= 9) && (level <= 12) )){
        (*demonstration_led_count)++;
    } else {
        if((level <= 8) ||  ((level >= 13) && (level <= 16) )){
            *demonstration_on_millis -= (*demonstration_on_millis) * DEMONSTRATION_ON_MILLIS_PRECENTAGE_INCREASE;
        }
    }
}

/* ending game step  */
void game_end(void){
    for (int i = 1; i <= 4; i++){
        enabled_all_leds(TRUE);

        if ((i == 1) || (i == 4)) delay(T_SHORT);
        else delay(T_LONG);

        enabled_all_leds(FALSE);
        delay(T_SHORT);
    }
}

#endif
