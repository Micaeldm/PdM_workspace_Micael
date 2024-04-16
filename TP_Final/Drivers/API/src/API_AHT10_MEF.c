/*
 * API_AHT10_MEF.c
 *
 *  Created on: Apr 6, 2024
 *      Author: micael
 */

#include <API_AHT10.h>
#include <API_AHT10_MEF.h>

#include <API_delay.h>
#include <API_debounce.h>
#include <API_AHT10_MEF.h>
#include <API_GPIO.h>

#define   Time_SENSOR 500 // TIEMPO DE MUESTRO DEL VALOR DE AHT10
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
	while (1) {
	}
}

static delay_t t5;

static TEMPState_t EstadoActual;
//static bool_t btnPres; //boton presionado
//static bool_t btnPres1; //boton presionado
//static bool_t btnPres2; //boton presionado

void TEMPFSM_init(conf_temp *conf_T) {

	if (conf_T == NULL)
		Error_Handler();

	EstadoActual = TEMP_INICIAL;
	//EstadoActual=DEFAULT;
	//printf("\033[2Jinicio\n");
	//printf("Temp_Init:%0.1f\n\r",AHT10_Temp() );
	temp_N_min = (conf_T->temp_normal - conf_T->temp_min);
	temp_N_max = (conf_T->temp_max - conf_T->temp_normal);
	delayInit(&t5, Time_SENSOR);

}

void TEMPFSM_update(conf_temp *conf_T) {

	switch (EstadoActual) {

	case TEMP_INICIAL:
		//printf("\033[2Jinicio\n");
		delayRead(&t5);
		if (AHT10_Temp() < conf_T->temp_min) { //&& AHT10_Temp() < conf_T->temp_normal)
			EstadoActual = TEMP_BAJA;
			temp_low_flag = true;

			/*printf("Temp1:%0.1f\n\r", conf_T->temp_max);
			 printf("Temp2:%0.1f\n\r", conf_T->temp_normal);
			 printf("Temp3:%0.1f\n\r", conf_T->temp_min);*/
			//printf("Temp:%0.1f\n\r", conf_T->temp_min);
		}

		if (AHT10_Temp() <= (conf_T->temp_normal + temp_N_max)
				&& AHT10_Temp() >= (conf_T->temp_normal - temp_N_min)) {
			EstadoActual = TEMP_NORMAL;
			temp_high_flag = false;
			temp_low_flag = false;
			/*printf("Temp4:%0.1f\n\r", conf_T->temp_max);
			 printf("Temp5:%0.1f\n\r", conf_T->temp_normal);
			 printf("Temp6:%0.1f\n\r", conf_T->temp_min);*/
		}
		if (AHT10_Temp() > conf_T->temp_max) { //|| AHT10_Temp() > (conf_T->temp_normal + 1)
			EstadoActual = TEMP_ALTA;
			temp_high_flag = true;
			/*	printf("Temp7%0.1f\n\r", conf_T->temp_max);
			 printf("Temp8:%0.1f\n\r", conf_T->temp_normal);
			 printf("Temp9:%0.1f\n\r", conf_T->temp_min);*/

		}

		break;

	case TEMP_BAJA:

		if (delayRead(&t5)) { // se cumplio los 200 ms

			//temp_state = AHT10_Temp();
			printf("\033[2JTemp Baja\n"
					"Temp:%0.1f\n", AHT10_Temp());
			//delayRead(&t5); //comienza de nuevo el timer

			//buttonPressed1(); //se activa para calefaccionar el ambiente
			if (AHT10_Temp() < conf_T->temp_min) {
				EstadoActual = TEMP_BAJA;
				if (temp_low_flag) {

					temp_low_flag = false;
					temp_low = true;
				}

				if (AHT10_Temp() >= (conf_T->temp_normal - temp_N_min)) {

					EstadoActual = TEMP_NORMAL;
					if (!temp_low_flag) {

						temp_low_flag = true;
						temp_low = true;
					}

				}

				//BSP_LED_On(LED2);
				//BSP_LED_Off(LED3);
				BSP_LED_Off(LED1);

				delayRead(&t5);
			}
			break;

			case TEMP_NORMAL:

			if (delayRead(&t5)) { // se cumplio los 40 ms
				printf("\033[2J  Temp Normal\n Temp:%0.1f\n", AHT10_Temp());

				if (AHT10_Temp() > (conf_T->temp_normal + temp_N_max)) {
					EstadoActual = TEMP_ALTA;
					temp_high_flag = true;
				}

				if (AHT10_Temp() < (conf_T->temp_normal - temp_N_min)) {
					EstadoActual = TEMP_BAJA;
					temp_low_flag = true;
				}

				//if (AHT10_Temp() < (conf_T->temp_normal + 1) )//&& AHT10_Temp() > (conf_T->temp_normal - 1)
				//	EstadoActual = TEMP_NORMAL;
				//buttonPressed1(); //se desactiva para calefaccionar el ambiente
				//BSP_LED_On(LED2);
				BSP_LED_Off(LED3);
				BSP_LED_On(LED1);
				BSP_LED_Off(LED2);

				delayRead(&t5);

			}

			//BSP_LED_On(LED2);

			//delayWrite(&t1, Time_AntiRebote);
			break;
			case TEMP_ALTA:

			if (delayRead(&t5)) {
				printf("\033[2JTemp Alta\n"
						"Temp:%0.1f\n", AHT10_Temp());
				//	temp_state = AHT10_Temp();

				//comienza de nuevo el timer

				if (AHT10_Temp() > conf_T->temp_max) {
					EstadoActual = TEMP_ALTA;
					if (temp_high_flag) {

						temp_high_flag = false;
						temp_high = true;
					}
				}

				if (AHT10_Temp() <= (conf_T->temp_normal + temp_N_max)) {
					EstadoActual = TEMP_NORMAL;
					if (!temp_high_flag) {

						temp_high_flag = true;
						temp_high = true;
					}
				}

				//BSP_LED_Off(LED2);
				//buttonReleased1();
				BSP_LED_Off(LED1); //
				//BSP_LED_On(LED3); //Enfriamos el ambiente para llevarlo a la temperatura normal
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
}

void buttonPressed1() {

	BSP_LED_On(LED2);
}

void buttonReleased1() {
	BSP_LED_Off(LED2);
}

bool_t Detecto_TempHigh() {

	if (temp_high) {
		temp_high = false;
		return true;
	}

	else
		return false;
}

bool_t Detecto_TempLow() {

	if (temp_low) {
		temp_low = false;
		return true;
	} else
		return false;
}


