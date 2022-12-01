#ifndef LED_CONTROL_H
#define LED_CONTROL_H

LED_CONTROL_H

#include "functions.h"
#include "types.h"


/* sets up the given led pin  */
void setup_led(uint32_t gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << gpio_pin);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << gpio_pin);
}

/* enables all leds with the given state  */
void enabled_all_leds(boolean state){
    enable_led(GREEN_LED, state);
    enable_led(BLUE_LED, state);
    enable_led(YELLOW_LED, state);
    enable_led(RED_LED, state);
}

/* enables a pecific led with the given state  */
void enable_led(uint32_t led, boolean state){
    if (state == TRUE){
		  REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << led);
    } else{
	    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << led);
    }
}

/* lets the leds blink up for the time period T_SHORT  */
void all_led_blink_short(void){
    enabled_all_leds(TRUE);
    delay(T_SHORT);
    enabled_all_leds(FALSE);
    delay(T_SHORT);
}

/* displays the given number binary with the 4 leds  */
void display_number_binary(uint_t number){
    for(uint_t i = 0; i < (uint_t)LED_COUNT; i++){
      int led_pin = led_pin_at_position(i);
      uint_t bit_at_position = (uint_t)( (uint_t) number >> (uint_t) ( (uint_t)LED_COUNT-i-(uint_t)1 ) ) & (uint_t)0x01;
      boolean led_enabled;
      if (bit_at_position == (uint_t)1){
        led_enabled = TRUE;
      } else {
        led_enabled = FALSE;
      }
      
      enable_led(led_pin, led_enabled);
    }
}

/* returns the led pin on the given position  */
uint32_t led_pin_at_position(uint_t pos){
  uint32_t led_pin;
  switch (pos)
  {
    case 0: led_pin = GREEN_LED; break;
    case 1: led_pin = BLUE_LED; break;
    case 2: led_pin = YELLOW_LED; break;
    case 3: led_pin = RED_LED; break;
  
    default: led_pin = -1;
  }
  return led_pin;
}

#endif