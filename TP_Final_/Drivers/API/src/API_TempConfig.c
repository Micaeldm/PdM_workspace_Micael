/*
 * API_Teclado.c
 *
 *  Created on: Apr 7, 2024
 *      Author: micael
 */

#include <API_AHT10.h>
#include <API_AHT10_MEF.h>
#include <API_LCD_i2c.h>
#include <API_delay.h>
#include <API_debounce.h>
#include <API_AHT10_MEF.h>
#include <API_GPIO.h>
#include <API_TempConfig.h>
#include <API_uart.h>

#define tempmin                  0.0
#define tempmax                 28.0
#define res_temp                0.5

typedef float float_t;
typedef int int_t;

typedef enum {

	CONF_TEMPMIN, CONF_TEMPNORMAL, CONF_TEMPMAX, SALIDA,

} TECLADO;

static TECLADO ESTADO = CONF_TEMPMIN;
conf_temp conf_T;
static bool_t flag = true;
static float_t data[3] = { 0 };
static int_t data1 = 1;

char cadena1[30]={0};
	    char cadena2[30]={0};
	    char cadena3[20]={0};

	    char cadena5[20]={0};

static void conf_temperatura(uint8_t flag1);

void Conf_update_Uart() {




			printf("\033[2JIngrese los Valores de Temperatura Formato xx,xx,xx,0 donde 0-->Exit\n"
									"Temp MinU:\nn"
									"Temp NormalU:\n"
									"Temp MaxU:\n");
			scanf("%f,%f,%f,%d", &data[0], &data[1], &data[2], &data1);

	do {



		if (data1 == '\0')
			data1 = 0;

		if (data[0] != '\0' && data[1] != '\0' && data[2] != '\0') {

			if (data[0] >= tempmin && data[0] < tempmax) {
				//conf_T.temp_min = conf_T.temp_min + 1;
				conf_T.temp_min = data[0];

			}

			if (data[1] >= tempmin && data[1] < tempmax) {
				//conf_T.temp_min = conf_T.temp_min + 1;
				conf_T.temp_normal = data[1];
				//scanf("%f",&conf_T.temp_min);
			}
			if (data[2] >= tempmin && data[2] < tempmax) {
				//conf_T.temp_min = conf_T.temp_min + 1;
				conf_T.temp_max = data[2];
				//scanf("%f",&conf_T.temp_min);
			}

			/*printf("\033[2J"); //borra la pantalla en la terminal coolterm

			 printf("Temp Min:%0.1f <--\n", conf_T.temp_min);
			 printf("Temp Normal:%0.1f\n", conf_T.temp_normal);
			 printf("Temp Max:%0.1f\n\r", conf_T.temp_max);*/

			printf("\033[2JTemp MinU:%0.1f\n"
					"Temp NormalU:%0.1f\n"
					"Temp MaxU:%0.1f \n", conf_T.temp_min, conf_T.temp_normal,
					conf_T.temp_max);
			sprintf(cadena1,"Temp Min:%0.1f",conf_T.temp_min);
			sprintf(cadena2,"Temp Normal:%0.1f",conf_T.temp_normal);
			sprintf(cadena3,"Temp Max:%0.1f",conf_T.temp_max);
			Lcd_Write_String(cadena1,2,1);
			Lcd_Write_String(cadena2,3,1);
			Lcd_Write_String(cadena3,4,1);

		}
	} while (data1 == 1);
}

void Conf_update() {

	uint8_t flag_next = 0;
	printf("\033[2J");
	printf("\033[2J Temp Min:\n"
			"Temp Normal:\n"
			"Temp Max:\n");
	Lcd_Clear();
	Lcd_Write_String("Sensor AHT10",1,3);
	Lcd_Write_String("Temp Min:",2,1);
	Lcd_Write_String("Temp Normal:",3,1);
	Lcd_Write_String("Temp Max:",4,1);

	do {

		switch (ESTADO) {

		case CONF_TEMPMIN:
			flag_next = 1;

			conf_temperatura(flag_next);

			flag_next = 2;

			ESTADO = CONF_TEMPNORMAL;

			break;

		case CONF_TEMPNORMAL:

			conf_temperatura(flag_next);

			flag_next = 3;

			ESTADO = CONF_TEMPMAX;

			break;

		case CONF_TEMPMAX:
			conf_temperatura(flag_next);

			ESTADO = SALIDA;

			break;

		case SALIDA:
			if (conf_T.temp_normal > conf_T.temp_min
					&& conf_T.temp_normal < conf_T.temp_max){
				flag = false;
			Lcd_Clear();
			Lcd_Write_String("Sensor AHT10",1,3);
			}

			else {
				printf(
						"\033[2J Error!! vuelva a ingresar los datos nuevamente Temp Min < Temp Normal < Temp Max\n");
				ESTADO = CONF_TEMPMIN;
			}
			break;

		default:
			//Si algo modificó la variable estadoActual
			// a un estado no válido llevo la MEF a un
			// lugar seguro, por ejemplo, la reinicio:
			//controlDeErrores();
			ESTADO = CONF_TEMPMIN;

			break;

		}

	}

	while (flag == true);
}

