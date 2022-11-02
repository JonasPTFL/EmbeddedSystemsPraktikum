typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38
#define GPIO_INPUT_VAL 0x0
#define GPIO_PUE 0x10

#define BLUE_LED 5
#define GREEN_LED 18
#define BUTTON 19

typedef enum {
    FALSE, TRUE
} boolean;

void setup_led(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << gpio_pin);
}

void setup_button(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << gpio_pin);
}

void enable_led(int led, int state){
    if (state){
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << led);
    } else{
	    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << led);
    }
    
}

boolean is_pressed(int button){
    if((REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << BUTTON)) <= 0) return TRUE;
    else return FALSE;
}

int main (void)
{
	// setup LEDs
    setup_led(BLUE_LED);
    setup_led(GREEN_LED);

    setup_button(BUTTON);

	// toggle only blue LED
    enable_led(BLUE_LED, 0);
    enable_led(GREEN_LED, 0);

    while(1){
		if (is_pressed(BUTTON)){
            enable_led(BLUE_LED, 1);
            enable_led(GREEN_LED, 1);
		} else {
            enable_led(BLUE_LED, 0);
            enable_led(GREEN_LED, 0);
        }
    }

}
