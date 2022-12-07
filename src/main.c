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

uint_t note_index = 0;

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
}

/* programm loop, that runs forever  */
void loop(void){
    for (uint_t i = 0; i < sizeof(song)/sizeof(song[0]); i++){
    
    uint_t tone_frequency = song[note_index];
    float tone_duration = duration[note_index];

    play_tone(tone_frequency, tone_duration);

        note_index = i;
    }
    

}

void setup_buzzer(){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << BUZZER);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << BUZZER);
}

void play_tone(uint_t tone_frequency, float tone_duration){
    for (uint_t i = 0; i < tone_duration; i++)
    {
        for (uint_t j = 0; j < tone_frequency; j++)
        { 
            REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << BUZZER);
            delay((MILLISECONDS_PER_SECOND/2)/tone_frequency);
            REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << BUZZER);
            delay((MILLISECONDS_PER_SECOND/2)/tone_frequency);
        }
        delay(1);
    }
}

/* main method, which starts the program  */
int main(void){

    setup();

    while(1){
        loop();
    }
}

