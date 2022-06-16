#include "lcd_display.h"
#include "lcd.h"
#include "speed.h"
#include "slider.h"
#include "os.h"
#include "fan_controller.h"

#define DISPLAY_MAXIMUM_PRESSED_DISPLAY_BUTTON_DURATION_MS             (200)
#define DISPLAY_MAXIMUM_SWING_STATE_DURATION_MS                        (20000)

typedef enum
{
    SPEED = 0,
    SWING
}DISPLAY_State_t ;

static DISPLAY_State_t display_state ;

void LCD_InitDisplay(void)
{
    display_state = SPEED;
}

void LCD_UpdateDisplay(void)
{
    static uint16_t time_in_state_ms  ;
    uint8_t slider_value ;
    static uint16_t counter_ms = 0;
    FAN_State_t fan_state ;
    counter_ms += OS_TICK_MS ;
    if(counter_ms != LCD_DISPLAY_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0 ;

    fan_state  =FAN_GetState();

    switch(display_state)
    {
    case SPEED :
        {
            if(fan_state ==  FAN_DISPLAY)
            {
                time_in_state_ms = 0;
                display_state = SWING ;
            }
            else
            {
                LCD_PutString("  Motor Speed   ", 0) ;

                if(SPEED_GetSpeed() == SPEED_MINIMUM)
                {
                    LCD_PutString("Speed=140 degree" , 1);
                }
                else if (SPEED_GetSpeed() == SPEED_MEDIUM)
                {
                    LCD_PutString("Speed=90  degree" , 1);
                }
                else if (SPEED_GetSpeed() == SPEED_MAXIMUM)
                {
                    LCD_PutString("Speed=10  degree" , 1);
                }
            }
            break;
        }
    case SWING :
        {
            slider_value = SLIDER_GetValue();
            time_in_state_ms += LCD_DISPLAY_TASK_PERIOD_MS ;
            if(fan_state ==  FAN_SPEED)
            {
                display_state = SPEED ;
            }

            LCD_PutString("  Swing Value   ",0);

            switch(slider_value)
            {
            case 0:
                {
                    LCD_PutString("                ",1);
                    break ;
                }
            case 1:
                {
                    LCD_PutString("       **       ",1);
                    break ;
                }
            case 2:
                {
                    LCD_PutString("      ****      ",1);
                    break;
                }
            case 3 :
                {
                    LCD_PutString("     ******     ",1);
                    break ;
                }
            case 4 :
                {
                    LCD_PutString("    ********    ",1);
                    break ;
                }
            case 5 :
                {
                    LCD_PutString("   **********   ",1);
                    break ;
                }
            case 6:
                {
                    LCD_PutString("  ************  ",1);
                    break ;
                }
            case 7 :
                {
                    LCD_PutString(" ************** ",1);
                    break ;
                }
            case 8:
                {
                    LCD_PutString("****************",1);
                    break ;
                }
            }
            break;
        }
    default :
        {
            /*Should not be here !*/
            break;
        }
    }
}
