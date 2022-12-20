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
    i2c_init();
}

/* programm loop, that runs forever  */
void loop(void){

    uint_t brightness = read_light_sensor();
    if(brightness > 110){
        show_next_led_stripe_colors();
        for (uint_t i = 0; i < sizeof(song)/sizeof(song[0]); i++){
        
            brightness = read_light_sensor();
            
            uint_t tone_frequency = song[i];
            float tone_duration = duration[i];

            if(brightness > 110){
                play_tone(tone_frequency, tone_duration);
            } else {
                break;
            }
        }
    }

}

/* main method, which starts the program  */
int main(void){

    setup();

    // test
    asm(
        ""
        ""
    );

    while(1){
        loop();
    }
}


