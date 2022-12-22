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

/* time measurement */
#define CLINT_CTRL_ADDR 0x02000000UL
#define CLINT_MTIME 0xBFF8
#define RTC_FREQ 32768

/* led gpio pins */
#define LED_STRIPE 9U
#define BUZZER 11

/* time length definitions */
#define MILLISECONDS_PER_SECOND 1000
#define BRIGTHNESS_CHANGE_VALUE 110U


typedef struct color {
    uint_t g;
    uint_t r;
    uint_t b;
} color;

#endif
