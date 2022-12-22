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
                "li t0, 30\n" // byte iterator counter
                "li t2, 0\n" // byte iterator counter
                "byteloop:\n"
                    "addi t0, t0, -1\n"
                    "addi %[current_colors], %[current_colors], 1\n" // increase pointer to next elem // TODO low high proceduren mit zeiten anpassen, sonst funktionsfähig?!
                    "li t4, 8\n" // bit iterator counter
                    "li t1, 0x80\n" // load a binary mask to filter only relevant bit
                "bitloop:\n"
                    "and  t3, t1, t2\n" // apply mask and store mask result in t3
                    "beqz t4, byteloop\n"
                    "sw %[high], (%[output])\n" // begin first high output
                    "beqz t3, writelow\n" // jump to low procedure if bit is 0
                 "writehigh:\n" // write high output
                    "beqz t0, endloop\n"
                    "srli t1, t1, 1\n" // right shift mask to check next bit
                    "lb t2, (%[current_colors])\n" // load byte in t2
                    "nop\n"
                    "nop\n"
                    "nop\n"
                    //"nop\n"
                    //"nop\n"
                    "addi t4, t4, -1\n"
                    "sw %[low], (%[output])\n"
                    "j bitloop\n"
                 "writelow:\n" // write low output
                    "beqz t0, endloop\n"
                    "addi t4, t4, -1\n"
                    "sw %[low], (%[output])\n"
                    "nop\n"
                    "nop\n"
                    "lb t2, (%[current_colors])\n" // load byte in t2
                    "srli t1, t1, 1\n" // right shift mask to check next bit
                    "nop\n"
                    "j bitloop\n"
                "endloop:\n"
                 "sw   %[high], 0(%[output])\n"
                 "sw   %[low],  0(%[output])\n" // reset
                 :
                 : [output] "r" (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL),
                   [high]   "r" (reg |  pin),
                   [low]    "r" (reg & ~pin),
                   [current_colors]   "r" (current_colors)
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
    
    //color_index++;
    
    if (color_index > 2) {
        color_index = 0;
    }
}




#endif