/*
 * LCD.h
 *
 * Created: 10/4/2019 9:03:09 AM
 *  Author: Nasser
 */ 


#ifndef LCD_H_
#define LCD_H_

#define left 0x04
#define right 0x05
#define clr 0x01

void LCD_movecursor(char row,char coloumn);
void LCD_initialize ();
void LCD_falling_edge ();
void LCD_send_cmd (unsigned char cmd);
void LCD_send_char (unsigned char data);
void LCD_send_string (unsigned char *data);


#endif /* LCD_H_ */