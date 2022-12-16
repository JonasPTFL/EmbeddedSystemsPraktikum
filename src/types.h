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

/* i2c sifive */
#define I2C_SL_ADDR 0x1d

/* time measurement */
#define CLINT_CTRL_ADDR 0x02000000UL
#define CLINT_MTIME 0xBFF8
#define RTC_FREQ 32768

/* led gpio pins */
#define LED_STRIPE 9U
#define BUZZER 11

/* time length definitions */
#define SIMULATOR_MILLIS_MULTIPLIER 13.25
#define MILLISECONDS_PER_SECOND 1000
#define SONG_DURATION_STEPS 0.5


typedef struct color {
    uint_t green;
    uint_t red;
    uint_t blue;
} color_t;

/* general constants */


#define RED   { .green = 0x00, .red = 0xFF, .blue = 0x00 } 
#define GREEN { .green = 0xFF, .red = 0x00, .blue = 0x00 }
#define BLUE  { .green = 0x00, .red = 0x00, .blue = 0xFF }
#define START_COLOR 2

/* defining own boolean enum struct for better readability */
typedef enum {
    FALSE, TRUE
} boolean;

/* game state enum used in state pattern */

#endif
