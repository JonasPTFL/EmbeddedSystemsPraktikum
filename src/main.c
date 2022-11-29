#include "game.h"
#include "led_control.h"
#include "types.h"
#include "functions.h"
#include <time.h>

static int demonstration_on_millis = T_LONG;
static int demonstration_led_count = INITIAL_DEMONSTRATION_LED_COUNT;
static int level = INITIAL_LEVEL;
static u_int seed = INITIAL_RAND_SEED;


/* sets up the button with the given gpio pin  */
void setup_button(int gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << (uint32_t) gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= (uint32_t)1 << (uint32_t) gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= (uint32_t)1 << (uint32_t) gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~((uint32_t)1 << (uint32_t) gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~((uint32_t)1 << (uint32_t) gpio_pin);
}

/* generates a nearly random number from 0 to 3  */
unsigned int nearly_random_number(void){
    static u_int lfsr = 0xADEu;
    u_int bit = (u_int)(((((u_int)lfsr >> (u_int)0) ^ ((u_int)lfsr >> (u_int)2)) ^ ((u_int)lfsr >> (u_int)3)) ^ ((u_int)lfsr >> (u_int)5))  & (u_int)1;

    lfsr =  ((u_int)lfsr >> (u_int)1) | ((u_int)bit << (u_int)15);
    return ((lfsr)+seed) % (u_int)4;
}

/* returns true, if the given button pin is pressed  */
boolean is_pressed(int button){
    boolean result;
    if((uint32_t)(REG(GPIO_BASE + GPIO_INPUT_VAL) & ((uint32_t)1 << (uint32_t) button)) == (uint32_t) 0) {
        result = TRUE;
    } else {
        result = FALSE;
    }
    return result;
}

/* returns true, if the given button pin is pressed and all other buttons are not pressed  */
boolean is_only_pressed(int button){
    return is_pressed(button)
        && ((button == GREEN_BUTTON) || ((button != GREEN_BUTTON) && (!is_pressed(GREEN_BUTTON))))
        && ((button == BLUE_BUTTON) || ((button != BLUE_BUTTON) && (!is_pressed(BLUE_BUTTON))))
        && ((button == YELLOW_BUTTON) || ((button != YELLOW_BUTTON) && (!is_pressed(YELLOW_BUTTON))))
        && ((button == RED_BUTTON) || ((button != RED_BUTTON) && (!is_pressed(RED_BUTTON))));
}

/* returns the button matching the given led_pin color  */
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

/* delay the program for a specific amount of milliseconds and interrupts on any button press  */
boolean delay_with_any_button_interrupt(unsigned_long milliseconds){
    unsigned_long pause;
    clock_t now;
    clock_t then;

    pause = (unsigned_long)(milliseconds*((unsigned_long)((unsigned_long)CLOCKS_PER_SEC/(unsigned_long)MILLISECONDS_PER_SECOND)));
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

/* delay the program for a specific amount of milliseconds and interrupts on a specific button pin press  */
boolean delay_with_specific_button_interrupt(unsigned_long milliseconds, int button){
    unsigned_long pause;
    clock_t now;
    clock_t then;

    pause = (unsigned_long)(milliseconds*((unsigned_long)((unsigned_long)CLOCKS_PER_SEC/(unsigned_long)MILLISECONDS_PER_SECOND)));
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

/* delay the program for a specific amount of milliseconds  */
void delay(unsigned_long milliseconds){
    unsigned_long pause;
    clock_t now;
    clock_t then;

    pause = (unsigned_long)(milliseconds*((unsigned_long)((unsigned_long)CLOCKS_PER_SEC/(unsigned_long)MILLISECONDS_PER_SECOND)));
    now = clock();
    then = now;
    while(((unsigned_long)(now-then)) < pause) {
        now = clock();
    }
}

/* sets up the program (leds and buttons)  */
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

/* sets up the program (leds and buttons)  */
void reset_game(void){
    level = INITIAL_LEVEL;
    demonstration_on_millis = T_SHORT;
    demonstration_led_count = INITIAL_DEMONSTRATION_LED_COUNT;
}

/* game loop, which should be reapetly called forever  */
void loop(void){
    static int pressed_button_pins[MAX_DEMONSTRATION_LED_COUNT];
    static game_state state = INITIAL;
    switch (state){
        case INITIAL:
            all_led_blink_short();
            state = READY;
            break;
        case READY: {
            boolean green_btn_pressed = game_ready();
            if (green_btn_pressed == TRUE){

                if (seed == (u_int)INITIAL_RAND_SEED) {
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

/* main method, which starts the program  */
int main(void){

    setup();

    while(1){
        loop();
    }
}

