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
                "li t0, 30\n" // set byte iterator to 3 bytes * 10 LEDs (30)
                "lb t2, (%[current_colors])\n" // load byte in t2
                "j startloop\n"
                "byteloop:\n"
                    "addi t0, t0, -1\n" // decrease byte iterator
                    "addi %[current_colors], %[current_colors], 1\n" // increase pointer to next elem
                    "startloop:\n"
                        "li t4, 8\n" // bit iterator counter
                        "li t1, 0x80\n" // load a binary mask to filter only relevant bit
                "bitloop:\n"
                    "sw %[high], 0(%[output])\n" // begin first high output
                    "and  t3, t1, t2\n" // apply mask and store mask result in t3
                    "beqz t3, writelow\n" // jump to low procedure if bit is 0
                 "writehigh:\n" // write high output
                    "beqz t0, endloop\n" // jumpt to end if byte iterator is 0
                    "srli t1, t1, 1\n" // right shift mask to check next bit
                    "lb t2, (%[current_colors])\n" // load byte in t2
                    "nop\n"
                    "nop\n"
                    "addi t4, t4, -1\n" // decrement bit iterator
                    "sw %[low], 0(%[output])\n" // write reg low 
                    "beqz t4, byteloop\n" // jump to loop new byte, if all bits are processed
                    "nop\n"
                    "j bitloop\n"
                 "writelow:\n" // write low output
                    "addi t4, t4, -1\n" // decrement bit iterator
                    "beqz t4, byteloop\n" // jump to loop new byte, if all bits are processed
                    "sw %[low], 0(%[output])\n" // decrement bit iterator
                    "nop\n"
                    "beqz t0, endloop\n" // jumpt to end if byte iterator is 0
                    "lb t2, (%[current_colors])\n" // load byte in t2
                    "srli t1, t1, 1\n" // right shift mask to check next bit
                    "nop\n"
                    "j bitloop\n"
                "endloop:\n"
                 "sw   %[high], 0(%[output])\n"
                 "sw   %[low],  0(%[output])\n" // set low for reset 
                 :
                 : [output] "r" (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL),
                   [high]   "r" (reg |  pin),
                   [low]    "r" (reg & ~pin),
                   [current_colors]   "r" (current_colors)
    );
}

void disable_led_stripe(void){
    uint_t pin = (1U << LED_STRIPE);
    uint_t reg = REG(GPIO_BASE + GPIO_OUTPUT_VAL);
    asm volatile(
        "li t0, 240\n" // loop through all 24 bits of the 10 leds (240 times) and set each color to black
        "low:\n"
        "beqz t0, end\n"
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
        "nop\n"
        "nop\n"    
        "addi t0, t0, -1\n"
        "j low\n"
        "end:\n"
        "nop\n"
        :
        : [output] "r" (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL),
        [high]   "r" (reg |  pin),
        [low]    "r" (reg & ~pin)
    );
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