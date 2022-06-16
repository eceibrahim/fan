#include "fan_controller.h"
#include "push_button.h"
#include "speed.h"
#include "buzzer.h"
#include "os.h"

#define FAN_MAXIMUM_INIT_DURATION_MS                                      (1000)

#define FAN_DISPLAY_BUTTON_MAXIMUM_PRESSSD_DURATION_MS                    (200)
#define FAN_DISPLAY_STATE_MAXIMUM_DURATION_MS                             (20000)

#define FAN_TIMER_BUTTON_MAXIMUM_PRESSSD_DURATION_MS                      (10)

#define FAN_MINUTE_DURATION_MS                                            (60000)

#define FAN_TIMER_TIMER_STATE_MAXIMUM_DURATION_MS                          (6000)

typedef enum
{
    FAN_MINIMUM ,
    FAN_MEDIUM ,
    FAN_MAXIMUM
}FAN_SpeedState_t;

static FAN_Time_t fan_wanted_time  ;
static FAN_Time_t fan_current_time ;


static FAN_State_t fan_state ;


static FAN_SpeedState_t speed_state ;


void FAN_Init(void)
{
    fan_state = FAN_INIT ;
    speed_state = FAN_MINIMUM;
    fan_wanted_time .hours = 0;
    fan_wanted_time.minutes = 0;
    fan_current_time.hours = 0 ;
    fan_current_time.minutes = 0;
}

