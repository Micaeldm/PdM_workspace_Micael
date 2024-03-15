/*
 * API_delay.c
 *
 *  Created on: Mar 13, 2024
 *      Author: micael
 */

#include <API_delay.h>

void delayInit(delay_t *delay, tick_t duration) {
  	delay->duration = duration;
  	delay->running = false;
  }

 bool_t delayRead( delay_t * delay ){

	 tick_t diff=0;


	 if(!delay->running){

		  delay->startTime=HAL_GetTick(); //se asigna el valor cada 1mms
		  delay->running = true;

		 // return false;
	  }

	 diff=(HAL_GetTick() - delay->startTime);

	 if (diff>= delay->duration) {

			delay->running = false;

			return true;
		}
		  else
			return false;
	  }


 void delayWrite(delay_t *delay, tick_t duration) {
 	delay->duration = duration;
 }

