#include "led_control.h"
#include "functions.h"
#include "song.h"
#include "light_sensor.h"
#include "led_stripe.h"
#include "buzzer.h"

/* delay the program for a specific amount of milliseconds  */
void delay(double milliseconds){
    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
    volatile uint64_t then = *now + ((double)milliseconds)*(((double)RTC_FREQ) / ((double)MILLISECONDS_PER_SECOND));
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
    for (uint_t i = 0; i < sizeof(song)/sizeof(song[0]); i++){
    
        uint_t tone_frequency = song[i];
        float tone_duration = duration[i];

        play_tone(tone_frequency, tone_duration);
    }
    delay(5000);

}

/* main method, which starts the program  */
int main(void){

    setup();

    // test
    asm(
        ""
        ""
    );
    enabled_led_stripe();

    while(TRUE){
        loop();
    }
}


