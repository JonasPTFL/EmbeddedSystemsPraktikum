#ifndef TYPES_H
#define TYPES_H

/* 
* Neccessary to avoid misra warning 2.5: "A project should not contain unused macro declarations"
* Since i need to declare a variable to not include the same header file multiple times, a simple 'usage' of the
* macro like shown below will avoid the warning 2.5 to show. This is used in other header on the same way.
*/
TYPES_H

/* defining data general int data types */
typedef	unsigned int uint_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

/* REG macro from the embedded systes workspace example used to change system value and read/write to gpio pins */
#define REG(P) (*(volatile uint32_t *) (P))

/* gpio pins */
#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38
#define GPIO_INPUT_VAL 0x0
#define GPIO_PUE 0x10

/* time measurement */
#define CLINT_CTRL_ADDR 0x02000000UL
#define CLINT_MTIME 0xBFF8
#define RTC_FREQ 32768

/* led gpio pins */
#define GREEN_LED 18U
#define BLUE_LED 21U
#define YELLOW_LED 0U
#define RED_LED 3U

/* numbers diesplayed in the transition phase as binary number on leds (this creates the led patter) */
#define BINNARY_TRANSITION_NUMBER_1 9
#define BINNARY_TRANSITION_NUMBER_2 6

/* button gpio pins */
#define GREEN_BUTTON 19U
#define BLUE_BUTTON 20U
#define YELLOW_BUTTON 1U
#define RED_BUTTON 2U

/* time length definitions */
#define T_SHORT (uint32_t)700
#define T_LONG 2*(uint32_t)T_SHORT
#define T_VERY_LONG 2*(uint32_t)T_LONG
#define MILLISECONDS_PER_SECOND 1000


/* general constants */
#define LED_COUNT 4
#define LEVEL_COUNT 16
#define INITIAL_DEMONSTRATION_LED_COUNT 3
#define INITIAL_LEVEL 1
#define INITIAL_RAND_SEED 0
#define MAX_DEMONSTRATION_LED_COUNT 10
#define DEMONSTRATION_ON_MILLIS_PRECENTAGE_INCREASE 0.1
#define GAME_LOST_BLINK_COUNT 5
#define GAME_TRANSITION_BLINK_COUNT 5
#define GAME_ENDING_BLINK_COUNT 4

/* defining own boolean enum struct for better readability */
typedef enum {
    FALSE, TRUE
} boolean;

/* game state enum used in state pattern */
typedef enum {
    INITIAL, READY, DEMONSTRATION, IMITATION, LOST, TRANSITION, END
} game_state;

#endif
