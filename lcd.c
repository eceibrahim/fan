#include "lcd.h"
#include "Port.h"
#include "util.h"
#include "os.h"
#include "SSD.h"

#define LCD_CONFG_WORD                  (0X30)
#define LCD_CLR                         (0X01)
#define LCD_CURSOR_HOME                 (0X02)
#define LCD_SET_ENTRY_MODE              (0X40)
#define LCD_INCREMENT_CURSOR            (0X02)
#define LCD_DECREMENT_CURSOR            (0X00)
#define LCD_DISPLAY_SHIFT_ON            (0X01)
#define LCD_DISPLAY_SHIFT_OFF           (0X00)

#define LCD_DISPLAY_CONTROL             (0X08)
#define LCD_DISPLAY_ON                  (0X04)
#define LCD_DISPLAY_OFF                 (0X00)
#define LCD_CURSOR_ON                   (0X02)
#define LCD_CURSOR_OFF                  (0X00)
#define LCD_CURSOR_BLINK_ON             (0X01)
#define LCD_CURSOR_BLINK_OFF            (0X00)

#define LCD_CURSOR_DIPLAY_CONTROL       (0X10)
#define LCD_SHIFT_CURSOR                (0X00)
#define LCD_SHIFT_DISPLAY               (0X08)
#define LCD_SHIFT_RIGHT                 (0X00)
#define LCD_SHIFT_LEFT                  (0X02)

#define LCD_FUNCTION_SET                (0X20)
#define LCD_DATA_LENGTH_4               (0X00)
#define LCD_DATA_LENGTH_8               (0X10)
#define LCD_ONE_LINE                    (0X00)
#define LCD_TWO_LINES                   (0X08)
#define LCD_SMALL_FONT                  (0X00)
#define LCD_LARGE_FONT                  (0X04)


#define LCD_SET_CGROM_ADDRESS           (0X40)
#define LCD_SET_DDRAM_ADDRESS           (0X80)

#define LCD_LINE_SIZE                   (40)
#define LCD_DDRAM_LINE1_START_ADDRESS   (0X40)


char string[LCD_LINES_NUMBER][LCD_LINE_WIDTH] ;

static void LCD_SendCommand(uint8_t command) ;
static void LCD_GoTo(uint8_t line , uint8_t column);
static void LCD_SendData(uint8_t character);

void LCD_Init(void)
{
    GPIO_InitPortPin(LCD_DATA_PORT_CMD , LCD_DATA_PINS , GPIO_Output);
    GPIO_InitPortPin(LCD_RS_PORT_CMD , LCD_RS_PIN , GPIO_Output );
    GPIO_InitPortPin(LCD_E_PORT_CMD , LCD_E_PIN , GPIO_Output);

    GPIO_SetPortPinState(LCD_RS_PORT_DATA , LCD_RS_PIN , 0);
    GPIO_SetPortPinState(LCD_E_PORT_DATA , LCD_E_PIN , 0);

    UTIL_DelayMS(20);
    GPIO_SetPortPinState(LCD_E_PORT_DATA , LCD_E_PIN , 1);
    LCD_SendCommand(LCD_CONFG_WORD);
    UTIL_DelayMS(5);
    LCD_SendCommand(LCD_CONFG_WORD);
    UTIL_DelayMS(5);
    LCD_SendCommand(LCD_CONFG_WORD);

    LCD_SendCommand(LCD_FUNCTION_SET|LCD_DATA_LENGTH_8|LCD_TWO_LINES|LCD_SMALL_FONT);
    LCD_SendCommand(LCD_DISPLAY_CONTROL|LCD_DISPLAY_OFF|LCD_CURSOR_OFF|LCD_CURSOR_BLINK_OFF);
    LCD_SendCommand(LCD_CLR);
    LCD_SendCommand(LCD_SET_ENTRY_MODE|LCD_INCREMENT_CURSOR|LCD_DISPLAY_OFF);
    LCD_SendCommand(LCD_DISPLAY_CONTROL|LCD_DISPLAY_ON|LCD_CURSOR_OFF|LCD_CURSOR_BLINK_OFF);
}

void LCD_Update(void)
{
    static uint16_t counter_ms = 0;

    counter_ms += OS_TICK_MS ;
    if(counter_ms != LCD_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0;

    SSD_TurnOff();
    LCD_SetString(string[0]  , 0);
    LCD_SetString(string[1]  , 1);
    SSD_TurnOn();
}

void LCD_SetChar(uint8_t character , uint8_t line , uint8_t column)
{
    LCD_GoTo(line, column);
    LCD_SendData(character);
}

void LCD_SetString(char * string, uint8_t line)
{
    uint8_t current_index  =0 ;

    if(line == 0)
    {
        LCD_SendCommand(LCD_CLR);
    }

    while(string[current_index] != '\0')
    {

        LCD_SetChar(string[current_index] , line , current_index);
        ++current_index ;
    }
}

static void LCD_SendCommand(uint8_t command)
{
    GPIO_SetPortPinState(LCD_E_PORT_DATA ,LCD_E_PIN , 1 );
    GPIO_SetPort(LCD_DATA_PORT , command);
    GPIO_SetPortPinState(LCD_RS_PORT_DATA , LCD_RS_PIN , 0) ;
    GPIO_SetPortPinState(LCD_E_PORT_DATA , LCD_E_PIN , 0);
    GPIO_SetPortPinState(LCD_E_PORT_DATA , LCD_E_PIN , 1);
}

static void LCD_GoTo(uint8_t line , uint8_t column)
{
    uint8_t address ;
    address = (line * LCD_DDRAM_LINE1_START_ADDRESS) + column ;
    LCD_SendCommand(address|LCD_SET_DDRAM_ADDRESS) ;

}

static void LCD_SendData(uint8_t character)
{
    GPIO_SetPortPinState(LCD_E_PORT_DATA ,LCD_E_PIN , 1 );
    GPIO_SetPort(LCD_DATA_PORT , character);
    GPIO_SetPortPinState(LCD_RS_PORT_DATA , LCD_RS_PIN , 1) ;
    GPIO_SetPortPinState(LCD_E_PORT_DATA , LCD_E_PIN , 0);
    GPIO_SetPortPinState(LCD_E_PORT_DATA , LCD_E_PIN , 1);
}

void LCD_PutString(char * address , uint8_t line)
{
    uint8_t current_index ;
    for(current_index =0 ; current_index < LCD_LINE_WIDTH ; ++current_index)
    {
        string[line][current_index] = address[current_index];
    }
}
