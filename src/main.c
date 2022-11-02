#include "types.h"
#include "game.h"
#include "functions.h"
#include "led_control.h"
#include <stdio.h>
#include <time.h>

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

void delay(int milliseconds){
    delay_with_interrupt(milliseconds, -1);
}

boolean delay_with_interrupt(int milliseconds, int interrupt_button_pin){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/5000); // TODO klären, wieso es mit 5000 passt, obwohl 1sec=1000ms
    now = then = clock();
    while( (now-then) < pause ) {
        if (interrupt_button_pin != -1 && is_pressed(interrupt_button_pin)){
            return TRUE;
        }
        
        now = clock();
    }
    return FALSE;
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
            state = READY;
            break;
        case READY: {
            boolean green_btn_pressed = led_blink_ready();
            if (green_btn_pressed){
                enabled_all_leds(FALSE);
                state = DEMONSTRATION;
            }
            break;
        }
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

