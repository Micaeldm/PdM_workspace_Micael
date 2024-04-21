/*
 * API_AHT10_MEF.c
 *
 *  Created on: Apr 6, 2024
 *      Author: micael
 */

#include <API_AHT10.h>
#include <API_AHT10_MEF.h>
#include <API_LCD_i2c.h>
#include <API_delay.h>
#include <API_debounce.h>
#include <API_AHT10_MEF.h>
#include <API_GPIO.h>

#define   Time_SENSOR 100 // TIEMPO DE MUESTRO DEL VALOR DE AHT10
#define   tamaño 40
//static float temp_state=0;
static float temp_N_max = 0;
static float temp_N_min = 0;
static bool_t temp_high;
static bool_t temp_low;
static bool_t temp_high_flag = false;
static bool_t temp_low_flag = false;

typedef enum {
	TEMP_INICIAL, TEMP_BAJA, TEMP_NORMAL, TEMP_ALTA, DEFAULT,
} TEMPState_t;

static void Error_Handler(void);

static void Error_Handler(void) {
	/* Turn LED2 on */
       BSP_LED_On(LED1);
       BSP_LED_On(LED2);
       BSP_LED_On(LED3);
	while (1) {
	}
}

static delay_t t5;
char cadena4[tamaño] = { 0 };
char cadena7[tamaño] = { 0 };
char cadena8[tamaño] = { 0 };

static TEMPState_t EstadoActual;


void TEMPFSM_init(conf_temp *conf_T)
{

	if (conf_T == NULL)
		Error_Handler();

	EstadoActual = TEMP_INICIAL;
	temp_N_min = (conf_T->temp_normal - conf_T->temp_min); //resto la temp normal con la temp min obtengo tolerancia min
	temp_N_max = (conf_T->temp_max - conf_T->temp_normal); //resto la temp maxima con la temp normal obtengo tolerancia max
	delayInit(&t5, Time_SENSOR);

}

void TEMPFSM_update(conf_temp *conf_T)
{

	switch (EstadoActual)
	{

		case TEMP_INICIAL:

			delayRead(&t5);
			if (AHT10_Temp() < conf_T->temp_min)
				{
					EstadoActual = TEMP_BAJA;
					temp_low_flag = true;
				}

			if (AHT10_Temp() <= (conf_T->temp_normal + temp_N_max) && AHT10_Temp() >= (conf_T->temp_normal - temp_N_min))
				{
					EstadoActual = TEMP_NORMAL;
					temp_high_flag = false;
					temp_low_flag = false;
				}

			if (AHT10_Temp() > conf_T->temp_max)
				{
					EstadoActual = TEMP_ALTA;
					temp_high_flag = true;
				}

			break;

		case TEMP_BAJA:

			if (delayRead(&t5))
				{ // se cumplio los 200 ms

					printf("\033[2JTemp Baja\n"
							"Temp:%0.1f\n", AHT10_Temp());
					sprintf(cadena4, "T:%0.2f", AHT10_Temp());
					Lcd_Write_String(cadena4, 2, 1);
					Lcd_Write_String("Temp Baja  ", 3, 1);

					if (AHT10_Temp() < conf_T->temp_min)
						{
							EstadoActual = TEMP_BAJA;
							if (temp_low_flag)
							{
								temp_low_flag = false;
								temp_low = true;
							}
						}
					if (AHT10_Temp() >= (conf_T->temp_normal - temp_N_min))
						{
							EstadoActual = TEMP_NORMAL;
							if (!temp_low_flag)
							{
								temp_low_flag = true;
								temp_low = true;
							}

						}
					BSP_LED_Off(LED1);
					delayRead(&t5);
				}
			break;

		case TEMP_NORMAL:

			if (delayRead(&t5))
				{ // se cumplio los 40 ms
					printf("\033[2J  Temp Normal\n Temp:%0.1f\n", AHT10_Temp());
					sprintf(cadena7, "T:%0.2f", AHT10_Temp());
					Lcd_Write_String(cadena7, 2, 1);
					Lcd_Write_String("Temp Normal", 3, 1);

					if (AHT10_Temp() > (conf_T->temp_normal + temp_N_max))
						{
							EstadoActual = TEMP_ALTA;
							temp_high_flag = true;
						}

					if (AHT10_Temp() < (conf_T->temp_normal - temp_N_min))
						{
							EstadoActual = TEMP_BAJA;
							temp_low_flag = true;
						}


					BSP_LED_On(LED1);

					delayRead(&t5);

				}
			break;

		case TEMP_ALTA:

			if (delayRead(&t5))
				{
					printf("\033[2JTemp Alta\n"
							"Temp:%0.1f\n", AHT10_Temp());
					sprintf(cadena8, "T:%0.2f", AHT10_Temp());
					Lcd_Write_String(cadena8, 2, 1);
					Lcd_Write_String("Temp Alta  ", 3, 1);

					if (AHT10_Temp() > conf_T->temp_max)
						{
							EstadoActual = TEMP_ALTA;
							if (temp_high_flag)
							{
								temp_high_flag = false; //porngo en falso y lo vuevolvo a leer en el proximo if para el toggle en la salida
								temp_high = true;
							}
						}

					if (AHT10_Temp() <= (conf_T->temp_normal + temp_N_max))
						{
							EstadoActual = TEMP_NORMAL;
							if (!temp_high_flag)
							{
								temp_high_flag = true;
								temp_high = true;
							}
						}
					BSP_LED_Off(LED1); //
					delayRead(&t5); //tiempo de muestro para obtener datos del AHT10
				}

			break;

		default:
			//Si algo modificó la variable estadoActual
			// a un estado no válido llevo la MEF a un
			// lugar seguro, por ejemplo, la reinicio:
			//controlDeErrores();
			TEMPFSM_init(conf_T);

			break;

	}
}

void buttonPressed1()
{

	BSP_LED_On(LED2);
}

void buttonReleased1()
{
	BSP_LED_Off(LED2);
}

bool_t Detecto_TempHigh()
{

	if (temp_high)
	{
		temp_high = false;
		return true;
	}
	else
		return false;
}

bool_t Detecto_TempLow()
{

	if (temp_low)
	{
		temp_low = false;
		return true;
	}
	else
		return false;
}


