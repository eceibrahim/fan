#ifndef __PUSH_BUTTON_H__
#define __PUSH_BUTTON_H__

#include "Main.h"

#define PB_TASK_PERIOD_MS                    (20)

#define PB_MAXIMUM_PRESSED_TIME_MS           (10000)
#define PB_MAXIMUM_RELEASED_TIME_MS          (10000)

typedef enum
{
    PB_PLUS = 0,
    PB_MINUS   ,
    PB_DISPLAY ,
    PB_TIMER
}PB_t;

typedef enum
{
    PB_RELEASED =0 ,
    PB_PRE_PRESSED ,
    PB_PRESSED ,
    PB_PRE_RELEASED
}PB_State_t ;

void PB_Init(PB_t push_button , PB_State_t initial_state);
void PB_Update(void);
void PB_SetState(PB_t push_button , PB_State_t state );
PB_State_t PB_GetState(PB_t push_button);
uint16_t PB_GetPressedTime (PB_t push_button);
uint16_t PB_GetReleasedTime (PB_t push_button);

#endif /*__PUSH_BUTTON_H__*/

