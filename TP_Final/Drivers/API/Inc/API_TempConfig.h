/*
 * API_Teclado.h
 *
 *  Created on: Apr 7, 2024
 *      Author: micael
 */

#ifndef API_INC_API_TEMPCONFIG_H_
#define API_INC_API_TEMPCONFIG_H_

#include <stdio.h>
//#include <stm32f4xx_hal.h>		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal.h"
#include <stdbool.h>

void Conf_update();
void Conf_update_Uart();


#endif /* API_INC_API_TEMPCONFIG_H_ */
