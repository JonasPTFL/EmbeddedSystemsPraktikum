#include "types.h"
#include "game.h"
#include "functions.h"
#include "led_control.h"
#include <time.h>

static game_state state = INITIAL;
static int demonstration_on_millis = T_LONG;
static int demonstration_led_count = 3;
static int level = 1;
static int pressed_button_pins[10];
static int seed = 0;

static unsigned short lfsr = 0xACE1u;
static unsigned int bit;

void setup_button(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << gpio_pin);
}

unsigned int nearly_random_number(void){

    bit  = (((int)lfsr >> 0) ^ ((int)lfsr >> 2) ^ ((int)lfsr >> 3) ^ ((int)lfsr >> 5) ) & 1;
    return (int)(((lfsr =  (int)((int)lfsr >> 1) | (bit << 15))+seed) % 4);
}

boolean is_pressed(int button){
    boolean result;
    if((int)(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << button)) <= 0) {
        result = TRUE;
    } else {
        result = FALSE;
    }
    return result;
}

boolean is_only_pressed(int button){
    return is_pressed(button)  // TODO can be simplified??
        && ((button == GREEN_BUTTON) || ((button != GREEN_BUTTON) && (!is_pressed(GREEN_BUTTON))))
        && ((button == BLUE_BUTTON) || ((button != BLUE_BUTTON) && (!is_pressed(BLUE_BUTTON))))
        && ((button == YELLOW_BUTTON) || ((button != YELLOW_BUTTON) && (!is_pressed(YELLOW_BUTTON))))
        && ((button == RED_BUTTON) || ((button != RED_BUTTON) && (!is_pressed(RED_BUTTON))));
}

int get_button_for_led(int led_pin){
    int button_pin;
    switch (led_pin)
    {
    case GREEN_LED: button_pin = GREEN_BUTTON; break;
    case BLUE_LED: button_pin = BLUE_BUTTON; break;
    case YELLOW_LED: button_pin = YELLOW_BUTTON; break;
    case RED_LED: button_pin = RED_BUTTON; break;
    default: button_pin = -1; break;
    }
    return button_pin;
}

boolean delay_with_any_button_interrupt(unsigned_long milliseconds){
    unsigned_long pause;
    clock_t now;
    clock_t then;

    pause = (unsigned_long)(milliseconds*((unsigned_long)(CLOCKS_PER_SEC/5000)));
    now = clock();
    then = now;
    boolean interrupted = FALSE;
    while( (interrupted == FALSE) && (((unsigned_long)(now-then)) < pause)) {
        if (is_pressed(GREEN_BUTTON) 
        || is_pressed(BLUE_BUTTON) 
        || is_pressed(YELLOW_BUTTON) 
        || is_pressed(RED_BUTTON)){
            interrupted = TRUE;
        }
       
        now = clock();
    }
    return interrupted;
}

boolean delay_with_specific_button_interrupt(unsigned_long milliseconds, int button){
    unsigned_long pause;
    clock_t now;
    clock_t then;
    pause = (unsigned_long)(milliseconds*((unsigned_long)(CLOCKS_PER_SEC/5000)));
    now = clock();
    then = now;
    boolean interrupted = FALSE;
    while( (interrupted == FALSE) && ((unsigned_long)(now-then) < pause)) {
        if (is_pressed(button) == TRUE) {
            interrupted = TRUE;
        }

        now = clock();
    }
    return interrupted;
}

void delay(unsigned_long milliseconds){
    unsigned_long pause;
    clock_t now;
    clock_t then;

    pause = (unsigned_long)(milliseconds*((unsigned_long)(CLOCKS_PER_SEC/5000)));
    now = clock();
    then = now;
    while(((unsigned_long)(now-then)) < pause) {
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

void reset_game(void){
    level = 1;
    demonstration_on_millis = T_SHORT;
    demonstration_led_count = 3;
}

void loop(void){
    switch (state){
        case INITIAL:
            all_led_blink_short();
            state = READY;
            break;
        case READY: {
            boolean green_btn_pressed = game_ready();
            if (green_btn_pressed == TRUE){

                if (seed == 0) {
                    seed = clock();
                }

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
        case IMITATION: 
            ;
            boolean sequence_passed = game_imitation(demonstration_led_count, demonstration_on_millis, pressed_button_pins);
            if (sequence_passed == TRUE) {
                state = TRANSITION;
            } else {
                state = LOST;
            }
            break;
        case LOST:
            game_lost(level-1);
            reset_game();
            state = READY;
            break;
        case TRANSITION:
            game_transition();
            level++;
            if (level > LEVEL_COUNT) {
                state = END;
            } else {
                game_evaluate_round(level, &demonstration_led_count, &demonstration_on_millis);
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

