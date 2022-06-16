#include "push_button.h"
#include "Port.h"
#include "os.h"


#define PB_MAX_N                        (4)
#define PB_SAMPLES_N                    (2)

#define PB_RELEASED_VOLTAGE_LEVEL       (1)
#define PB_PRESSED_VOLTAGE_LEVEL        (0)

typedef struct
{
    uint8_t samples[PB_SAMPLES_N];
    PB_State_t state ;
    uint16_t pressed_time;
    uint16_t released_time ;
}PB_Info_t ;

static PB_Info_t pb_data[PB_MAX_N];

void PB_Init(PB_t push_button , PB_State_t initial_state)
{
    switch(push_button)
    {
    case PB_PLUS :
        {
            GPIO_InitPortPin(PB_PLUS_PORT_CMD ,PB_PLUS_PIN , GPIO_Input);
            break ;
        }
    case PB_MINUS:
        {
            GPIO_InitPortPin(PB_MINUS_PORT_CMD , PB_MINUS_PIN , GPIO_Input);
            break;
        }
    case PB_DISPLAY:
        {
            GPIO_InitPortPin(PB_DISPLAY_PORT_CMD , PB_DISPLAY_PIN , GPIO_Input);
            break ;
        }
    case PB_TIMER:
        {
            GPIO_InitPortPin(PB_TIMER_PORT_CMD , PB_TIMER_PIN , GPIO_Input);
            break;
        }
    default :
        {
            /*Should not be here !*/
            break ;
        }
    }

    switch(initial_state)
    {
    case PB_RELEASED:
    case PB_PRE_RELEASED :
        {
            pb_data[push_button].samples[0]=PB_RELEASED_VOLTAGE_LEVEL ;
            pb_data[push_button].samples[1]=PB_RELEASED_VOLTAGE_LEVEL ;
            break;
        }
    case PB_PRESSED :
    case PB_PRE_PRESSED:
        {
            pb_data[push_button].samples[0]=PB_PRESSED_VOLTAGE_LEVEL ;
            pb_data[push_button].samples[1]=PB_PRESSED_VOLTAGE_LEVEL ;
        }
    default :
        {
            /*Should not be here !*/
            break ;
        }

    }

    PB_SetState(push_button , initial_state);
    pb_data[push_button].pressed_time = 0 ;
    pb_data[push_button].released_time = 0;

}

void PB_Update(void)
{
    PB_t current_pb ;
    uint8_t current_sample ;
    static uint8_t counter_ms = 0;

    counter_ms += OS_TICK_MS ;
    if(counter_ms != PB_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0;

    for (current_pb =0 ; current_pb < PB_MAX_N ;++ current_pb)
    {
        /*Update samples */
        for(current_sample = 0 ; current_sample < PB_SAMPLES_N - 1 ; ++ current_sample)
        {
            pb_data[current_pb].samples[current_sample] = pb_data[current_pb].samples[current_sample + 1] ;
        }

        switch(current_pb)
        {
        case PB_PLUS :
            {
                pb_data[current_pb].samples[current_sample] = GPIO_GetPortPin(PB_PLUS_PORT_DATA , PB_PLUS_PIN);
                break ;
            }
        case PB_MINUS :
            {
                pb_data[current_pb].samples[current_sample] = GPIO_GetPortPin(PB_MINUS_PORT_DATA , PB_MINUS_PIN);
                break ;
            }
        case PB_DISPLAY:
            {
                pb_data[current_pb].samples[current_sample] = GPIO_GetPortPin(PB_DISPLAY_PORT_DATA , PB_DISPLAY_PIN);
                break ;
            }
        case PB_TIMER :
            {
                pb_data[current_pb].samples[current_sample] = GPIO_GetPortPin(PB_TIMER_PORT_DATA , PB_TIMER_PIN);
            }
        default :
            {
                /*Should not be her !*/
                break;
            }
        }

        /*Update state*/
        switch(pb_data[current_pb].state)
        {
        case PB_RELEASED :
            {
                if((pb_data[current_pb].samples[0] == PB_PRESSED_VOLTAGE_LEVEL) &&
                   (pb_data[current_pb].samples[1] == PB_PRESSED_VOLTAGE_LEVEL))
                {
                    PB_SetState(current_pb, PB_PRE_PRESSED);
                    pb_data[current_pb].released_time = 0;
                }
                else
                {
                    if(PB_GetReleasedTime(current_pb) < PB_MAXIMUM_RELEASED_TIME_MS)
                    {
                        pb_data[current_pb].released_time += PB_TASK_PERIOD_MS ;
                    }
                }
                break;
            }
        case PB_PRE_PRESSED :
            {
                if((pb_data[current_pb].samples[0] == PB_PRESSED_VOLTAGE_LEVEL) &&
                   (pb_data[current_pb].samples[1] == PB_PRESSED_VOLTAGE_LEVEL))
                {
                    PB_SetState(current_pb, PB_PRESSED);
                }
                break ;
            }
        case PB_PRESSED :
            {
                if((pb_data[current_pb].samples[0] == PB_RELEASED_VOLTAGE_LEVEL) &&
                   (pb_data[current_pb].samples[1] == PB_RELEASED_VOLTAGE_LEVEL))
                {
                    PB_SetState(current_pb, PB_PRE_RELEASED);
                    pb_data[current_pb].pressed_time =0;
                }
                else
                {
                    if(PB_GetPressedTime(current_pb)<PB_MAXIMUM_PRESSED_TIME_MS)
                    {
                        pb_data[current_pb].pressed_time += PB_TASK_PERIOD_MS ;
                    }
                }
                break ;
            }
        case PB_PRE_RELEASED :
            {
                if((pb_data[current_pb].samples[1] == PB_RELEASED_VOLTAGE_LEVEL)  &&
                   (pb_data[current_pb].samples[1] == PB_RELEASED_VOLTAGE_LEVEL))
                {
                    PB_SetState(current_pb, PB_RELEASED);
                }
                break;
            }
        }
    }
}

void PB_SetState(PB_t push_button , PB_State_t state )
{
    pb_data[push_button].state =state;
}

PB_State_t PB_GetState(PB_t push_button)
{
    PB_State_t ret =PB_RELEASED;
    ret = pb_data[push_button].state;
    return ret ;
}

uint16_t PB_GetPressedTime (PB_t push_button)
{
    uint16_t ret = 0;
    ret = pb_data[push_button].pressed_time ;
    return ret ;
}

uint16_t PB_GetReleasedTime (PB_t push_button)
{
    uint16_t ret = 0;
    ret = pb_data[push_button].released_time ;
    return ret ;
}
