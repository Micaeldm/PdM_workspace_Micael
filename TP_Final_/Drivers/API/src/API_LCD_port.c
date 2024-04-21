/*
 * API_LCD_port.c
 *
 *  Created on: Apr 19, 2024
 *      Author: micael
 */
#include <API_i2c.h>

#include <API_LCD_port.h>





extern I2C_HandleTypeDef hi2c1;
HAL_StatusTypeDef returnValue;


static void Error_Handler(void);

static void Error_Handler(void)
{
	/* Turn LED2 on */
	BSP_LED_On(LED1);
	BSP_LED_On(LED2);
	BSP_LED_On(LED3);
	while (1)
	{
	}
}

void Enviar4bitWrite(char data1, bool comando)
{
	uint8_t data_t[Size1];
	char cmd = data1;
	char data = data1;
	if (comando) //envio comando
	{
		data_t[0] = (cmd & _F0) + EN + BL; //EN=1 Bl=1    |0x0C 1
		data_t[1] = (cmd & _F0) + BL;  //EN=0 Bl=1
		data_t[2] = ((cmd << _4) & _F0) + EN + BL; //EN=1 Bl=1 control=0    |0x0C 1
		data_t[3] = ((cmd << _4) & _F0) + BL; //EN=1 Bl=1 control=0    |0x0C 1
	}

	if (!comando) //envio datos
	{
		data_t[0] = (data & _F0) + EN + BL + W; //EN=1 Bl=1
		data_t[1] = (data & _F0) + BL + W;  //EN=0 Bl=1
		data_t[2] = ((data << _4) & _F0) + EN + BL + W; //EN=1 Bl=1 W=1 datos
		data_t[3] = ((data << _4) & _F0) + BL + W; //EN=1 Bl=1
	}

	returnValue = HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS,
			(uint8_t*) data_t, sizeof(Size1), time);
	if (returnValue != HAL_OK)
	{
		Error_Handler();

	}
}
