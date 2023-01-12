/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "startup.h"
#include "wrap.h"
#include "types.h"
/* includes for oled display */
#include "encoding.h"
#include "platform.h"
#include "display.h"
#include "framebuffer.h"
#include "font.h"

//#include <string.h>

void irq_handler() __attribute__((interrupt));

int left_game_bar_height = (DISP_H/2)+(GAME_BAR_HEIGHT/2), right_game_bar_height = (DISP_H/2)+(GAME_BAR_HEIGHT/2);
int ball_x = DISP_W/2, ball_y = DISP_H/2;
int ball_speed_x = 1, ball_speed_y = 1;
int last_ball_pos_x = -1, last_ball_pos_y = -1;

/*-----------------------------------------------------------*/

/* The task functions. */
void update_ball( void *pvParameters );
void update_game( void *pvParameters );

/*-----------------------------------------------------------*/
int main( void )
{

	setup();

	/* three tasks with different priorities */
	xTaskCreate( update_ball, "Draw game", 1000, NULL, 2, NULL );
	xTaskCreate( update_game, "Updates the game", 1000, NULL, 1, NULL );

	/* start scheduler */
	vTaskStartScheduler();

	for( ;; ){}
	return 0;
}

/* delay the program for a specific amount of milliseconds  */
void delay(uint32_t milliseconds){
    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
    volatile uint64_t then = *now + (uint64_t)milliseconds*((uint64_t)RTC_FREQ / (uint64_t)MILLISECONDS_PER_SECOND);
    while ((*now) < then){
        
    }
}

/* enables all leds with the given state  */
void enabled_all_leds(boolean state){
    enable_led(GREEN_LED, state);
    enable_led(BLUE_LED, state);
    enable_led(YELLOW_LED, state);
    enable_led(RED_LED, state);
}

/* enables a pecific led with the given state  */
void enable_led(uint32_t led, boolean state){
    if (state == TRUE){
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << led);
    } else{
	    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << led);
    }
}

void setup(void){

	init_irq();

	oled_init();
    fb_init();

	setup_led(GREEN_LED);
	setup_led(BLUE_LED);
	setup_led(YELLOW_LED);
	setup_led(RED_LED);

	enabled_all_leds(FALSE);

	setup_button(BUTTON_RIGHT_DOWN);
	setup_button(BUTTON_RIGHT_UP);
	setup_button(BUTTON_LEFT_DOWN);
	setup_button(BUTTON_LEFT_UP);


	// intitially draw bars
	draw_game_bar(GAME_BAR_PADDING, left_game_bar_height);
	draw_game_bar(DISP_W-GAME_BAR_PADDING, right_game_bar_height);
}


void toggle_led(uint32_t led){
	REG(GPIO_BASE + GPIO_OUTPUT_VAL)  ^=  (1U << led);
}

/* sets up the given led pin  */
void setup_led(uint32_t gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~((uint32_t)1 << gpio_pin);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~((uint32_t)1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= ((uint32_t)1 << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= ((uint32_t)1 << gpio_pin);
}

/* sets up the button with the given gpio pin  */
void setup_button(uint32_t gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1U << gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= 1U << gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1U << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1U << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << gpio_pin);
}


void init_irq()
{
    	// PLIC, 52 sources, 7 priorities
	// all off
	REG(PLIC_BASE + PLIC_ENABLE) = 0;
	REG(PLIC_BASE + PLIC_ENABLE + 4) = 0;
	// threshold 0
	REG(PLIC_BASE + PLIC_THRESH) = 0;

	// enable irq for button and set priority for button to 1
	// interrupts for gpio start at 8
	REG(PLIC_BASE + PLIC_ENABLE) |= (1 << (8 + BUTTON_LEFT_UP));
	REG(PLIC_BASE + 4 * (8 + BUTTON_LEFT_UP)) = 1;

	// set handler
	//asm volatile("csrw mtvec, %0" ::"r"(irq_handler));

	// irq at rising
	REG(GPIO_BASE + GPIO_RISE_IE) |= (1 << BUTTON_LEFT_UP);

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BUTTON_LEFT_UP);

	// enable plic interrupts, set meie
	//asm volatile("csrw mie, %0" ::"r"(1 << 11));

	// Enable all interrupts, set mie
	//asm volatile("csrw mstatus, %0" ::"i"(0x8));
}

void activate_button_for_interrupt(int pin){
	// enable irq for button and set priority for button to 1
    // interrupts for gpio start at 8
    REG(PLIC_BASE + PLIC_ENABLE) |= (1 << (8+pin));
    REG(PLIC_BASE + 4*(8+pin)) = 1;

	// irq at rising
    REG(GPIO_BASE + GPIO_RISE_IE) |= (1 << pin);

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << pin);
}


void clear_button_interrupt(int pin){

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << pin);
}

void irq_handler()
{
	// claim interrupt
	uint32_t nb = REG(PLIC_BASE + PLIC_CLAIM);

	// toggle led
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) ^= (1 << RED_LED);

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BUTTON_LEFT_UP);

	// complete interrupt
	REG(PLIC_BASE + PLIC_CLAIM) = nb;
}

/*-----------------------------------------------------------*/
void update_ball( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelay = pdMS_TO_TICKS( GAME_UPDATE_INTERVAL_MILLIS );

	xLastWakeTime = xTaskGetTickCount();


	for( ;; )
	{
		/* periodic */
		vTaskDelayUntil( &xLastWakeTime, xDelay );


		// currently nothing
	}
}

void draw_game_bar(uint8_t x, uint8_t y){
	for(uint8_t i=0; i < GAME_BAR_HEIGHT; i++){
		fb_set_pixel_direct(x, y-i, 1);
	}
}

/*-----------------------------------------------------------*/
void update_game( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelay = pdMS_TO_TICKS( GAME_UPDATE_INTERVAL_MILLIS );

	xLastWakeTime = xTaskGetTickCount();


	for( ;; )
	{
		/* periodic */
		vTaskDelayUntil( &xLastWakeTime, xDelay );

		if(ball_x <= 0 || ball_x >= DISP_W){
			// game over
			printText("Game over");
			continue;
		}

		// check edges
		if(ball_y >= DISP_H-1){
			ball_speed_y = -ball_speed_y;
		}else if(ball_y <= 1){
			ball_speed_y = -ball_speed_y;
		}

		// check bars
		if(ball_x == GAME_BAR_PADDING+1 || ball_x == DISP_W-GAME_BAR_PADDING-1){
			// x position matches bar x pos
			if((ball_y <= left_game_bar_height && ball_y > left_game_bar_height - GAME_BAR_HEIGHT)
				|| (ball_y <= right_game_bar_height && ball_y > right_game_bar_height - GAME_BAR_HEIGHT)){
				ball_speed_x = -ball_speed_x;
			}

		}

		fb_set_pixel_direct(ball_x, ball_y, 0);

		ball_x += ball_speed_x;
		ball_y += ball_speed_y;

		fb_set_pixel_direct(ball_x, ball_y, 1);
	}
}
