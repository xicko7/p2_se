#include "includes/MKL46Z4.h"

int check_button()
{
	return GPIOC_PDIR;
}

void init_button()
{
	SIM_COPC = 0; // Deshabilitar reloxo
	PORTC_PCR3 = PORT_PCR_MUX(1);
	PORTC_PCR3 |= ((uint32_t)(((uint32_t)(1)) << PORT_PCR_PE_SHIFT)) & PORT_PCR_PE_MASK;
	PORTC_PCR3 |= ((uint32_t)(((uint32_t)(0)) << PORT_PCR_PS_SHIFT)) & PORT_PCR_PS_MASK;
	GPIOC_PDDR &= (0 << 5); // Input
	GPIOC_PSOR = (0 << 5);
}

void led_green_init()
{
	SIM_COPC = 0;					   // Deshabilitar reloxo
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; // Habilitar reloxo no porto 5
	PORTD_PCR5 = PORT_PCR_MUX(1);	   // GPIO
	GPIOD_PDDR |= (1 << 5);
	GPIOD_PSOR = (1 << 5);
}

void led_green_toggle(void)
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

int delay(void)
{
	/*Devolve 1 se se pulsou o botón durante a espera e 0 en caso contrario*/
	volatile int i, res = 0;

	for (i = 0; i < 1000000; i++)
	{
		// if (check_button() /*& !(i % 1000)*/)
		// {
		// 	led_red_toggle();
		// 	led_green_toggle();
		// 	res = !res;
		// }
	}
	return res;
}

int main(void)
{
	led_red_init();
	led_green_init();
	//init_button();

	int green_red = 0; // Empeza co verde
	// O primeiro toggle encende o led
	while (1)
	{
		if (green_red)
		{
			led_red_toggle();
		}
		else
		{
			led_green_toggle();
		}
		// Se o botón é pulsado cambia green_red
		green_red = delay() ? !green_red : green_red;
	}

	return 0;
}
