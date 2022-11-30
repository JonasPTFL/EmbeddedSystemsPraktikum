#ifndef TYPES_H
#define TYPES_H

TYPES_H

typedef unsigned long uint32_t;
typedef	unsigned int uint_t;

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38
#define GPIO_INPUT_VAL 0x0
#define GPIO_PUE 0x10

#define GREEN_LED 18
#define BLUE_LED 21
#define YELLOW_LED 0
#define RED_LED 3

#define LED_COUNT 4
#define LEVEL_COUNT 16

#define BINNARY_TRANSITION_NUMBER_1 9
#define BINNARY_TRANSITION_NUMBER_2 6

#define GREEN_BUTTON 19
#define BLUE_BUTTON 20
#define YELLOW_BUTTON 1
#define RED_BUTTON 2

#define T_SHORT 500
#define T_LONG 1000
#define T_VERY_LONG 2000
#define MILLISECONDS_PER_SECOND 1000

#define INITIAL_DEMONSTRATION_LED_COUNT 3
#define INITIAL_LEVEL 1
#define INITIAL_RAND_SEED 0

#define MAX_DEMONSTRATION_LED_COUNT 10
#define DEMONSTRATION_ON_MILLIS_PRECENTAGE_INCREASE 0.1


typedef enum {
    FALSE, TRUE
} boolean;

typedef enum {
    INITIAL, READY, DEMONSTRATION, IMITATION, LOST, TRANSITION, END
} game_state;

#endif
