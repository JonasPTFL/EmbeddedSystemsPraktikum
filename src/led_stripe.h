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
                 "sw   %[low],  0(%[output])\n" // reset
             "byte_loop:\n"
                 "li   t1, 0x80\n"              // t1: bit mask
             "bit_loop:\n"
                 "lb   t0, 0(%[current_colors])\n"        // t0: current byte
                                                // yes we load the byte again for every bit even though this is not necessary
                 "sw   %[high], 0(%[output])\n"
                 "and  t2, t1, t0\n"
                 "srli t1, t1, 1\n"
                 "beqz t2, check_next\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
             "check_next:\n"                    // check if next byte needs to be loaded
                 "beqz t1, next\n"
                 "j    low\n"
             "next:\n"                             //preload next byte
                 "addi %[current_colors],   %[current_colors],    1\n"
                 "addi %[current_length], %[current_length], -1\n"
             "low:\n"
                 "sw   %[low],  0(%[output])\n"
                 "bnez t2, iter_end\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
                 "nop\n"
             "iter_end:\n"
                 "bnez t1, bit_loop\n"
                 "bnez %[current_length], byte_loop\n"
             "end:"
                 "sw   %[high], 0(%[output])\n"
                 "sw   %[low],  0(%[output])\n" // reset
                 :
                 : [output] "r" (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL),
                   [high]   "r" (reg |  pin),
                   [low]    "r" (reg & ~pin),
                   [current_colors]   "r" (current_colors),
                   [current_length] "r" (current_length)
    );
}

void show_next_led_stripe_colors(void){
    static int color_index = 0;

    const color red = {0, 255, 0};
    const color green = {255, 0, 0};
    const color blue = {0, 0, 255};

    static color colors[] = { red, green, blue, red, green, blue, red, green, blue, red };
    color *current_colors = colors + color_index;
    enable_led_stripe((uint_t *)current_colors, 10);
    
    color_index++;
    
    if (color_index > 2) {
        color_index = 0;
    }
}




#endif