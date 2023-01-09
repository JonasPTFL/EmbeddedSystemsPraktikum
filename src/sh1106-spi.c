#include "types.h"

#include "encoding.h"
#include "platform.h"
#include "wrap.h"
#include "startup.h"

#include "display.h"
#include "font.h"
#include "framebuffer.h"



/* delay the program for a specific amount of milliseconds  */
void delay(double milliseconds){
    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
    volatile uint64_t then = *now + ((double)milliseconds)*(((double)RTC_FREQ) / ((double)MILLISECONDS_PER_SECOND));
    while ((*now) < then){
        
    }
}

/* sets up the button with the given gpio pin  */
void setup_button(uint32_t gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1U << gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= 1U << gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1U << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1U << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << gpio_pin);
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

/* sets up the program (leds and buttons)  */
void setup(void){
    //init oled inclusive spi
	oled_init();
    setup_button(BUTTON_LEFT_DOWN);
    setup_button(BUTTON_LEFT_UP);
    setup_button(BUTTON_RIGHT_DOWN);
    setup_button(BUTTON_RIGHT_UP);
    
	draw_control_panel(30);
}

void draw_control_panel(int y){
	for (uint8_t i = 0; i < PANEL_WIDTH; i++)
	{
		fb_draw_vertical_line(30+i, y, PANEL_HEIGHT);
	}
}

/* programm loop, that runs forever  */
void loop(void){
}

/* main method, which starts the program  */
int main(void){
    setup();

    while(1){
        loop();
    }
}


