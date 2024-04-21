/*
 * API_LCD_port.h
 *
 *  Created on: Apr 19, 2024
 *      Author: micael
 */

#ifndef API_INC_API_LCD_PORT_H_
#define API_INC_API_LCD_PORT_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
//#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdbool.h>
#define LCD_ADDRESS 	0x4E
#define  Size1  		4
#define EN 				(1<<2)
#define BL 				(1<<3)
#define W 				1
#define _F0				0xF0
#define _4				4
#define time 			100

void Enviar4bitWrite(char data1,bool comando);




#endif /* API_INC_API_LCD_PORT_H_ */
