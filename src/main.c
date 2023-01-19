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

void irq_handler(void);
static void reset_game(void);
static void draw_game_bar(uint8_t x, uint8_t y);
static void delay(uint32_t milliseconds);
static unsigned int nearly_random_number(void);
static void setup(void);
static void draw_game_bars(void);
static uint8_t check_bar_in_screen(uint8_t bar_height);
static boolean is_pressed(uint32_t button);
static void clear_button_interrupt(uint8_t pin);
static void activate_button_for_interrupt(uint8_t pin);
static void init_irq(void);
static void setup_button(uint32_t gpio_pin);
static void end_round(void);

static int left_game_bar_height = (int)(((int)DISP_H/2)+((int)GAME_BAR_HEIGHT/2));
static int right_game_bar_height = (int)(((int)DISP_H/2)+((int)GAME_BAR_HEIGHT/2));
static float ball_x = (float)DISP_W/2;
static float ball_y = (float)DISP_H/2;
static float ball_speed_x = (float)BALL_SPEED;
static float ball_speed_y = (float)BALL_SPEED;
static uint_t seed = 0;


/*-----------------------------------------------------------*/

static TaskHandle_t xBallUpdateTask;
static TaskHandle_t xGameEndTask;

/* The task functions. */
static void update_ball( void *pvParameters );
static void show_scores( void *pvParameters );

/*-----------------------------------------------------------*/
int main( void )
{

	setup();

	/* three tasks with different priorities */
	BaseType_t t1 = xTaskCreate( update_ball, "Update Ball", 1000U, NULL, 2, &xBallUpdateTask);
	//BaseType_t t2 = xTaskCreate( update_game, "Updates the game", 1000U, NULL, 3, NULL );
	BaseType_t t3 = xTaskCreate( show_scores, "Shows the player scores", 1000U, NULL, 4, &xGameEndTask );
	

	(void) t1;
	//(void) t2;
	(void) t3;

	/* start scheduler */
	vTaskStartScheduler();

	for( ;; ){}
	return 0;
}

/* generates a nearly random number 0 or 1
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
    return (lfsr+seed) % 2U;
}

void setup(void){

	init_irq();

	oled_init();
    fb_init();

	setup_button(BUTTON_RIGHT_DOWN);
	setup_button(BUTTON_RIGHT_UP);
	setup_button(BUTTON_LEFT_DOWN);
	setup_button(BUTTON_LEFT_UP);

	// intitially draw bars
	draw_game_bars();
	
}

void draw_game_bars(void){
	right_game_bar_height = check_bar_in_screen(right_game_bar_height);
	left_game_bar_height = check_bar_in_screen(left_game_bar_height);

	for(uint8_t i=0; i < DISP_H; i++){
		fb_set_pixel_direct(GAME_BAR_PADDING, i, 0U);
		fb_set_pixel_direct(DISP_W-GAME_BAR_PADDING, i, 0U);
	}
	draw_game_bar(GAME_BAR_PADDING, left_game_bar_height);
	draw_game_bar(DISP_W-GAME_BAR_PADDING, right_game_bar_height);
}

/* sets up the button with the given gpio pin  */
void setup_button(uint32_t gpio_pin){
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1U << gpio_pin);
	REG(GPIO_BASE + GPIO_PUE) |= 1U << gpio_pin;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1U << gpio_pin;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1U << gpio_pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << gpio_pin);
}


void init_irq(void)
{
	(void) init_irq;
    // PLIC, 52 sources, 7 priorities
	// all off
	REG(PLIC_BASE + PLIC_ENABLE) = 0U;
	REG(PLIC_BASE + PLIC_ENABLE + 4U) = 0U;
	// threshold 0
	REG(PLIC_BASE + PLIC_THRESH) = 0U;

	activate_button_for_interrupt(BUTTON_LEFT_UP);
	activate_button_for_interrupt(BUTTON_LEFT_DOWN);
	activate_button_for_interrupt(BUTTON_RIGHT_UP);
	activate_button_for_interrupt(BUTTON_RIGHT_DOWN);
}

void activate_button_for_interrupt(uint8_t pin){
	// enable irq for button and set priority for button to 1
    // interrupts for gpio start at 8
    REG(PLIC_BASE + PLIC_ENABLE) |= (1U << (8U+pin));
    REG(PLIC_BASE + 4U*(8U+pin)) = 1U;

	// irq at rising
    REG(GPIO_BASE + GPIO_RISE_IE) |= (1U << pin);

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1U << pin);
}

void clear_button_interrupt(uint8_t pin){
	(void) clear_button_interrupt;
	// clear gpio penactivate_button_for_interruptding interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1U << pin);
}

void irq_handler(void)
{

	(void) irq_handler; 
	// claim interrupt
	uint32_t nb = REG(PLIC_BASE + PLIC_CLAIM);
	uint32_t button_pin = nb-8U;

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1U << (button_pin));

	if (button_pin == BUTTON_LEFT_UP){
		left_game_bar_height -= GAME_BAR_STEP_LENGTH;
	} else if(button_pin == BUTTON_LEFT_DOWN){
		left_game_bar_height += GAME_BAR_STEP_LENGTH;
	} else if(button_pin == BUTTON_RIGHT_UP){
		right_game_bar_height -= GAME_BAR_STEP_LENGTH;
	}  else if(button_pin == BUTTON_RIGHT_DOWN){
		right_game_bar_height += GAME_BAR_STEP_LENGTH;
	} else {

	}
	

	draw_game_bars();

	// complete interrupt
	REG(PLIC_BASE + PLIC_CLAIM) = nb;
}

