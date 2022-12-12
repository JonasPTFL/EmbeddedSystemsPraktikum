#include "led_control.h"
#include "types.h"
#include "functions.h"
#include "song.h"

/*
* I copied some of the preprocessor annotation to obtain the current system time from the platform.h header file and other lib files from
* the embedded systems git repo workspace. I did not want to include the whole lib, since the code of the lib throws misra warnings and 
* a only need a small part from the library to fetch the current system time.
*
* #include "platform.h" is missing on purpose...
*/

/* delay the program for a specific amount of milliseconds  */
void delay(uint32_t milliseconds){
    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
    volatile uint64_t then = *now + (uint64_t)milliseconds*((uint64_t)RTC_FREQ / (uint64_t)MILLISECONDS_PER_SECOND);
    while ((*now) < then){
        
    }
}

/* sets up the program (leds and buttons)  */
void setup(void){
    setup_buzzer();
    setup_led_stripe();
}

/* programm loop, that runs forever  */
void loop(void){
    enabled_led_stripe();
    for (uint_t i = 0; i < sizeof(song)/sizeof(song[0]); i++){
    
        uint_t tone_frequency = song[i];
        float tone_duration = duration[i];

        play_tone(tone_frequency, tone_duration);
    }
    delay(5000);

}

void setup_buzzer(){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << BUZZER);
}

void setup_led_stripe(){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << LED_STRIPE);
}

void delay_tone_frequency(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 1000 *12);
    while (*now < then);
}

void play_frequency(uint_t tone_frequency){
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << BUZZER);
    delay_tone_frequency(1000/(tone_frequency*2));
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << BUZZER);
    delay_tone_frequency(1000/(tone_frequency*2));
}

void enabled_led_stripe(){
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << LED_STRIPE);
    delay_tone_frequency(2);
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << LED_STRIPE);
}

void play_tone(uint_t tone_frequency, float tone_duration){
    for (double i = 0; i < tone_duration; i++)
    {
        for (uint_t j = 0; j < tone_frequency; j++)
        {   
            play_frequency(tone_frequency);
        }
    }
}

/* main method, which starts the program  */
int main(void){

    setup();

    asm(
        ""
        ""
    );

    while(TRUE){
        loop();
    }
}


