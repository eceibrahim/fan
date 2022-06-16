#ifndef __FAN_CONTROLLER_H__
#define __FAN_CONTROLLER_H__

#include "Main.h"

#define FAN_TASK_PERIOD_MS       (20)

typedef enum
{
    FAN_INIT = 0 ,
    FAN_OFF ,
    FAN_SPEED ,
    FAN_DISPLAY ,
    FAN_TIMER
}FAN_State_t ;

typedef struct
{
    uint8_t hours ;
    uint8_t minutes ;
}FAN_Time_t ;

void FAN_Init(void);
void FAN_Update(void) ;
FAN_State_t FAN_GetState(void);
void FAN_GetWantedTime(FAN_Time_t *time);
void FAN_GetCurrentTime(FAN_Time_t *time);
#endif /*__FAN_CONTROLLER_H__*/
