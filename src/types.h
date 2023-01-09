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
#define MILLISECONDS_PER_SECOND 1000

/* pins */
#define BUTTON_LEFT_UP 10
#define BUTTON_LEFT_DOWN 11
#define BUTTON_RIGHT_DOWN 20
#define BUTTON_RIGHT_UP 21
#define GREEN_LED 22
#define BLUE_LED 23
#define YELLOW_LED 0
#define RED_LED 1

/* defining own boolean enum struct for better readability */
typedef enum {
    FALSE, TRUE
} boolean;

#endif
