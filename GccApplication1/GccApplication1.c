/*
 * GccApplication1.c
 *
 * Created: 12/29/2020 1:05:11 PM
 *  Author: Abdulrhman Nasser
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "macros.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "USART.h"

#define  Trigger_pin	PA0	/* Trigger pin */


int TimerOverflow = 0;
char direction;				//Direction received from PC
char speed;

int main(void)
{
	UART_vInit(9600);
	LCD_initialize();
	long count;
	double distance;
	int ton=5000, toff=5000;		//Var to controll speed of motor
	
	DDRA = 0x07;					//Make pin0 of port a trigger of ultrasonic
	PORTD = 0xFF;					//Turn on pull up
	//Controlling of motor
	SET_BIT(DDRA,7);
	SET_BIT(DDRA,6);
	SET_BIT(DDRA,5);
	SET_BIT(DDRA,4);
	
	UCSRB |= (1 << RXCIE);
	sei();
	SET_BIT(TIMSK, TOIE1);			//Enable timer interupt
	TCCR1A = 0;						//normal mode
	LCD_movecursor(1,1);
	LCD_send_string("Distance: ");
	LCD_movecursor(2,1);
	LCD_send_string("Direction: ");
    while(1)
	{
		//Recieve direction from bluetooth module
		LCD_movecursor(2,11);
		LCD_send_char(direction);				//direction recieved by the bluetooth module
		LCD_send_char(speed);
		
        /*Send 10us pulse to trigger*/
		SET_BIT(PORTA,0);
		_delay_us(10);
		CLR_BIT(PORTA,0);
		
		TCNT1 = 0;					//Clear timer count
		TCCR1B = 0x41;				/* Capture on rising edge, No prescaler*/
		TIFR = 1<<ICF1;				/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;				/* Clear Timer Overflow flag */
		
		/*Calculate width of Echo by Input Capture (ICP) */
		
		while ((TIFR & (1 << ICF1)) == 0);/* Wait for rising edge */
		TCNT1 = 0;	/* Clear Timer counter */
		TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
		TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
		TimerOverflow = 0;/* Clear Timer overflow count */
		
		while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
		count = ICR1 + (65535 * TimerOverflow);	/* Take count */
		/* 8MHz Timer freq, sound speed =343 m/s */
		distance = (double)count / 466.47;
		
		/*Send reading to LCD*/
		LCD_movecursor(1,10);
		if(distance>=100 && distance<1000)
		{
			LCD_send_char((distance/100)+48);
			LCD_send_char(((int)(distance/10)%10)+48);
			LCD_send_char(((int)distance%10)+48);
			LCD_movecursor(1,13);
			LCD_send_string("CM");
		}
		else if (distance>=10 && distance<100)
		{
			//LCD_send_string("0");
			LCD_send_char((distance/10)+48);
			LCD_send_char(((int)distance%10)+48);
			LCD_movecursor(1,12);
			LCD_send_string("CM");
			LCD_send_string("  ");
		}
		else if(distance<10)
		{
			//LCD_send_string("00");
			LCD_send_char(distance+48);
			LCD_movecursor(1,11);
			LCD_send_string("CM");
			LCD_send_string("   ");
		}
		
		
		//Motor controls
		
		//Speed control function
		switch (speed)
		{
		case '0':
			ton=9000;
			toff=1000;
			break;
		case '1':
			ton=5500;
			toff=4500;
			break;
		case '2':
			ton=6000;
			toff=4000;
			break;
		case '4':
			ton=6500;
			toff=3500;
			break;
		case '5':
			ton=7000;
			toff=3000;
			break;
		case '6':
			ton=7500;
			toff=2500;
			break;
		case '7':
			ton=8000;
			toff=2000;
			break;
		case '8':
			ton=8500;
			toff=1500;
			break;
		case '9':
			ton=9000;
			toff=1000;
			break;
		}
		
		//Move forward function
		if (direction=='F')
		{
			SET_BIT(PORTA,7);
			CLR_BIT(PORTA,6);
			SET_BIT(PORTA, 5);
			CLR_BIT(PORTA, 4);
			//_delay_loop_2(ton);
			/*CLR_BIT(PORTA,7);
			SET_BIT(PORTA,6);
			CLR_BIT(PORTA, 5);
			SET_BIT(PORTA, 4);*/
			//_delay_loop_2(toff);
		}
		
		else if (direction=='B')
		{
			CLR_BIT(PORTA,7);
			CLR_BIT(PORTA, 5);
			SET_BIT(PORTA,6);
			SET_BIT(PORTA, 4);
			_delay_loop_2(ton);
			SET_BIT(PORTA,7);
			SET_BIT(PORTA, 5);
			CLR_BIT(PORTA,6);
			CLR_BIT(PORTA, 4);
			_delay_loop_2(toff);
		}
		//Adjust it
		else if (direction=='R')
		{
			CLR_BIT(PORTA,7);
			CLR_BIT(PORTA, 5);
			SET_BIT(PORTA,6);
			SET_BIT(PORTA, 4);
			_delay_loop_2(ton);
			SET_BIT(PORTA,7);
			SET_BIT(PORTA, 5);
			CLR_BIT(PORTA,6);
			CLR_BIT(PORTA, 4);
			_delay_loop_2(toff);
		}
		//Adjust it
		else if (direction=='L')
		{
			CLR_BIT(PORTA,7);
			CLR_BIT(PORTA, 5);
			SET_BIT(PORTA,6);
			SET_BIT(PORTA, 4);
			_delay_loop_2(ton);
			SET_BIT(PORTA,7);
			SET_BIT(PORTA, 5);
			CLR_BIT(PORTA,6);
			CLR_BIT(PORTA, 4);
			_delay_loop_2(toff);
		}
		else if (direction=='S')
		{
			CLR_BIT(PORTA,7);
			CLR_BIT(PORTA, 5);
			CLR_BIT(PORTA,6);
			CLR_BIT(PORTA, 4);
		}
    }
}

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}


ISR(USART_RXC_vect)
{
	speed = UDR;
	direction = UDR;
}



