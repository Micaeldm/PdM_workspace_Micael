/*
 * API_debounce.c
 *
 *  Created on: Mar 22, 2024
 *      Author: micael
 */

#include <API_delay.h>
#include <API_debounce.h>
#include <API_GPIO.h>

#define   Time_AntiRebote 10

typedef enum {
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

static delay_t t1;

static debounceState_t EstadoActual;
static bool_t btnPress; //boton presionado
static bool_t btnPress1; //boton presionado
static bool_t btnPress2; //boton presionado

void debounceFSM_init() {
	EstadoActual = BUTTON_UP;
	delayInit(&t1, Time_AntiRebote);
}

void debounceFSM_update() {

	switch (EstadoActual) {

	case BUTTON_UP:

		if ((ButtonGet_1() || ButtonGet_2() || ButtonGet_3() || ButtonGet_4())) { //presiono el boton
			//if ( button_1()) {  //presiono el boton
			delayRead(&t1);
			EstadoActual = BUTTON_FALLING;
		}
		break;

	case BUTTON_FALLING:

		if (delayRead(&t1)) { // se cumplio los 40 ms
			if ((ButtonGet_1() || ButtonGet_2()
					|| ButtonGet_3() || ButtonGet_4())) { //SI ESTA PRESIONADO PRENDO EL LED
				//if (button_1()) {  //SI ESTA PRESIONADO PRENDO EL LED
				//delayRead(&t1);
				//BSP_LED_On(LED1);

				buttonPressed();
				if (ButtonGet_1()) {
					btnPress = true;
				}
				if (ButtonGet_2()) {
					btnPress1 = true;
				}
				if (ButtonGet_3()) {
					btnPress2 = true;
				}

				EstadoActual = BUTTON_DOWN;
			} else {
				EstadoActual = BUTTON_UP;

			}
		}
		break;

	case BUTTON_DOWN:
		if (!(  ButtonGet_1() || ButtonGet_2()
				|| ButtonGet_3() || ButtonGet_4())) { // el pulsador esta en estado bajo
			//if ( !button_1()) { // el pulsador esta en estado bajo
			delayRead(&t1); //comienza el timer

			EstadoActual = BUTTON_RAISING;
		}

		//delayWrite(&t1, Time_AntiRebote);
		break;
	case BUTTON_RAISING:

		if (delayRead(&t1)) {
			if (!(ButtonGet_1() || ButtonGet_2()
					|| ButtonGet_3() || ButtonGet_4())) {
				//	if ( !button_1()) {
				//delayRead(&t1);
				//BSP_LED_Off(LED1);
				buttonReleased();

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

void buttonPressed() {

	BSP_LED_On(LED1);
}

void buttonReleased() {
	BSP_LED_Off(LED1);
}

bool_t readKey_Up() {

	if (btnPress) {
		btnPress = false;
		return true;
	} else
		return false;

}

bool_t readKey_Down() {

	if (btnPress1) {
		btnPress1 = false;
		return true;
	} else
		return false;

}

bool_t readKey_enter() {

	if (btnPress2) {
		btnPress2 = false;
		return true;
	} else
		return false;

}
