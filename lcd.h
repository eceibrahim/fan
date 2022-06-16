#ifndef __LCD_H__
#define __LCD_H__

#include "Main.h"

#define LCD_TASK_PERIOD_MS                  (1500)

#define LCD_LINE_WIDTH                      (16)
#define LCD_LINES_NUMBER                    (2)


void LCD_Init(void);
void LCD_Update(void);
void LCD_SetChar(uint8_t character , uint8_t line , uint8_t column);
void LCD_SetString(char * string, uint8_t line);
void LCD_PutString(char * address , uint8_t line);

#endif /*__LCD_H__*/
