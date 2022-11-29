#ifndef LED_CONTROL_H
#define LED_CONTROL_H

LED_CONTROL_H

#include "functions.h"
#include "types.h"


void setup_led(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << (uint32_t) gpio_pin);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << (uint32_t) gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << (uint32_t) gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << (uint32_t) gpio_pin);
}

void enabled_all_leds(boolean state){
    enable_led(GREEN_LED, state);
    enable_led(BLUE_LED, state);
    enable_led(YELLOW_LED, state);
    enable_led(RED_LED, state);
}

void enable_led(int led, boolean state){
    if (state == TRUE){
		  REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << (uint32_t) led);
    } else{
	    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~((uint32_t)1 << (uint32_t) led);
    }
}

void all_led_blink_short(void){
    enabled_all_leds(TRUE);
    delay(T_SHORT);
    enabled_all_leds(FALSE);
    delay(T_SHORT);
}

void display_number_binary(unsigned_int number){
    for(unsigned_int i = 0; i < (unsigned_int)LED_COUNT; i++){
      int led_pin = led_pin_at_position(i);
      unsigned_int bit_at_position = (unsigned_int)( (unsigned_int) number >> (unsigned_int) ( (unsigned_int)LED_COUNT-i-(unsigned_int)1 ) ) & (unsigned_int)0x01;
      boolean led_enabled;
      if (bit_at_position == (unsigned_int)1){
        led_enabled = TRUE;
      } else {
        led_enabled = FALSE;
      }
      
      enable_led(led_pin, led_enabled);
    }
}

int led_pin_at_position(int pos){
  int led_pin;
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