#include "game.h"
#include "led_control.h"
#include "types.h"
#include "functions.h"

/*
* I copied some of the preprocessor annotation to obtain the current system time from the platform.h header file and other lib files from
* the embedded systems git repo workspace. I did not want to include the whole lib, since the code of the lib throws misra warnings and 
* a only need a small part from the library to fetch the current system time.
*
* #include "platform.h" is missing on purpose...
*/


static uint32_t demonstration_on_millis = (uint32_t)T_LONG;
static uint_t demonstration_led_count = INITIAL_DEMONSTRATION_LED_COUNT;
static int level = INITIAL_LEVEL;
static uint_t seed = INITIAL_RAND_SEED;


/* sets up the button with the given gpio pin  */
void setup_button(uint32_t gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1U << gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= 1U << gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1U << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1U << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << gpio_pin);
}

/* generates a nearly random number from 0 to 3  
* this method is a modifier version from the method posted on :
* stackoverflow.com/a/7603688
* This posted code snippet is a modifier version of an generation algorithm from the wikipedia article:
* en.wikipedia.org/wiki/Linear_feedback_shift_register
* and uses bit shift. I modified the output by adding a seed value to get different values
* when restarting the device. */
unsigned int nearly_random_number(void){
    static uint_t lfsr = 0xADEu;
    uint_t bit = (uint_t)((((lfsr >> 0U) ^ (lfsr >> 2U)) ^ (lfsr >> 3U)) ^ (lfsr >> 5U))  & 1U;

    lfsr =  (lfsr >> 1U) | (bit << 15U);
    return (lfsr+seed) % 4U;
}

/* returns true, if the given button pin is pressed  */
boolean is_pressed(uint32_t button){
    boolean result;
    if((uint32_t)(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1U << button)) == 0U) {
        result = TRUE;
    } else {
        result = FALSE;
    }
    return result;
}

/* returns true, if the given button pin is pressed and all other buttons are not pressed  */
boolean is_only_pressed(uint32_t button){
    return is_pressed(button)
        && ((button == GREEN_BUTTON) || ((button != GREEN_BUTTON) && (!is_pressed(GREEN_BUTTON))))
        && ((button == BLUE_BUTTON) || ((button != BLUE_BUTTON) && (!is_pressed(BLUE_BUTTON))))
        && ((button == YELLOW_BUTTON) || ((button != YELLOW_BUTTON) && (!is_pressed(YELLOW_BUTTON))))
        && ((button == RED_BUTTON) || ((button != RED_BUTTON) && (!is_pressed(RED_BUTTON))));
}

/* returns the button matching the given led_pin color  */
int get_button_for_led(uint32_t led_pin){
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
boolean delay_with_any_button_interrupt(uint32_t milliseconds){
    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
    volatile uint64_t then = *now + (uint64_t)milliseconds*((uint64_t)RTC_FREQ / (uint64_t)MILLISECONDS_PER_SECOND);
    boolean interrupted = FALSE;
    while ((interrupted == FALSE) && ((*now) < then)){
        if (is_pressed(GREEN_BUTTON) 
        || is_pressed(BLUE_BUTTON) 
        || is_pressed(YELLOW_BUTTON) 
        || is_pressed(RED_BUTTON)){
            interrupted = TRUE;
        }
    }
    return interrupted;
}

/* delay the program for a specific amount of milliseconds and interrupts on a specific button pin press  */
boolean delay_with_specific_button_interrupt(uint32_t milliseconds, uint32_t button){
    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
    volatile uint64_t then = *now + (uint64_t)milliseconds*((uint64_t)RTC_FREQ / (uint64_t)MILLISECONDS_PER_SECOND);
    boolean interrupted = FALSE;
    while ((interrupted == FALSE) && ((*now) < then)){
            if (is_pressed(button) == TRUE) {
                interrupted = TRUE;
            }   
    }
    return interrupted;
}

/* delay the program for a specific amount of milliseconds  */
void delay(uint32_t milliseconds){
    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
    volatile uint64_t then = *now + (uint64_t)milliseconds*((uint64_t)RTC_FREQ / (uint64_t)MILLISECONDS_PER_SECOND);
    while ((*now) < then){
        
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
    static uint32_t pressed_button_pins[MAX_DEMONSTRATION_LED_COUNT];
    static game_state state = INITIAL;
    switch (state){
        case INITIAL:
            all_led_blink_short();
            state = READY;
            break;
        case READY: {
            boolean green_btn_pressed = game_ready();
            if (green_btn_pressed == TRUE){

                if (seed == (uint_t)INITIAL_RAND_SEED) {
                    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
                    seed = (uint_t)*now;
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

