/*
 * AHT10.h
 *
 *  Created on: Apr 1, 2024
 *      Author: micael
 */

#ifndef API_INC_API_AHT10_H_
#define API_INC_API_AHT10_H_

#include <API_i2c.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal.h"
#include <stdbool.h>

void AHT10_Init();
float AHT10_Temp();
float AHT10_Humidity();

#endif /* API_INC_API_AHT10_H_ */
