#include "types.h"
#include "game.h"
#include "functions.h"
#include "led_control.h"

game_state state = INITIAL;


void setup_button(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << gpio_pin);
}

boolean is_pressed(int button){
    if((REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << button)) <= 0) return TRUE;
    else return FALSE;
}

void delay(){
    volatile uint32_t i = 0;
    for (i = 0; i < 184210; i++){}
}

void setup(void){
    setup_led(GREEN_LED);
    setup_led(BLUE_LED);
    setup_led(YELLOW_LED);
    setup_led(RED_LED);

    setup_button(GREEN_BUTTON);
    setup_button(BLUE_BUTTON);
    setup_button(YELLOW_BUTTON);
    setup_button(RED_BUTTON);
}

void loop(){
    switch (state){
        case INITIAL:
            led_blink_initial();
            //state = STANDBY;
            break;
        case STANDBY:
            break;
        case DEMONSTRATION:
            break;
        case IMITATION:
            break;
        case LOST:
            break;
        case TRANSITION:
            break;
        case END:
            break;
        
        default:
            break;
    }
}

int main(void){

    setup();

    while(1){
        loop();
    }
}

