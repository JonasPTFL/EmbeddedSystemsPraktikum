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
//#include "framebuffer.h"
#include "font.h"

//#include <string.h>



void irq_handler() __attribute__((interrupt));


/*-----------------------------------------------------------*/

/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void vTask3( void *pvParameters );
void vTask4( void *pvParameters );

const char *pcTextForTask1 = "Enabled Green LED\n";
const char *pcTextForTask2 = "Enable Blue LED\n";
const char *pcTextForTask3 = "Enable Yellow LED\n";
const char *pcTextForTask4 = "Hallo printed\n";

/*-----------------------------------------------------------*/
int main( void )
{

	setup();
	/* _init for uart printf */
	_init();
	/* three tasks with different priorities */
	xTaskCreate( vTask1, "Enabled Green LED", 1000, (void*)pcTextForTask1, 2, NULL );
	xTaskCreate( vTask2, "Enable Blue LED", 1000, (void*)pcTextForTask2, 1, NULL );
	xTaskCreate( vTask3, "Enable Yellow LED", 1000, (void*)pcTextForTask3, 1, NULL );
	xTaskCreate( vTask4, "Print Hallo", 1000, (void*)pcTextForTask4, 2, NULL );

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
	oled_init();
	
	delay(2000);

	setup_led(GREEN_LED);
	setup_led(BLUE_LED);
	setup_led(YELLOW_LED);
	setup_led(RED_LED);

	enabled_all_leds(FALSE);

	setup_button(BUTTON_RIGHT_DOWN);
	setup_button(BUTTON_RIGHT_UP);
	setup_button(BUTTON_LEFT_DOWN);
	setup_button(BUTTON_LEFT_UP);


	init_irq();
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
    REG(PLIC_BASE + PLIC_ENABLE) |= (1 << (8+BUTTON_LEFT_UP));
    REG(PLIC_BASE + 4*(8+BUTTON_LEFT_UP)) = 1;

    // set handler
    asm volatile ("csrw mtvec, %0" :: "r"(irq_handler));

	// irq at rising
    REG(GPIO_BASE + GPIO_RISE_IE) |= (1 << BUTTON_LEFT_UP);

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BUTTON_LEFT_UP);

    // enable plic interrupts, set meie
    asm volatile ("csrw mie, %0" :: "r"(1<<11));

    // Enable all interrupts, set mie
    asm volatile ("csrw mstatus, %0" :: "i"(0x8));
}

void irq_handler()
{
	// claim interrupt
	uint32_t nb = REG(PLIC_BASE + PLIC_CLAIM);

	// toggle led
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) ^= (1 << RED_LED);


	printChar('T');
	printChar('e');
	printChar('s');
	printChar('t');
	printChar('1');

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BUTTON_LEFT_UP);

	// complete interrupt
	REG(PLIC_BASE + PLIC_CLAIM) = nb;
}

/*-----------------------------------------------------------*/
void vTask1( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelay = pdMS_TO_TICKS( 1000 );

	xLastWakeTime = xTaskGetTickCount();

	toggle_led(GREEN_LED);

	for( ;; )
	{
		//printf(pcTextForTask1);
		/* periodic */
		vTaskDelayUntil( &xLastWakeTime, xDelay );
	}
}

/*-----------------------------------------------------------*/
void vTask2( void *pvParameters )
{
	toggle_led(BLUE_LED);

	for( ;; )
	{
		//printf(pcTextForTask2);
	}
}

/*-----------------------------------------------------------*/
void vTask3( void *pvParameters )
{
	toggle_led(YELLOW_LED);
	for( ;; )
	{
		//printf(pcTextForTask3);
	}
}

/*-----------------------------------------------------------*/
void vTask4( void *pvParameters )
{

	// const char* text = "Oled example...";
	// uint32_t textpos = 0;
	// while (textpos < strlen(text))
	// {
	// 	printChar(text[textpos]);
	// 	if(textpos % ((DISP_W / CHAR_W) * (DISP_H/8)) == ((DISP_W / CHAR_W) * (DISP_H/8))-1)
	// 	{
	// 		delay(200);
	// 	}
	// 	delay(1000);
	// 	textpos++;
	// }

	//fb_set_pixel_direct(10,10, 1);

	for( ;; )
	{
		//printf(pcTextForTask4);
	}
}
