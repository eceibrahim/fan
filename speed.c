#include "speed.h"
#include "Main.h"
#include "os.h"

#define SPEED_INITIAL_ANGLE       (170)

static Speed_t speed ;

static const speed_angles[] =
{
    140 ,
    90  ,
    10
};

static uint8_t wanted_angle ;

uint8_t speed_angle ;


void SPEED_Init(Speed_t initial_speed)
{
    speed = initial_speed ;
    wanted_angle =speed_angles[initial_speed];
    speed_angle = SPEED_INITIAL_ANGLE ;
}

void SPEED_Update(void) //@80 ms
{
    static uint8_t counter_ms  =0;

    counter_ms += OS_TICK_MS ;
    if(counter_ms != SPEED_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0;

    if(speed_angle >  wanted_angle)
    {
        speed_angle -- ;
    }
    else if (speed_angle < wanted_angle)
    {
        speed_angle ++ ;
    }
    else
    {
        /*Do nothing here .*/
    }
}

void SPEED_SetSpeed(Speed_t value)
{
    speed = value ;
    wanted_angle = speed_angles[value];
}

Speed_t SPEED_GetSpeed(void)
{
    Speed_t ret ;
    ret = speed;
    return ret;
}
