/*
 * API_debounce.h
 *
 *  Created on: Mar 22, 2024
 *      Author: micael
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdio.h>
//#include <stm32f4xx_hal.h>		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal.h"
#include <stdbool.h>


typedef bool bool_t;

 void debounceFSM_init();
 void debounceFSM_update();
 void buttonPressed();

 void buttonReleased();

 // Devuelve true si se detecto una pulsacion del botón (flanco negativo).
 bool_t readKey();
 bool_t Detecto_flanco_D();
 bool_t Detecto_flanco_A();

//bool_t readKey();

#endif /* API_INC_API_DEBOUNCE_H_ */
