#include <API_i2c.h>
#include <API_LCD_i2c.h>
#include <API_LCD_port.h>
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

bool  comando=1;

//void Enviar4bitWrite(uint8_t data_t[4],bool comando);
//void Enviar4bitWrite(char data1,bool comando);

/*void Enviar4bitWrite(char data1,bool comando){
	uint8_t data_t[4];
	char cmd=data1;
	char data=data1;
	if(comando){
		 data_t[0] =(cmd & 0xF0)+EN+BL; //EN=1 Bl=1    |0x0C 1
				data_t[1] = (cmd & 0xF0)+BL;  //EN=0 Bl=1
				data_t[2] = ((cmd<<4) & 0xF0)+EN+BL; //EN=1 Bl=1 control=0    |0x0C 1
				data_t[3] = ((cmd<<4) & 0xF0)+BL; //EN=1 Bl=1 control=0    |0x0C 1
	}

	if(!comando){
		        data_t[0] =(data & 0xF0)+EN+BL+W; //EN=1 Bl=1
				data_t[1] = (data& 0xF0)+BL+W;  //EN=0 Bl=1
				data_t[2] = ((data<<4) & 0xF0)+EN+BL+W; //EN=1 Bl=1 W=1 datos
				data_t[3] = ((data<<4) & 0xF0)+BL+W; //EN=1 Bl=1
	}


	returnValue=HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS,(uint8_t*) data_t, 4, 100);
	if(returnValue != HAL_OK){
		Error_Handler();

}

}*/




static void Lcd_Cmd(char cmd)
{


        comando=true;
		Enviar4bitWrite(cmd,comando);

}

static void Lcd_Char(char data)
{

			comando=false;
			Enviar4bitWrite(data,comando);

}

void Lcd_Init(void)
{
	//HAL_Delay(60);


	for(unsigned char i=0; i<3; i++){
		Lcd_Cmd(0x03);         //Inicializa
		HAL_Delay(5);
		}


	        HAL_Delay(60);
			Lcd_Cmd(0x02); //return home
			HAL_Delay(5);
			Lcd_Cmd(0x28);  //Configura el LCD a 4 Bits, 2 Lineas Y Fuente de 5*7
		    HAL_Delay(1);
			Lcd_Cmd(0x0C); //display ON cursor OFF
			HAL_Delay(1);
			Lcd_Cmd(0x80); //cursor a primera linea
		    HAL_Delay(1);
			Lcd_Cmd(0x01); //clear display



}

void Lcd_Clear(void)
{
	Lcd_Cmd(0x01);
	HAL_Delay(2);
}

/*void Lcd_Set_Cursor(int row, int col)
{
	uint8_t address;
	switch(row)
	{
		case 1:
			address = 0x00; //linia 1
			break;
		case 2:
			address = 0x40; //linea 2
			break;
		case 3:
			address = 0x14; //linea 3
			break;
		case 4:
			address = 0x54; //linea 4
			break;
	}
	address += col - 1;
	Lcd_Send_Cmd(0x80 | address); //0x80  es del comando set DDRAM bit7=1

}*/

void Lcd_Write_String(char *str,int fila, int col)
{

	uint8_t address;
	uint8_t vectorf[4]={0x00,0x40,0x14,0x54}; //posiciones memoria para cada fila

	for(uint8_t i=0; i<fila;i++){

		address=vectorf[i];

	}


		address = address+(col - 1);
		Lcd_Cmd(0x80 | address); //0x80  es del comando set DDRAM bit7=1

	while(*str) Lcd_Char(*str++);
}

void Lcd_Shift_Right(void)
{
	Lcd_Cmd(0x1C);
}

void Lcd_Shift_Left(void)
{
	Lcd_Cmd(0x18);
}

void Lcd_Blink(void)
{
	Lcd_Cmd(0x0F);
}

void Lcd_NoBlink(void)
{
	Lcd_Cmd(0x0C);
}

void Lcd_CGRAM_CreateChar(unsigned char pos, const char*msg)
{
    if(pos < 8)
    {
        Lcd_Cmd(0x40 + (pos*8));
        for(unsigned char i=0; i<8; i++)
        {
            Lcd_Char(msg[i]);
        }
    }
}

void Lcd_CGRAM_WriteChar(char pos)
{
    Lcd_Char(pos);
}




