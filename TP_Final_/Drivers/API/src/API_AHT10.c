/*
 * AHT10.c
 *
 *  Created on: Apr 1, 2024
 *      Author: micael
 */
#include <API_AHT10.h>

#define time 			100
#define size2 			3
#define size3 			6
#define Delay_100ms 	100
#define AHT10_ADRESS (0x38 << 1) // 0b1110000; Adress[7-bit]Wite/Read[1-bit]

static uint8_t DATA_RX[size3];
static uint32_t AHT10_ADC;
static float Temperature;
static const float valor2exp20 = 1048576.00;
static const float valor200 = 200.00;
static const float valor50 = 50.00;
static const uint32_t shift_8 = 8;
static const uint32_t shift_16 = 16;
static const uint32_t dec_15 = 15;

//int size= sizeof DATA_RX/ sizeof DATA_RX[0];
static uint8_t AHT10_Config[size2] =
    {
    0xAC, 0x33, 0x00
    }; //configuracion

extern I2C_HandleTypeDef hi2c2;

HAL_StatusTypeDef returnValue1;

static void Error_Handler(void);

static void Error_Handler(void)
{

	BSP_LED_On(LED1);
	BSP_LED_On(LED2);
	BSP_LED_On(LED3);
	while (1)
	{
	}
}

static void DelayAHt10(uint32_t Delay_ms);

static void DelayAHt10(uint32_t Delay_ms)
{
	HAL_Delay(Delay_ms);
}

float AHT10_Temp()
{

	/* Convert to Temperature in °C */
	returnValue1 = HAL_I2C_Master_Transmit(&hi2c2, AHT10_ADRESS,
			(uint8_t*) AHT10_Config, sizeof(AHT10_Config), time);
	if (returnValue1 != HAL_OK)
	{
		Error_Handler();
	}

	DelayAHt10(Delay_100ms);
	HAL_I2C_Master_Receive(&hi2c2, AHT10_ADRESS, (uint8_t*) DATA_RX,
			sizeof(DATA_RX), time);

	AHT10_ADC = (((uint32_t) DATA_RX[3] & dec_15) << shift_16) | ((uint32_t) DATA_RX[4] << shift_8) | DATA_RX[5];
	Temperature = (float) (AHT10_ADC * valor200 / valor2exp20) - valor50;


	return Temperature;
}


