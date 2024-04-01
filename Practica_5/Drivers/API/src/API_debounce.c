/*
 * API_debounce.c
 *
 *  Created on: Mar 22, 2024
 *      Author: micael
 */

#include <API_delay.h>
#include <API_debounce.h>

#define   Time_AntiRebote 40


typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;


static  delay_t t1;

static debounceState_t EstadoActual;
static bool_t btnPress; //boton presionado
static bool_t flanco_A=false; //boton presionado
static bool_t flanco_D=false; //boton presionado

void debounceFSM_init() {
	EstadoActual = BUTTON_UP;
	delayInit(&t1, Time_AntiRebote);
}



void debounceFSM_update() {

	switch (EstadoActual) {

	case BUTTON_UP:

		if (BSP_PB_GetState(BUTTON_USER)) {  //presiono el boton
			delayRead(&t1);
			EstadoActual = BUTTON_FALLING;
		}
		break;

	case BUTTON_FALLING:

		if (delayRead(&t1)) { // se cumplio los 40 ms
			if (BSP_PB_GetState(BUTTON_USER)) {  //SI ESTA PRESIONADO PRENDO EL LED
				//delayRead(&t1);
				//BSP_LED_On(LED1);
				buttonPressed();
				flanco_D=true;
				//flanco_A=false;
				btnPress=true;
				EstadoActual = BUTTON_DOWN;
			} else {
				EstadoActual = BUTTON_UP;

			}
		}
		break;

	case BUTTON_DOWN:
		if (!BSP_PB_GetState(BUTTON_USER)) { // el pulsador esta en estado bajo
			delayRead(&t1); //comienza el timer
			readKey();
			EstadoActual = BUTTON_RAISING;
		}

		//delayWrite(&t1, Time_AntiRebote);
		break;
	case BUTTON_RAISING:

		if (delayRead(&t1)) {
			if (!BSP_PB_GetState(BUTTON_USER)) {
				//delayRead(&t1);
				//buttonPressed();
				BSP_LED_Off(LED1);
				btnPress=true;
				flanco_A=true;
				//flanco_D=false;
				EstadoActual = BUTTON_UP;
			} else
				EstadoActual = BUTTON_DOWN;

			break;

			default:
			//Si algo modificó la variable estadoActual
			// a un estado no válido llevo la MEF a un
			// lugar seguro, por ejemplo, la reinicio:
			//controlDeErrores();
			debounceFSM_init();

			break;

		}
	}

}

 void buttonPressed(){

	BSP_LED_On(LED1);
}

void buttonReleased(){
	BSP_LED_Off(LED1);
}

bool_t readKey()
{

	if(btnPress){
		btnPress=false;
		return true;
	}else
		return false;

}

bool_t  Detecto_flanco_A(){

	if(flanco_A){
		flanco_A=false;
		return true;
	}

	else
       return false;
}

bool_t  Detecto_flanco_D(){

	if(flanco_D){
		flanco_D=false;
		return true;
	}
	else
        return false;
}
