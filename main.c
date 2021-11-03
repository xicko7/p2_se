#include "includes/MKL46Z4.h"

void delay(void)
{
	volatile int i;

	for (i = 0; i < 10000; i++);
}

void led_green_init()
{
	SIM_COPC = 0; //Deshabilitar reloxo
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; //Habilitar reloxo no porto 5
	PORTD_PCR5 = PORT_PCR_MUX(1); //GPIO
	GPIOD_PDDR |= (1 << 5);
	GPIOD_PSOR = (1 << 5);
}

void led_green_toggle()
{
	GPIOD_PTOR = (1 << 5);
}

void led_red_init()
{
	SIM_COPC = 0;
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE_PCR29 = PORT_PCR_MUX(1);
	GPIOE_PDDR |= (1 << 29);
	GPIOE_PSOR = (1 << 29);
}

void led_red_toggle(void)
{
	GPIOE_PTOR = (1 << 29);
}

int main(void)
{
	led_red_init();
	led_green_init();

	//int button = 1, greenon = 0, redon = 0;
	//O primeiro toggle encende os leds
	while (1) {
		//if (button)
			led_red_toggle();
		//else
			led_green_toggle();
		delay();
	}

	return 0;
}

