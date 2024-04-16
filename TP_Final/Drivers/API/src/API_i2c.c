/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
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
#include <API_i2c.h>

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

static void Error_Handler(void);

static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}


/* I2C1 init function */
void I2C_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	 GPIO_InitTypeDef GPIO_InitStruct2 = {0};
    /* I2C1 clock enable */
   __HAL_RCC_I2C1_CLK_ENABLE(); //IMPORTANTE
   __HAL_RCC_I2C2_CLK_ENABLE(); //IMPORTANTE

   __HAL_RCC_GPIOB_CLK_ENABLE();//IMPORTANTE

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;

  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&hi2c1);
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

     GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
     GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
     GPIO_InitStruct.Pull = GPIO_NOPULL;
     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
     GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);




     /* USER CODE END I2C1_Init 1 */
      hi2c2.Instance = I2C2;
      hi2c2.Init.ClockSpeed = 100000;
      hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
      hi2c2.Init.OwnAddress1 = 0;
      hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
      hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
      hi2c2.Init.OwnAddress2 = 0;
      hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
      hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
      HAL_I2C_Init(&hi2c2);
      if (HAL_I2C_Init(&hi2c2) != HAL_OK)
      {
        Error_Handler();
      }
      /* USER CODE BEGIN I2C1_Init 2 */

      /* USER CODE END I2C1_Init 2 */

         GPIO_InitStruct2.Pin = GPIO_PIN_10|GPIO_PIN_11;
         GPIO_InitStruct2.Mode = GPIO_MODE_AF_OD;
         GPIO_InitStruct2.Pull = GPIO_NOPULL;
         GPIO_InitStruct2.Speed = GPIO_SPEED_FREQ_LOW;
         GPIO_InitStruct2.Alternate = GPIO_AF4_I2C2;
         HAL_GPIO_Init(GPIOB, &GPIO_InitStruct2);

}

/*void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle) //INICIALIZA
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {


    __HAL_RCC_GPIOB_CLK_ENABLE();


    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    __HAL_RCC_I2C1_CLK_ENABLE(); //IMPORTANTE



  }
}*/

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle) //DESINICIALIZA
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
