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

static void enable_led_stripe(uint_t *color_data)
{
    uint_t * current_colors = color_data;
    uint_t pin = (1U << LED_STRIPE);
    uint_t reg = REG(GPIO_BASE + GPIO_OUTPUT_VAL);


    asm volatile(
                "li t0, 10\n" // iterator counter
                "byteloop:\n"
                    "beqz t0, endloop\n"
                    "li t1, 0x80\n" // load a binary mask to filter only relevant bit
                    "lb t2, (%[current_colors])\n" // load byte in t2
                "bitloop:\n"
                    "and  t3, t1, t2\n" // apply mask and store mask result in t3
                    "srli t1, t1, 1\n" // right shift mask to check next bit
                    "sw %[high], (%[output])\n" // begin first high output
                    "beqz t2, writelow\n" // jump to low procedure if bit is 0
                 "writehigh:\n" // write high output
                    "addi %[current_colors], %[current_colors], 1\n" // increase pointer to next elem // TODO low high proceduren mit zeiten anpassen, sonst funktionsfähig?!
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    "sw %[low], (%[output])\n"
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
                "endloop:\n"
                 "end:\n"
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
    enable_led_stripe((uint_t *)current_colors);
    
    color_index++;
    
    if (color_index > 2) {
        color_index = 0;
    }
}




#endif