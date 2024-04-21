/*
 * GPIO.h
 *
 *  Created on: Apr 1, 2024
 *      Author: micael
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

#include "main.h"
#include <stdio.h>
#include <stm32f4xx_hal.h>		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal.h"
#include <stdbool.h>

typedef bool bool_t;
typedef bool bool_t1;

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void GPIO_Init(void);
bool_t ButtonGet_1();
bool_t ButtonGet_2();
bool_t ButtonGet_3();
bool_t ButtonGet_4();
void Device_Cool();
void Device_Heat();

#endif /* API_INC_API_GPIO_H_ */
