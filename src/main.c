#include "types.h"
#include "game.h"
#include "functions.h"
#include "led_control.h"
#include <time.h>

game_state state = INITIAL;
int demonstration_on_millis = T_LONG;
int demonstration_led_count = 3;
int level = 1;
int pressed_button_pins[10];

void setup_button(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << gpio_pin);
}

unsigned nearly_random_number(){
    return 0;
}

boolean is_pressed(int button){
    if((REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << button)) <= 0) return TRUE;
    else return FALSE;
}

boolean is_only_pressed(int button){
    return is_pressed(button)  // TODO can be simplified??
        && (button == GREEN_BUTTON || (button != GREEN_BUTTON && !is_pressed(GREEN_BUTTON)))
        && (button == BLUE_BUTTON || (button != BLUE_BUTTON && !is_pressed(BLUE_BUTTON)))
        && (button == YELLOW_BUTTON || (button != YELLOW_BUTTON && !is_pressed(YELLOW_BUTTON)))
        && (button == RED_BUTTON || (button != RED_BUTTON && !is_pressed(RED_BUTTON)));
}

int get_button_for_led(int led_pin){
    switch (led_pin)
    {
    case GREEN_LED: return GREEN_BUTTON;
    case BLUE_LED: return BLUE_BUTTON;
    case YELLOW_LED: return YELLOW_BUTTON;
    case RED_LED: return RED_BUTTON;
    default: return -1;
    }
}

boolean delay_with_any_button_interrupt(int milliseconds){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/5000);
    now = then = clock();
    while( (now-then) < pause ) {
        if (is_pressed(GREEN_BUTTON) 
        || is_pressed(BLUE_BUTTON) 
        || is_pressed(YELLOW_BUTTON) 
        || is_pressed(RED_BUTTON)){
            return TRUE;
        }
       
        now = clock();
    }
    return FALSE;
}

boolean delay_with_specific_button_interrupt(int milliseconds, int button){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/5000);
    now = then = clock();
    while( (now-then) < pause ) {
        if (is_pressed(button))return TRUE;

        now = clock();
    }
    return FALSE;
}

void delay(int milliseconds){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/5000); // TODO klären, wieso es mit 5000 passt, obwohl 1sec=1000ms + TODO redundanten delay code verbessern
    now = then = clock();
    while( (now-then) < pause ) {
        now = clock();
    }
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

void reset_game(){
    level = 1;
    demonstration_on_millis = T_SHORT;
    demonstration_led_count = 3;
}

void loop(){
    switch (state){
        case INITIAL:
            all_led_blink_short();
            state = READY;
            break;
        case READY: {
            boolean green_btn_pressed = game_ready();
            if (green_btn_pressed){
                state = DEMONSTRATION;
            }
            break;
        }
        case DEMONSTRATION:
            game_demonstrate_start();
            game_demonstration_main(demonstration_led_count, demonstration_on_millis, pressed_button_pins);
            all_led_blink_short();
            state = IMITATION;
            break;
        case IMITATION: {
            boolean sequence_passed = game_imitation(demonstration_led_count, demonstration_on_millis, pressed_button_pins);
            if (sequence_passed) state = TRANSITION;
            else state = LOST;
            break;
            }
        case LOST:
            game_lost(level);
            reset_game();
            state = READY;
            break;
        case TRANSITION:
            game_transition();
            if (level > LEVEL_COUNT) state = END;
            else {
                game_evaluate_round(level, &demonstration_led_count, &demonstration_on_millis);
                level++;
                state = DEMONSTRATION;
            }
            break;
        case END:
            game_end();
            reset_game();
            state = READY;
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

