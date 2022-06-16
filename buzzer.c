#include "Main.h"
#include "Port.h"
#include "buzzer.h"
#include "os.h"


#define BUZZER_ON_DURATION_MS            (2000)

static BUZZER_State_t buzzer_state ;

void BUZZER_Init(BUZZER_State_t initial_state)
{
    GPIO_InitPortPin(BUZZER_PORT_CMD , BUZZER_PIN , GPIO_Output);
    GPIO_SetPortPinState(BUZZER_PORT_DATA , BUZZER_PIN , initial_state);
    buzzer_state = initial_state ;
}

void BUZZER_Update(void)
{
    static uint16_t time_in_state_ms  = 0;
    static uint8_t counter_ms  =0 ;

    counter_ms += OS_TICK_MS ;
    if(counter_ms != BUZZER_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0;

    switch(buzzer_state)
    {
    case BUZZER_OFF :
        {

            break ;
        }
    case BUZZER_ON :
        {
            time_in_state_ms += BUZZER_TASK_PERIOD_MS ;
            if(time_in_state_ms == BUZZER_ON_DURATION_MS)
            {
                time_in_state_ms = 0;
                buzzer_state = BUZZER_OFF ;
            }
        }
    default:
        {
            /*Should not be here !*/
            break ;
        }
    }
    GPIO_SetPortPinState(BUZZER_PORT_DATA , BUZZER_PIN , buzzer_state);
}

void BUZZER_SetState(BUZZER_State_t state)
{
    buzzer_state = state ;
}

BUZZER_State_t BUZZER_GetState(void)
{
    BUZZER_State_t ret ;
    ret = buzzer_state ;
    return ret ;
}
