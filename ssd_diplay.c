#include "ssd_display.h"
#include "ssd.h"
#include "Main.h"
#include "os.h"
#include "fan_controller.h"

#define DISPLAY_DOT_TOGGLE_DURATION_MS                         (1000)
#define DIPLAY_BLINKING_DURATION_MS                            (1000)

typedef enum
{
    INIT  = 0,
    TIMING ,
    SETTING  ,
}DISPLAY_State_t;

DISPLAY_State_t display_state  ;


void SSD_InitDisplay(void)
{
    display_state = INIT;
}

void SSD_UpdateDisplay(void)
{
    static uint8_t counter_ms = 0;
    static uint16_t time_in_state_ms  =0 ;
    FAN_Time_t  wanted_time ;
    FAN_Time_t current_time ;
    counter_ms += OS_TICK_MS ;
    if(counter_ms != SSD_DISPLAY_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0;


    switch(display_state)
    {
    case INIT:
        {

            if(FAN_GetState() == FAN_SPEED)
            {
                display_state = TIMING ;
                SSD_SetSymbol(SSD_MEDIUM_RIGHT , SSD_NULL);
                SSD_SetSymbol(SSD_MEDIUM_LEFT , SSD_NULL);
            }
            else
            {
                SSD_SetSymbol(SSD_MEDIUM_LEFT , SSD_H);
                SSD_SetSymbol(SSD_MEDIUM_RIGHT , SSD_I);
            }
            break;
        }
    case TIMING :
        {
            if(FAN_GetState() == FAN_TIMER)
            {
                display_state =SETTING ;
                time_in_state_ms = 0;
            }

            FAN_GetWantedTime(&wanted_time);

            if(wanted_time.hours == 0)
            {
                SSD_SetSymbol(SSD_RIGHT , SSD_0 );
                SSD_SetSymbol(SSD_MEDIUM_RIGHT, SSD_0);
                SSD_SetSymbol(SSD_MEDIUM_LEFT ,SSD_0);
                SSD_SetSymbol(SSD_LEFT , SSD_0);
                SSD_SetDotState(SSD_ON);
            }
            else
            {
                /*Read fan current time */
                FAN_GetCurrentTime(&current_time);

                time_in_state_ms += SSD_DISPLAY_TASK_PERIOD_MS ;

                SSD_SetSymbol(SSD_RIGHT , current_time.minutes % 10 );
                SSD_SetSymbol(SSD_MEDIUM_RIGHT, current_time.minutes / 10);
                SSD_SetSymbol(SSD_MEDIUM_LEFT ,current_time.hours % 10);
                SSD_SetSymbol(SSD_LEFT , current_time.hours / 10);

                if(time_in_state_ms == DISPLAY_DOT_TOGGLE_DURATION_MS)
                {
                    time_in_state_ms = 0 ;
                    if(SSD_GetDotState() == SSD_OFF)
                    {
                        SSD_SetDotState(SSD_ON);
                    }
                    else
                    {
                        SSD_SetDotState(SSD_OFF);
                    }
                }

            }
            break ;
        }
        case SETTING :
        {
            if(FAN_GetState() == FAN_SPEED)
            {
                display_state = TIMING ;
            }

            time_in_state_ms += SSD_DISPLAY_TASK_PERIOD_MS  ;

            if(time_in_state_ms == DIPLAY_BLINKING_DURATION_MS)
            {
                time_in_state_ms = 0;
                if((SSD_GetSymbol(SSD_RIGHT) == SSD_NULL) &&(SSD_GetSymbol(SSD_MEDIUM_RIGHT) == SSD_NULL) &&
                   (SSD_GetSymbol(SSD_MEDIUM_LEFT) == SSD_NULL) && (SSD_GetSymbol(SSD_LEFT) == SSD_NULL))
                {
                    FAN_GetWantedTime(&wanted_time);
                    SSD_SetSymbol(SSD_RIGHT , wanted_time.minutes % 10 );
                    SSD_SetSymbol(SSD_MEDIUM_RIGHT, wanted_time.minutes / 10);
                    SSD_SetSymbol(SSD_MEDIUM_LEFT ,wanted_time.hours % 10);
                    SSD_SetSymbol(SSD_LEFT , wanted_time.hours / 10);
                    SSD_SetDotState(SSD_ON);
                }
                else
                {
                    SSD_SetSymbol(SSD_RIGHT , SSD_NULL);
                    SSD_SetSymbol(SSD_MEDIUM_RIGHT, SSD_NULL);
                    SSD_SetSymbol(SSD_MEDIUM_LEFT ,SSD_NULL);
                    SSD_SetSymbol(SSD_LEFT , SSD_NULL);
                    SSD_SetDotState(SSD_OFF);
                }
            }
            else
            {
                if((SSD_GetSymbol(SSD_RIGHT) != SSD_NULL) &&(SSD_GetSymbol(SSD_MEDIUM_RIGHT) != SSD_NULL) &&
                   (SSD_GetSymbol(SSD_MEDIUM_LEFT) != SSD_NULL) && (SSD_GetSymbol(SSD_LEFT) != SSD_NULL))
                   {
                       FAN_GetWantedTime(&wanted_time);

                       SSD_SetSymbol(SSD_RIGHT , wanted_time.minutes % 10 );
                       SSD_SetSymbol(SSD_MEDIUM_RIGHT, wanted_time.minutes / 10);
                       SSD_SetSymbol(SSD_MEDIUM_LEFT ,wanted_time.hours % 10);
                       SSD_SetSymbol(SSD_LEFT , wanted_time.hours / 10);
                       SSD_SetDotState(SSD_ON);
                   }
                   else
                   {

                       SSD_SetSymbol(SSD_RIGHT , SSD_NULL);
                       SSD_SetSymbol(SSD_MEDIUM_RIGHT, SSD_NULL);
                       SSD_SetSymbol(SSD_MEDIUM_LEFT ,SSD_NULL);
                       SSD_SetSymbol(SSD_LEFT , SSD_NULL);
                       SSD_SetDotState(SSD_OFF);
                   }
            }
        }
    default :
        {
            /*Should not be here !*/
            break ;
        }

    }
}


