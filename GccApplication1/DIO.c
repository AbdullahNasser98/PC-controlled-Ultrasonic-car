/*
 * DIO.c
 *
 * Created: 9/8/2019 11:23:37 AM
 *  Author: Nasser
 */ 


#include <avr/io.h>
#include "macros.h"

	void DIO_setdir (unsigned char portname, unsigned char pinnumber, unsigned char direction)
	{
		switch(portname)
		{
			case 'A':
			if (direction==1)
			{
				SET_BIT(DDRA,pinnumber);	
			}
			
			else
			{
				CLR_BIT(DDRA,pinnumber);
			}
			break;
			
			case 'B':
			if (direction==1)
			{
				SET_BIT(DDRB,pinnumber);
			}
			
			else
			{
				CLR_BIT(DDRB,pinnumber);
			}
			break;
			
			case 'C':
			if (direction==1)
			{
				SET_BIT(DDRC,pinnumber);
			}
			
			else
			{
				CLR_BIT(DDRC,pinnumber);
			}
			break;
			
			case 'D':
			if (direction==1)
			{
				SET_BIT(DDRD,pinnumber);
			}
			
			else
			{
				CLR_BIT(DDRD,pinnumber);
			}
			break;
			default:
			break;
		}
	}
	
	void DIO_write (unsigned char portname, unsigned char pinnumber, unsigned char outval)
	{
		switch (portname)
		{
			case 'A':
			if (outval==1)
			{
				SET_BIT(PORTA,pinnumber);
			}
			
			else
			{
				CLR_BIT(PORTA,pinnumber);
			}
			break;
			
			case 'B':
			if (outval==1)
			{
				SET_BIT(PORTB,pinnumber);
			}
			
			else
			{
				CLR_BIT(PORTB,pinnumber);
			}
			break;
			
			case 'C':
			if (outval==1)
			{
				SET_BIT(PORTC,pinnumber);
			}
			
			else
			{
				CLR_BIT(PORTC,pinnumber);
			}
			break;
			
			case 'D':
			if (outval==1)
			{
				SET_BIT(PORTD,pinnumber);
			}
			
			else
			{
				CLR_BIT(PORTD,pinnumber);
			}
			break;
			default:
			break;
		}
	}
	
	unsigned char DIO_read (unsigned char portname, unsigned char pinnumber)
	{	
		unsigned char return_value=0;
		
		switch (portname)
		{
			case 'A':
				return_value=READ_BIT(PINA,pinnumber);
				break;
				
			case 'B':
			return_value=READ_BIT(PINB,pinnumber);
			break;
			
			case 'C':
			return_value=READ_BIT(PINC,pinnumber);
			break;
			
			case 'D':
			return_value=READ_BIT(PIND,pinnumber);
			break;
			
			default:
			break;
				
			
		}	
		
			return return_value;
		
	}
	
	
		
void DIO_write_port(unsigned char portname,unsigned char portvalue)
{
	switch(portname)
	{
		case 'A' :
		PORTA=portvalue; //Write the given value to the port A
		break ;
		case 'B':
		PORTB=portvalue; //Write the given value to the port B
		break ;
		case 'C' :
		PORTC=portvalue; //Write the given value to the port C
		break ;
		case 'D':
		PORTD=portvalue; //Write the given value to the port D
		break ;
		default:
		break ;
	}
}

void DIO_setdir_port(unsigned char portname,unsigned char direction)
{
	switch(portname)
	{
		case 'A' :
		DDRA=direction;
		break ;
		case 'B':
		DDRB=direction;
		break ;
		case 'C' :
		DDRC=direction;
		break ;
		case 'D':
		DDRD=direction;
		break ;
		default:
		break ;
	}
	
}



