#ifndef GAME_H
#define GAME_H

#include "functions.h"
#include "types.h"

void led_blink_initial(){
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

#endif
