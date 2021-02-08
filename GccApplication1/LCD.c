/*
 * LCD.c
 *
 * Created: 9/28/2019 12:29:28 PM
 *  Author: Nasser
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"
#include "DIO.h"
#include "LCD.h"
#define portname 'B'
#define bitsport 'A'
#define  EN 1
#define RS 2
#define RW 3
#define  F_CPU 8000000UL


void LCD_initialize ()
{	_delay_ms(1000);
	DIO_setdir(portname,0,1);
	DIO_setdir(portname,1,1);
	DIO_setdir(portname,2,1);
	DIO_setdir(portname,3,1);
	DIO_setdir(portname,4,1);
	DIO_setdir(portname,5,1);
	DIO_setdir(portname,6,1);
	DIO_setdir(portname,7,1);
	DIO_setdir(bitsport,EN,1);
	DIO_setdir(bitsport,RW,1);
	DIO_setdir(bitsport,RS,1);
	
	LCD_send_cmd( 0x38); //8 bit mode
	_delay_ms(200);
	LCD_send_cmd(0x0e);//display on cursor on
	_delay_ms(200);
	LCD_send_cmd(0x01);//clear the screen
	_delay_ms(200);
	LCD_send_cmd(0x06); //entry mode
	_delay_ms(200);
}

void LCD_falling_edge()
{
	DIO_write(bitsport, EN, 1);
	_delay_ms(2);
	DIO_write(bitsport, EN, 0);
	_delay_ms(2);
}

void LCD_send_cmd(unsigned char cmd)
{
	DIO_write_port(portname, cmd);
	DIO_write(bitsport, RS, 0);
	LCD_falling_edge();
}

void LCD_send_char(unsigned char data)
{
	DIO_write_port(portname, data);
	DIO_write(bitsport, RS, 1);
	LCD_falling_edge();
}

void LCD_send_string (unsigned char *data)
{
	while ((*data) != '\0')
	{
		LCD_send_char(*data);
		data++;
	}
	LCD_falling_edge();
}

void LCD_movecursor(char row,char coloumn)
{
	char data ;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_send_cmd(data);
	_delay_ms(1);
}


