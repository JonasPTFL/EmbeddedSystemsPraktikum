#ifndef LED_STRIPE_H
#define LED_STRIPE_H

#include "types.h"
#include "functions.h"

LED_STRIPE_H


void setup_led_stripe(){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << LED_STRIPE);
}

void enabled_led_stripe(){
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << LED_STRIPE);
    delay(2);
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << LED_STRIPE);
}


#endif