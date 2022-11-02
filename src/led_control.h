#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "functions.h"
#include "types.h"


void setup_led(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << gpio_pin);
}

void enabled_all_leds(boolean state){
    enable_led(GREEN_LED, state);
    enable_led(BLUE_LED, state);
    enable_led(YELLOW_LED, state);
    enable_led(RED_LED, state);
}

void enable_led(int led, boolean state){
    if (state){
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << led);
    } else{
	    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << led);
    }
}

#endif