#ifndef LED_STRIPE_H
#define LED_STRIPE_H

#include "types.h"
#include "functions.h"

LED_STRIPE_H

color_t colors[] = { RED, GREEN, BLUE, RED, GREEN, BLUE, RED, GREEN, BLUE, RED, GREEN, BLUE };


void setup_led_stripe(){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << LED_STRIPE);
}

void enabled_led_stripe(){
    color_t *current_colors = colors;
    ws2812b_write((1 << LED_STRIPE), (const uint8_t *)current_colors, 10 * sizeof(color_t));
}

void ws2812b_write(uint32_t pin_mask, const uint8_t *data, uint8_t length)
{
    uint32_t state = REG(GPIO_BASE + GPIO_OUTPUT_VAL);

    // HERE BE DRAGONS
    asm volatile(
                 "sw   %[low],  0(%[output])\n" // reset
             "byte_loop:\n"
                 "li   t1, 0x80\n"              // t1: bit mask
             "bit_loop:\n"
                 "lb   t0, 0(%[data])\n"        // t0: current byte
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
                 "addi %[data],   %[data],    1\n"
                 "addi %[length], %[length], -1\n"
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
                 "bnez %[length], byte_loop\n"
             "end:"
                 "sw   %[high], 0(%[output])\n"
                 "sw   %[low],  0(%[output])\n" // reset
                 :
                 : [output] "r" (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL),
                   [high]   "r" (state |  pin_mask),
                   [low]    "r" (state & ~pin_mask),
                   [data]   "r" (data),
                   [length] "r" (length)
    );
}



#endif