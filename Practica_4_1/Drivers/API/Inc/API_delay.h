/*
 * API_delay.h
 *
 *  Created on: Mar 13, 2024
 *      Author: micael
 */

#ifndef API_API_DELAY_H_
#define API_API_DELAY_H_

#include <stdio.h>
//#include <stm32f4xx_hal.h>		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal.h"
#include <stdbool.h>


typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );




#endif /* API_API_DELAY_H_ */
