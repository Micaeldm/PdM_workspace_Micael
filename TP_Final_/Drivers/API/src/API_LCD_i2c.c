#include <API_i2c.h>
#include <API_LCD_i2c.h>
#include <API_LCD_port.h>
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#define  Size0  4
bool comando = 1;



static void DelayLcd(uint32_t Delay_m);

static void DelayLcd(uint32_t Delay_m)
{
	HAL_Delay(Delay_m);
}



static void Lcd_Cmd(char cmd)
{

	comando = true;
	Enviar4bitWrite(cmd, comando);

}

static void Lcd_Char(char data)
{

	comando = false;
	Enviar4bitWrite(data, comando);

}

void Lcd_Init(void) {


	for (unsigned char i = 0; i < 3; i++)
	{
		Lcd_Cmd(inicializa);         //Inicializa
		DelayLcd(Delay_5);
	}

	DelayLcd(Delay_60);
	Lcd_Cmd(Return_Home); //return home
	DelayLcd(Delay_5);
	Lcd_Cmd(Conf_lcd_4bits);  //Configura el LCD a 4 Bits, 2 Lineas Y Fuente de 5*7
	DelayLcd(Delay_1);
	Lcd_Cmd(Lcd_On_Cur_OFF); //display ON cursor OFF
	DelayLcd(Delay_1);
	Lcd_Cmd(Return_1_line); //cursor a primera linea
	DelayLcd(Delay_1);
	Lcd_Cmd(Clear_disp); //clear display

}

void Lcd_Clear(void)
{
	Lcd_Cmd(Clear_disp);
	DelayLcd(Delay_2);

}



void Lcd_Write_String(char *str, int fila, int col)
{

	uint8_t address;
	uint8_t vectorf[ Size0 ] = { 0x00, 0x40, 0x14, 0x54 }; //posiciones memoria para cada fila

	for (uint8_t i = 0; i < fila; i++)
	{
		address = vectorf[i];
	}

	address = address + (col - 1);
	Lcd_Cmd(Set_DDRam | address); //0x80  es del comando set DDRAM bit7=1

	while (*str)
		Lcd_Char(*str++);
}

void Lcd_Shift_Right(void)
{
	Lcd_Cmd(Shift_Right );
}

void Lcd_Shift_Left(void)
{
	Lcd_Cmd(Shift_Left );
}

void Lcd_Blink(void)
{
	Lcd_Cmd(Blink);
}

/*void Lcd_NoBlink(void) {
	Lcd_Cmd(0x0C);
}*/

void Lcd_CGRAM_CreateChar(unsigned char pos, const char *data_msg)
{
	if (pos < 8)
	{
		Lcd_Cmd(Set_CGRAM  + (pos * 8));
		for (unsigned char i = 0; i < 8; i++)
		{
			Lcd_Char(data_msg[i]);
		}
	}
}

void Lcd_CGRAM_WriteChar(char pos)
{
	Lcd_Char(pos);
}




