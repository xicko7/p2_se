#include "includes/MKL46Z4.h"

#define sleep 1500000
#define BUTTON_MASK 0x8u

void init_button()
{
	SIM_COPC = 0;					   // Deshabilitar watchdog
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; // Habilitar reloxo

	PORTC_PCR3 = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // GPIO + PE + PS
	GPIOC_PDDR &= ~(1 << 3);											// Input
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

void led_red_toggle()
{
	GPIOE_PTOR = (1 << 29);
}

int delay()
{
	/*Devolve as iteracións restantes para completar o bucle*/
	volatile int i, aux;

	for (i = 0; i < sleep; i++)
	{
		aux = GPIOC_PDIR & (BUTTON_MASK);
		if (!aux)
		{
			return (sleep - i);
		}
	}
	return 0;
}

int main(void)
{
	led_red_init();
	led_green_init();
	init_button();

	int green_red = 0, espera; // Empeza co verde
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
		// Espera o tempo que se saltou en delay()
		espera = delay();
		for (int i = 0; i < espera; i++)
		{
			// Se o bucle se interrompiu antes de tempo:
			if (i == 0)
			{
				green_red = !green_red;
				led_red_toggle();
				led_green_toggle();
			}
		}
	}

	return 0;
}
