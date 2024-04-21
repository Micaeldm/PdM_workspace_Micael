#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */

#include <stdbool.h>
//tiempos demora
#define  Delay_1   		1
#define  Delay_2  		2
#define  Delay_5   		5
#define  Delay_60  		60

//Comandos
#define inicializa 		0x03
#define Return_Home 	0x02
#define Conf_lcd_4bits 	0x28
#define Lcd_On_Cur_OFF 	0x0C
#define Return_1_line 	0x80
#define Clear_disp   	0x01
#define Shift_Right  	0x1C
#define Shift_Left  	0x18
#define Blink 			0x0F
//#define NoBlink  		0x18

//Escritura
#define Set_DDRam 		(1<<7)
#define Set_CGRAM 		(1<<6)

void Lcd_Init(void);
void Lcd_Send_Cmd(char cmd);
void Lcd_Send_Char(char data);
void Lcd_Send_String(char *str);
void Lcd_Write_String(char *str,int row, int col);
void Lcd_Set_Cursor(int row, int col);
void Lcd_Clear(void);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);
void Lcd_Blink(void);
void Lcd_NoBlink(void);
void Lcd_CGRAM_CreateChar(unsigned char pos, const char*msg);
void Lcd_CGRAM_WriteChar(char pos);

#endif
