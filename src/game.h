#ifndef GAME_H
#define GAME_H

#include "functions.h"
#include "types.h"

void led_blink_initial(){
    enabled_all_leds(TRUE);
    delay();
    enabled_all_leds(FALSE);
    delay();
}

#endif
