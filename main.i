# 1 "src/main.c"
# 1 "/home/jp/EmbeddedSystems//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "src/main.c"
# 1 "src/led_control.h" 1





# 1 "src/functions.h" 1





# 1 "src/types.h" 1
# 9 "src/types.h"



typedef unsigned int uint_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
# 45 "src/types.h"
typedef enum {
    FALSE, TRUE
} boolean;
# 7 "src/functions.h" 2


static void setup(void);
static void loop(void);
static void setup_buzzer(void);
void play_tone(uint_t tone_frequency, float tone_duration);
# 7 "src/led_control.h" 2




void setup_led(uint32_t gpio_pin){
 (*(volatile uint32_t *) (0x10012000 + 0x38)) &= ~((uint32_t)1 << gpio_pin);
 (*(volatile uint32_t *) (0x10012000 + 0x4)) &= ~((uint32_t)1 << gpio_pin);
 (*(volatile uint32_t *) (0x10012000 + 0x8)) |= ((uint32_t)1 << gpio_pin);
 (*(volatile uint32_t *) (0x10012000 + 0xc)) |= ((uint32_t)1 << gpio_pin);
}
# 2 "src/main.c" 2


# 1 "src/song.h" 1
# 21 "src/song.h"
int song[] = {
    392,330,349,392,440,392,440,392,349,294,392, 330,
    294,294,330,262,330, 294, 349,349,392,294,349,330,
    294,294,330,370,392,294,330,440,392,370,440,392,
    392,330,349,392,440,392,440,392,349,294,392, 330
};

float duration[] = {
    2,1,1,0.5,0.5,0.5,0.5,2,2,1,1,2,
    1,1,1,1,2,2,1,1,1,1,2,2,
    1,1,1,1,2,2,1,1,1,1,2,2,
    2,1,1,0.5,0.5,0.5,0.5,2,2,1,1,2
};
# 5 "src/main.c" 2
# 14 "src/main.c"
uint_t note_index = 0;


void delay(uint32_t milliseconds){
    const volatile uint64_t *now = (volatile uint64_t*)(0x02000000UL + (uint64_t)0xBFF8);
    volatile uint64_t then = *now + (uint64_t)milliseconds*((uint64_t)32768 / (uint64_t)1000);
    while ((*now) < then){

    }
}


void setup(void){
    setup_buzzer();
}


void loop(void){
    for (uint_t i = 0; i < sizeof(song)/sizeof(song[0]); i++){

    uint_t tone_frequency = song[note_index];
    float tone_duration = duration[note_index];

    play_tone(tone_frequency, tone_duration);

        note_index = i;
    }


}

void setup_buzzer(){
 (*(volatile uint32_t *) (0x10012000 + 0x38)) &= ~((uint32_t)1 << 11);
 (*(volatile uint32_t *) (0x10012000 + 0x4)) &= ~((uint32_t)1 << 11);
 (*(volatile uint32_t *) (0x10012000 + 0x8)) |= ((uint32_t)1 << 11);
 (*(volatile uint32_t *) (0x10012000 + 0xc)) |= ((uint32_t)1 << 11);
}

void play_tone(uint_t tone_frequency, float tone_duration){
    for (uint_t i = 0; i < tone_duration; i++)
    {
        for (uint_t j = 0; j < tone_frequency; j++)
        {
            (*(volatile uint32_t *) (0x10012000 + 0xc)) |= (1U << 11);
            delay((1000/2)/tone_frequency);
            (*(volatile uint32_t *) (0x10012000 + 0xc)) &= ~(1U << 11);
            delay((1000/2)/tone_frequency);
        }
        delay(1);
    }
}


int main(void){

    setup();

    while(1){
        loop();
    }
}