static void conf_temperatura(uint8_t flag1) {

	do {
		debounceFSM_update();

		if (readKey_Up()) {

			if (flag1 == 1) {

				if (conf_T.temp_min >= tempmin && conf_T.temp_min < tempmax) {
					conf_T.temp_min = conf_T.temp_min + res_temp;
					printf("\033[2J");
					printf("\033[2JTemp Min:%0.1f <--\n"
							"Temp Normal:%0.1f\n"
							"Temp Max:%0.1f\n", conf_T.temp_min,
							conf_T.temp_normal, conf_T.temp_max);
					 sprintf(cadena1,"Temp Min:%0.1f",conf_T.temp_min);
					// sprintf(cadena2,"Temp Normal:%0.1f",conf_T.temp_normal);
					// sprintf(cadena3,"Temp Max:%0.1f",conf_T.temp_max);
					 Lcd_Write_String(cadena1,2,1);
					// Lcd_Write_String(cadena2,3,1);
					 //Lcd_Write_String(cedena3,4,1);

				}

			}

			if (flag1 == 2) {
				if (conf_T.temp_normal >= tempmin
						&& conf_T.temp_normal < tempmax) {
					conf_T.temp_normal = conf_T.temp_normal + res_temp;
					printf("\033[2J");
					printf("\033[2JTemp Min:%0.1f \n"
							"Temp Normal:%0.1f <--\n"
							"Temp Max:%0.1f \n", conf_T.temp_min,
							conf_T.temp_normal, conf_T.temp_max);
					 sprintf(cadena2,"Temp Normal:%0.1f",conf_T.temp_normal);
					 Lcd_Write_String(cadena2,3,1);

				}
			}

			if (flag1 == 3) {
				if (conf_T.temp_max >= tempmin && conf_T.temp_max < tempmax) {
					conf_T.temp_max = conf_T.temp_max + res_temp;
					printf("\033[2J");
					printf("\033[2JTemp Min:%0.1f\n"
							"Temp Normal:%0.1f\n"
							"Temp Max:%0.1f<--\n", conf_T.temp_min,
							conf_T.temp_normal, conf_T.temp_max);
					sprintf(cadena3,"Temp Max:%0.1f",conf_T.temp_max);
					 Lcd_Write_String(cadena3,4,1);

				}
			}

		}

		if (readKey_Down()) {
			//Lcd_Set_Cursor(4, 2);
			//Lcd_Send_String("button_2");
			if (flag1 == 1) {
				if (conf_T.temp_min > tempmin && conf_T.temp_min <= tempmax) {
					conf_T.temp_min = conf_T.temp_min - res_temp;
					printf("\033[2J");
					printf("\033[2JTemp Min:%0.1f <--\n"
							"Temp Normal:%0.1f\n"
							"Temp Max:%0.1f \n", conf_T.temp_min,
							conf_T.temp_normal, conf_T.temp_max);
					 sprintf(cadena1,"Temp Min:%0.1f",conf_T.temp_min);
					 Lcd_Write_String(cadena1,2,1);

				}
			}

			if (flag1 == 2) {
				if (conf_T.temp_normal > tempmin
						&& conf_T.temp_normal <= tempmax) {
					conf_T.temp_normal = conf_T.temp_normal - res_temp;
					printf("\033[2J");
					printf("\033[2JTemp Min:%0.1f\n"
							"Temp Normal:%0.1f <--\n"
							"Temp Max:%0.1f \n", conf_T.temp_min,
							conf_T.temp_normal, conf_T.temp_max);
					 sprintf(cadena2,"Temp Normal:%0.1f",conf_T.temp_normal);
					 Lcd_Write_String(cadena2,3,1);
				}
			}

			if (flag1 == 3) {
				if (conf_T.temp_max > tempmin && conf_T.temp_max <= tempmax) {
					conf_T.temp_max = conf_T.temp_max - res_temp;
					printf("\033[2J");
					printf("\033[2JTemp Min:%0.1f\n"
							"Temp Normal:%0.1f\n"
							"Temp Max:%0.1f<--\n", conf_T.temp_min,
							conf_T.temp_normal, conf_T.temp_max);
					sprintf(cadena3,"Temp Max:%0.1f",conf_T.temp_max);
					Lcd_Write_String(cadena3,4,1);
				}
			}

		}

	} while (!readKey_enter());

}

