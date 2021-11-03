#include "includes/MKL46Z4.h"

int delay(void)
{
	/*Devolve 1 se se pulsou o botón durante a espera e 0 en caso contrario*/
	volatile int i;

	for (i = 0; i < 10000; i++){
		if (check_button())
			return 1;
	}
	return 0;
}

void led_green_init()
{
	SIM_COPC = 0; //Deshabilitar reloxo
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; //Habilitar reloxo no porto 5
	PORTD_PCR5 = PORT_PCR_MUX(1); //GPIO
	GPIOD_PDDR |= (1 << 5);
	GPIOD_PSOR = (1 << 5);
}

int check_button(){
	return GPIOC_PDIR;
}

void init_button()
{
	SIM_COPC = 0; //Deshabilitar reloxo
	PORTC_PCR3 = PORT_PCR_MUX(1); //GPIO
	GPIOE_PDDR |= (1 << 73);
	GPIOE_PSOR = (1 << 73);
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

	int button = 1, red_green = 0;
	//O primeiro toggle encende o led
	while (1) {
		if (red_green)
			led_red_toggle();
		else
			led_green_toggle();
		red_green = delay() ? !red_green : red_green;
	}

	return 0;
}

