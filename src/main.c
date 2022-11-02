typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38

#define BLUE_LED 5
#define GREEN_LED 18


void setup_led(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << gpio_pin);
}

void enable_led(int led, int state){
    if (state){
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << led);
    } else{
	    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << led);
    }
    
}

int main (void)
{
	// setup LEDs
    setup_led(BLUE_LED);
    setup_led(GREEN_LED);

	// toggle only blue LED
    enable_led(BLUE_LED, 1);
    enable_led(GREEN_LED, 1);

}