void FAN_Update(void)
{
    static uint16_t time_in_state_ms = 0 ;
    static uint8_t counter_ms = 0;


    counter_ms += OS_TICK_MS ;
    if(counter_ms != FAN_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0;

    switch(fan_state)
    {

    case FAN_INIT :
        {
            time_in_state_ms += FAN_TASK_PERIOD_MS ;
            if(time_in_state_ms == FAN_MAXIMUM_INIT_DURATION_MS)
            {
                fan_state = FAN_SPEED;
            }
            break;
        }
    case FAN_OFF :
        {
            if((PB_GetState(PB_TIMER)==PB_PRESSED) && (PB_GetPressedTime(PB_TIMER) >= FAN_TIMER_BUTTON_MAXIMUM_PRESSSD_DURATION_MS))
            {
                BUZZER_SetState(BUZZER_ON);
                fan_state = FAN_TIMER ;
            }
            break ;
        }
    case FAN_SPEED :
        {

            /*update fan state */
            if((PB_GetState(PB_TIMER)==PB_PRESSED) && (PB_GetPressedTime(PB_TIMER) >= FAN_TIMER_BUTTON_MAXIMUM_PRESSSD_DURATION_MS))
            {
                BUZZER_SetState(BUZZER_ON);
                fan_state = FAN_TIMER ;
            }
            else if((PB_GetState(PB_DISPLAY) == PB_PRESSED) && (PB_GetPressedTime(PB_DISPLAY) >= FAN_DISPLAY_BUTTON_MAXIMUM_PRESSSD_DURATION_MS))
            {
                BUZZER_SetState(BUZZER_ON);
                time_in_state_ms = 0;
                fan_state = FAN_DISPLAY ;
            }

            /*Update speed state */

            switch(speed_state)
            {
            case FAN_MINIMUM :
                {
                    if(PB_GetState(PB_PLUS) == PB_PRE_RELEASED)
                    {
                        BUZZER_SetState(BUZZER_ON);
                        speed_state = FAN_MEDIUM;
                        SPEED_SetSpeed(SPEED_MEDIUM);
                    }
                    break;
                }
            case FAN_MEDIUM :
                {
                    if(PB_GetState(PB_PLUS) == PB_PRE_RELEASED)
                    {
                        BUZZER_SetState(BUZZER_ON);
                        speed_state = FAN_MAXIMUM ;
                        SPEED_SetSpeed(SPEED_MAXIMUM);

                    }
                    else if (PB_GetState(PB_MINUS) == PB_PRE_RELEASED)
                    {
                        BUZZER_SetState(BUZZER_ON);
                        speed_state = FAN_MINIMUM ;
                        SPEED_SetSpeed(SPEED_MINIMUM);
                    }

                    break;
                }
            case FAN_MAXIMUM :
                {
                    if(PB_GetState(PB_MINUS) ==  PB_PRE_RELEASED)
                    {
                        BUZZER_SetState(BUZZER_ON);
                        speed_state = FAN_MEDIUM ;
                        SPEED_SetSpeed(SPEED_MEDIUM);
                    }
                    break;
                }
            default :
                {

                    break;
                }
            }

            /*End of update speed state */

            /*Update fan time */
            if((fan_current_time.hours != 0) || (fan_current_time.minutes != 0))
            {
                time_in_state_ms += FAN_TASK_PERIOD_MS ;
                if(time_in_state_ms == FAN_MINUTE_DURATION_MS)
                {
                    time_in_state_ms = 0;

                    if((fan_current_time.minutes == 0) && (fan_current_time.hours != 0 ))
                    {
                        --fan_current_time.hours ;
                        fan_current_time.minutes = 59 ;
                    }
                    else if ((fan_current_time.minutes != 0)  && (fan_current_time.hours == 0 ))
                    {
                        --fan_current_time.minutes ;
                        if(fan_current_time.minutes == 0 )
                        {
                            fan_state = FAN_OFF ;
                        }
                    }
                    else if((fan_current_time.minutes != 0)  && (fan_current_time.hours != 0 ))
                    {
                        --fan_current_time.minutes ;
                        if(fan_current_time.minutes == 0)
                        {
                            --fan_current_time.hours ;
                            fan_current_time.minutes = 59 ;
                        }
                    }

                }
            }
            break ;
        }
    case FAN_DISPLAY:
        {
            time_in_state_ms += FAN_TASK_PERIOD_MS ;

            if(time_in_state_ms  == FAN_DISPLAY_STATE_MAXIMUM_DURATION_MS)
            {
                fan_state = FAN_SPEED ;
                time_in_state_ms = 0;
            }
            else if(PB_GetState(PB_DISPLAY) == PB_PRE_PRESSED)
            {
                BUZZER_SetState(BUZZER_ON);
                time_in_state_ms = 0;
                fan_state = FAN_SPEED ;
            }
            break ;
        }
    case FAN_TIMER :
        {
            if(PB_GetState(PB_PLUS) == PB_PRE_RELEASED)
            {
                BUZZER_SetState(BUZZER_ON);
                fan_wanted_time.hours = (fan_wanted_time.hours + 1) % 5 ;
                if(fan_wanted_time.hours == 3)
                {
                    fan_wanted_time.hours = 4 ;
                }
                else if (fan_wanted_time.hours == 4)
                {
                    fan_wanted_time.hours= 0 ;
                }
            }
            else if (PB_GetState(PB_MINUS) == PB_PRE_RELEASED)
            {
                BUZZER_SetState(BUZZER_ON);
                if(fan_wanted_time.hours == 0)
                {
                    fan_wanted_time.hours = 4 ;
                }
                else if (fan_wanted_time.hours == 4)
                {
                    fan_wanted_time.hours = 2 ;
                }
                else
                {
                    -- fan_wanted_time.hours ;
                }
            }
            else if ((PB_GetState(PB_PLUS) == PB_RELEASED) && (PB_GetReleasedTime(PB_PLUS) >= FAN_TIMER_TIMER_STATE_MAXIMUM_DURATION_MS) &&
                     (PB_GetState(PB_MINUS) == PB_RELEASED) && (PB_GetReleasedTime(PB_MINUS) >= FAN_TIMER_TIMER_STATE_MAXIMUM_DURATION_MS) &&
                     (PB_GetState(PB_TIMER) == PB_RELEASED) && (PB_GetReleasedTime(PB_TIMER) >= FAN_TIMER_TIMER_STATE_MAXIMUM_DURATION_MS) )
            {
                fan_state = FAN_SPEED ;
                fan_current_time.hours = fan_wanted_time.hours ;
                fan_current_time.minutes = 0 ;
            }

            break;
        }
    default :
        {
            /*Should not be here !*/
            break ;
        }
    }

}

FAN_State_t FAN_GetState(void)
{
    FAN_State_t ret ;
    ret = fan_state ;
    return ret ;
}

void FAN_GetWantedTime(FAN_Time_t * time)
{
    time->hours = fan_wanted_time.hours ;
}

void FAN_GetCurrentTime(FAN_Time_t * time)
{
    time->hours  = fan_current_time.hours ;
    time->minutes = fan_current_time.minutes ;
}
