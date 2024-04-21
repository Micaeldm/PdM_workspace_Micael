/*
 * API_AHT10_MEF.h
 *
 *  Created on: Apr 6, 2024
 *      Author: micael
 */

#ifndef API_INC_API_AHT10_MEF_H_
#define API_INC_API_AHT10_MEF_H_
#include <stdio.h>
//#include <stm32f4xx_hal.h>		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal.h"
#include <stdbool.h>


typedef bool bool_t;

typedef struct{

	float  temp_min;
	float  temp_normal;
	float  temp_max;


}conf_temp;

void TEMPFSM_init();
void TEMPFSM_update(conf_temp *conf_T);
void buttonPressed1();

void buttonReleased1();
bool_t  Detecto_TempHigh();
bool_t  Detecto_TempLow();




#endif /* API_INC_API_AHT10_MEF_H_ */
