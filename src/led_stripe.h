#ifndef LED_STRIPE_H
#define LED_STRIPE_H

#include "types.h"
#include "functions.h"

LED_STRIPE_H


void setup_led_stripe(void){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1U << LED_STRIPE);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1U << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= (1U << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << LED_STRIPE);
}

static void enable_led_stripe(uint_t *color_data, uint_t data_length)
{
    uint_t * current_colors = color_data;
    uint_t current_length = data_length;
    uint_t pin = (1U << LED_STRIPE);
    uint_t reg = REG(GPIO_BASE + GPIO_OUTPUT_VAL);


    asm volatile(
                "li t0, 10\n"
                "loadbyte:\n"
                    "lb t1, 0(%[current_colors])\n"
                "beginloop:\n"
                    "beqz t0, endloop\n"
                    "beqz t1, writelow\n"
                 "writehigh:\n" // write high output
                    "sw %[high], (%[output])\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "sw %[low], (%[output])\n"
                    "nop\n"
                    "nop\n"
                    "addi t0, t0, -1\n"
                    "j beginloop\n"
                 "writelow:\n" // write low output
                    "sw %[high], (%[output])\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "sw %[low], (%[output])\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "addi t0, t0, -1\n"
                    "j beginloop\n"
                // "endloop:\n"
                //  "end:\n"
                //  "sw   %[high], 0(%[output])\n"
                //  "sw   %[low],  0(%[output])\n" // reset
                 :
                 : [output] "r" (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL),
                   [high]   "r" (reg |  pin),
                   [low]    "r" (reg & ~pin),
                   [current_colors]   "r" (current_colors),
                   [current_length] "r" (current_length)
    );
}

void disable_led_stripe(void){
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << LED_STRIPE);
    delay(500);
}

void show_next_led_stripe_colors(void){
    static int color_index = 0;

    const color red = {0, 255, 0};
    const color green = {255, 0, 0};
    const color blue = {0, 0, 255};

    static color colors[] = { blue, red, green, blue, red, green, blue, red, green, blue };
    color *current_colors = colors + color_index;
    enable_led_stripe((uint_t *)current_colors, 10);
    
    color_index++;
    
    if (color_index > 2) {
        color_index = 0;
    }
}




#endif