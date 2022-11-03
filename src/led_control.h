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

void all_led_blink_short(){
    enabled_all_leds(TRUE);
    delay(T_SHORT);
    enabled_all_leds(FALSE);
    delay(T_SHORT);
}

void display_number_binary(int number){
    for(int i = 0; i < LED_COUNT; i++){
      int led_pin = led_pin_at_position(i);
      boolean bit_at_position = ( number >> ( LED_COUNT-i-1 ) ) & 0x01;
      enable_led(led_pin, bit_at_position);
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