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

int led_pin_at_position(int pos){
  switch (pos)
  {
    case 0: return GREEN_LED;
    case 1: return BLUE_LED;
    case 2: return YELLOW_LED;
    case 3: return RED_LED;
  
    default: return -1;
  }
}

#endif