#ifndef GAME_H
#define GAME_H

#include "functions.h"
#include "types.h"
#include <time.h>

void all_led_blink_short(){
    enabled_all_leds(TRUE);
    delay(T_SHORT);
    enabled_all_leds(FALSE);
    delay(T_SHORT);
}

boolean led_blink_ready(){
    for (int i = 0; i < LED_COUNT; i++){
        enabled_all_leds(FALSE);
        enable_led(led_pin_at_position(i), TRUE);
        boolean interrupted = delay_with_interrupt(T_SHORT, GREEN_BUTTON);
        if (interrupted){
            return TRUE;
        }
        
    }
    return FALSE;
}

void led_demonstration_start(){
    enabled_all_leds(TRUE);
    for (int i = LED_COUNT-1; i >= 0; i--){
        delay(T_SHORT);
        enable_led(led_pin_at_position(i), FALSE);
    }
    delay(T_SHORT);
}

void led_demonstration_main(int step_count, int on_milliseconds, int * led_pins []){
    enabled_all_leds(FALSE);
    for (int i = 0; i < step_count; i++){
        int random_led_pin = led_pin_at_position(nearly_random_number() % 5);
        (*led_pins)[i] = random_led_pin;
        enable_led(random_led_pin, TRUE);
        delay(on_milliseconds);
        enable_led(random_led_pin, FALSE);
        delay(T_SHORT);
    }
}


void led_blink_end(){
    for (int i = 1; i <= 4; i++){
        enabled_all_leds(TRUE);

        if (i == 1 || i == 4) delay(T_SHORT);
        else delay(T_LONG);

        enabled_all_leds(FALSE);
        delay(T_SHORT);
    }

    delay(3000);
}

#endif
