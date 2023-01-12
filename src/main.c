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


int left_game_bar_height = (DISP_H/2)+(GAME_BAR_HEIGHT/2), right_game_bar_height = (DISP_H/2)+(GAME_BAR_HEIGHT/2);
int ballX = DISP_W/2, ballY = DISP_H/2;
int ball_speed_x = 1, ball_speed_y = 1;

void irq_handler() __attribute__((interrupt));


/*-----------------------------------------------------------*/

/* The task functions. */
void draw_game( void *pvParameters );
void update_game( void *pvParameters );

/*-----------------------------------------------------------*/
int main( void )
{

	setup();

	/* three tasks with different priorities */
	xTaskCreate( draw_game, "Draw game", 1000, NULL, 2, NULL );
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

	//init_irq();

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

    // set handler
    asm volatile ("csrw mtvec, %0" :: "r"(irq_handler));

	activate_button_for_interrupt(BUTTON_LEFT_UP);
	activate_button_for_interrupt(BUTTON_LEFT_DOWN);
	activate_button_for_interrupt(BUTTON_RIGHT_UP);
	activate_button_for_interrupt(BUTTON_RIGHT_DOWN);

    // enable plic interrupts, set meie
    asm volatile ("csrw mie, %0" :: "r"(1<<11));

    // Enable all interrupts, set mie
    asm volatile ("csrw mstatus, %0" :: "i"(0x8));
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

    clear_button_interrupt(BUTTON_LEFT_UP);
    clear_button_interrupt(BUTTON_LEFT_DOWN);
    clear_button_interrupt(BUTTON_RIGHT_UP);
    clear_button_interrupt(BUTTON_RIGHT_DOWN);


	// complete interrupt
	REG(PLIC_BASE + PLIC_CLAIM) = nb;
}

/*-----------------------------------------------------------*/
void draw_game( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelay = pdMS_TO_TICKS( GAME_UPDATE_INTERVAL_MILLIS );

	xLastWakeTime = xTaskGetTickCount();


	for( ;; )
	{
		/* periodic */
		vTaskDelayUntil( &xLastWakeTime, xDelay );



		fb_init();
		oled_clear();
		fb_set_pixel_direct(ballX, ballY, 1);

		draw_game_bar(GAME_BAR_PADDING, left_game_bar_height);
		draw_game_bar(DISP_W-GAME_BAR_PADDING, right_game_bar_height);
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

		ballX += ball_speed_x;
		ballY += ball_speed_y;

		if(ballX >= DISP_W-1){
			ball_speed_x = -ball_speed_x;
		} else if(ballX <= 1){
			ball_speed_x = -ball_speed_x;
		}
		if(ballY >= DISP_H-1){
			ball_speed_y = -ball_speed_y;
		}else if(ballY <= 1){
			ball_speed_y = -ball_speed_y;
		}
	}
}