uint8_t check_bar_in_screen(uint8_t bar_height){
	uint8_t new_bar_height = bar_height;
	if(bar_height < (uint8_t)GAME_BAR_HEIGHT) {
		new_bar_height = GAME_BAR_HEIGHT;
	} else if (bar_height >= (uint8_t)DISP_H) {
		new_bar_height = DISP_H-1;
	} else {

	}
	return new_bar_height;
}

/*-----------------------------------------------------------*/
void update_ball( void *pvParameters )
{
	( void ) pvParameters;
	TickType_t xLastWakeTime;
	const TickType_t xDelay = pdMS_TO_TICKS( GAME_UPDATE_INTERVAL_MILLIS );

	xLastWakeTime = xTaskGetTickCount();


	for( ;; )
	{
		/* periodic */
		vTaskDelayUntil( &xLastWakeTime, xDelay );

		// check game ended
		if((ball_x <= (float)0) || ( ball_x >= (float)DISP_W)){
			vTaskResume(xGameEndTask);
			vTaskSuspend(NULL);
		}


		// check edges
		if(ball_y >= (float)DISP_H-(float)1){
			ball_speed_y = -ball_speed_y;
		}else if(ball_y <= (float)1){
			ball_speed_y = -ball_speed_y;
		} else {

		}



		// check bars
		if((ball_x == (float)(GAME_BAR_PADDING+1.0)) || (ball_x == (float)(DISP_W-GAME_BAR_PADDING-1.0))){
			// x position matches bar x pos
			if(((ball_y <= (float)left_game_bar_height) && (ball_y > (float)((float)left_game_bar_height - (float)GAME_BAR_HEIGHT)))
				|| (ball_y <= (float)right_game_bar_height && ball_y > (right_game_bar_height - (int)GAME_BAR_HEIGHT))){
				
				boolean hitTop = (boolean)(ball_y <= (float)left_game_bar_height && ball_y > (float)(((float)left_game_bar_height) - GAME_BAR_HEIGHT/2.0F))
				 || ((ball_y <= (float)right_game_bar_height) && (ball_y > (((float)right_game_bar_height) - (float)(((float)GAME_BAR_HEIGHT)/2.0F))));

				if (seed == 0U) {
                    const volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + (uint64_t)CLINT_MTIME);
                    seed = (uint_t)*now;
                } else {

				}

				float rand_modifier = nearly_random_number();
                if (rand_modifier == 1.0F)
                {
                    rand_modifier = 1.25F;
                } else {
                    rand_modifier = 0.75F;
                }
                
				if (hitTop == TRUE)
				{
					ball_speed_y = -rand_modifier;
				} else {
					ball_speed_y = rand_modifier;
				}
				ball_speed_x = -ball_speed_x;
			} else {}
		} else {}

		fb_set_pixel_direct(ball_x, ball_y, 0U);

		ball_x += ball_speed_x;
		ball_y += ball_speed_y;

		fb_set_pixel_direct(ball_x, ball_y, 1U);
	}
}

void draw_game_bar(uint8_t x, uint8_t y){
	for(uint8_t i=0; i < (uint8_t)GAME_BAR_HEIGHT; i++){
		fb_set_pixel_direct(x, y-i, 1);
	}
}


void show_scores( void *pvParameters )
{
	( void ) pvParameters;

	static int left_player_score = 0;
	static int right_player_score = 0;

	for( ;; )
	{
		vTaskSuspend(NULL);
		fb_init();
		oled_clear();
		// game over
		printText("Game over");
		if (ball_x <= 0) {
			right_player_score++;
		} else {
			left_player_score++;
		}

		newline();
		if(left_player_score < 10) {
			printChar(left_player_score+'0');
		} else if(left_player_score < 100) {
			printChar(((int)(left_player_score/10))+'0');
			printChar(((int)(left_player_score%10))+'0');
		} else {

		}
		printText(" - ");
		if(right_player_score < 10) {
			printChar(right_player_score+'0');
		} else if(right_player_score < 100) {
			printChar(((int)(right_player_score/10))+'0');
			printChar(((int)(right_player_score%10))+'0');
		} else {

		}
		const TickType_t xDelay = pdMS_TO_TICKS( 1000 );
		vTaskDelay(xDelay);

		// reset game
		fb_init();
		oled_clear();
		draw_game_bars();
		ball_x = (float)((int)DISP_W)/2;
		ball_y = (float)((int)DISP_H)/2;
		left_game_bar_height = (int)(((int)DISP_H)/2)+(((int)GAME_BAR_HEIGHT)/2);
		right_game_bar_height = (int)((int)DISP_H/2)+(((int)GAME_BAR_HEIGHT)/2);

		ball_speed_x = (float) BALL_SPEED;
		ball_speed_y = (float) BALL_SPEED;
		

		vTaskResume(xBallUpdateTask);

	}
}
