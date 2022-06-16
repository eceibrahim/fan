#ifndef __SPEED_H__
#define __SPEED_H__

#define SPEED_TASK_PERIOD_MS        (80)

typedef enum
{
    SPEED_MINIMUM =0 ,
    SPEED_MEDIUM     ,
    SPEED_MAXIMUM
}Speed_t;

void SPEED_Init(Speed_t initial_speed);
void SPEED_Update(void);
void SPEED_SetSpeed(Speed_t value);
Speed_t SPEED_GetSpeed(void);

#endif /*__SPEED_H__*/
