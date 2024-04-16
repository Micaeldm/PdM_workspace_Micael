/*
 * AHT10.c
 *
 *  Created on: Apr 1, 2024
 *      Author: micael
 */
#include <API_AHT10.h>

#define time 100
#define AHT10_ADRESS (0x38 << 1) // 0b1110000; Adress[7-bit]Wite/Read[1-bit]

static uint8_t DATA_RX[6];
static uint32_t AHT10_ADC;
static float Temperature;
//static float Humidity;
static uint8_t AHT10_Config[3] = {0xAC, 0x33, 0x00}; //configuracion

extern I2C_HandleTypeDef hi2c2;

HAL_StatusTypeDef returnValue1;

static void Error_Handler(void);

static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

/*void AHT10_Init(){

	returnValue1=HAL_I2C_Master_Transmit(&hi2c2, AHT10_ADRESS, (uint8_t*)AHT10_Config,3, time);
	if(returnValue1 != HAL_OK){
			Error_Handler();
		}

	HAL_Delay(100); // Delay must be > 75 ms
	HAL_I2C_Master_Receive(&hi2c2, AHT10_ADRESS, (uint8_t*)DATA_RX, 6,time);
}*/

float AHT10_Temp(){

	/* Convert to Temperature in °C */
	returnValue1=HAL_I2C_Master_Transmit(&hi2c2, AHT10_ADRESS, (uint8_t*)AHT10_Config,3, time);
		if(returnValue1 != HAL_OK){
				Error_Handler();
			}

		HAL_Delay(100); // Delay must be > 75 ms
	    HAL_I2C_Master_Receive(&hi2c2, AHT10_ADRESS, (uint8_t*)DATA_RX, 6,time);
		AHT10_ADC = (((uint32_t) DATA_RX[3] & 15) << 16) | ((uint32_t) DATA_RX[4] << 8) | DATA_RX[5];
		Temperature = (float) (AHT10_ADC * 200.00 / 1048576.00) - 50;

		return Temperature;
}


/*float AHT10_Humidity(){



	    AHT10_ADC = ((uint32_t) DATA_RX[1] << 12)	| ((uint32_t) DATA_RX[2] << 4) | (DATA_RX[3] >> 4);
		Humidity = (float) (AHT10_ADC* 100.00 / 1048576.00);

		return Humidity;
}*/
