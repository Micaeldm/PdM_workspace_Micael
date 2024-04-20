/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <API_GPIO.h>

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/

#define PORT_E     GPIOE
#define PIN_E_10   GPIO_PIN_10
#define PIN_E_12   GPIO_PIN_12
#define PIN_E_14   GPIO_PIN_14
#define PIN_E_15   GPIO_PIN_15

#define GPIOD_CLK_EN   __HAL_RCC_GPIOD_CLK_ENABLE()
#define GPIOB_CLK_EN    __HAL_RCC_GPIOB_CLK_ENABLE()
#define GPIOE_CLK_EN    __HAL_RCC_GPIOE_CLK_ENABLE()


void GPIO_Init(void)
{


	GPIO_InitTypeDef GPIO_InitStructE = {0};


  /* GPIO Ports Clock Enable */
 // __HAL_RCC_GPIOD_CLK_ENABLE();
 // __HAL_RCC_GPIOB_CLK_ENABLE();
 // __HAL_RCC_GPIOE_CLK_ENABLE();
	GPIOD_CLK_EN;
	GPIOB_CLK_EN;
	GPIOE_CLK_EN;

  /*Configure GPIO pins : PA1 PA2 */
    GPIO_InitStructE.Pin = GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15;;
    GPIO_InitStructE.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructE.Pull = GPIO_PULLUP;
    GPIO_InitStructE.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(PORT_E , &GPIO_InitStructE);

}

bool_t ButtonGet_1(){

	//if(!HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10)){
		if(!HAL_GPIO_ReadPin(PORT_E ,PIN_E_10 )){
		return true;
	}


	return false;
}

bool_t ButtonGet_2(){

	//if(!HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12))
		if(!HAL_GPIO_ReadPin(PORT_E ,PIN_E_12 )){
		return true;
	}


	return false;
}

bool_t ButtonGet_3(){

	//if(!HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14))
		if(!HAL_GPIO_ReadPin(PORT_E ,PIN_E_14 )){
		return true;
	}


	return false;
}

bool_t ButtonGet_4(){

	//if(!HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_15))
		if(!HAL_GPIO_ReadPin(PORT_E ,PIN_E_15 )){
		return true;
	}


	return false;
}
/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
