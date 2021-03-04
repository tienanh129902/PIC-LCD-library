/*
 * File:   lcd.c
 * Author: DELL
 *
 * Created on February 2, 2021, 4:25 PM
 */

#include "lcd.h"
__bit RS;
void LCD_writeNibble(uint8_t n)
{
  LCD_RS = RS;
  LCD_D4 = n & 0x01;
  LCD_D5 = (n >> 1) & 0x01;
  LCD_D6 = (n >> 2) & 0x01;
  LCD_D7 = (n >> 3) & 0x01;

  // send enable pulse
  LCD_EN = 0;
  __delay_us(1);
  LCD_EN = 1;
  __delay_us(1);
  LCD_EN = 0;
  __delay_us(100);
}

void LCD_cmd(uint8_t Command)
{
  RS = 0;
  LCD_writeNibble(Command >> 4);
  LCD_writeNibble(Command);
  if((Command == LCD_CLEAR) || (Command == LCD_RETURN_HOME))
    __delay_ms(2);
}

void LCD_goTo(uint8_t col, uint8_t row)
{
  switch(row)
  {
    case 2:
      LCD_cmd(LCD_SECOND_ROW + col - 1);
      break;
    case 3:
      LCD_cmd(LCD_THIRD_ROW  + col - 1);
      break;
    case 4:
      LCD_cmd(LCD_FOURTH_ROW + col - 1);
    break;
    default:      // case 1:
      LCD_cmd(LCD_FIRST_ROW  + col - 1);
  }

}

void LCD_putChar(char LCD_Char)
{
  RS = 1;
  LCD_writeNibble(LCD_Char >> 4);
  LCD_writeNibble(LCD_Char );
}

void LCD_print(char* LCD_Str)
{
  uint8_t i = 0;
  RS = 1;
  while(LCD_Str[i] != '\0')
  {
    LCD_writeNibble(LCD_Str[i] >> 4);
    LCD_writeNibble(LCD_Str[i++] );
  }
}

void LCD_begin()
{
  RS = 0;

  LCD_RS     = 0;
  LCD_EN     = 0;
  LCD_D4     = 0;
  LCD_D5     = 0;
  LCD_D6     = 0;
  LCD_D7     = 0;
  LCD_RS_DIR = 0;
  LCD_EN_DIR = 0;
  LCD_D4_DIR = 0;
  LCD_D5_DIR = 0;
  LCD_D6_DIR = 0;
  LCD_D7_DIR = 0;

  __delay_ms(40);
  LCD_cmd(3);
  __delay_ms(5);
  LCD_cmd(3);
  __delay_ms(5);
  LCD_cmd(3);
  __delay_ms(5);
  LCD_cmd(LCD_RETURN_HOME);
  __delay_ms(5);
  LCD_cmd(0x20 | (LCD_TYPE << 2));
  __delay_ms(50);
  LCD_cmd(LCD_TURN_ON);
  __delay_ms(50);
  LCD_cmd(LCD_CLEAR);
  __delay_ms(50);
  LCD_cmd(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
  __delay_ms(50);
}
