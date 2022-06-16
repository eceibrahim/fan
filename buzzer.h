#ifndef __BUZZER_H__
#define __BUZZER_H__


#define BUZZER_TASK_PERIOD_MS                  (10)

typedef enum
{
    BUZZER_OFF = 0 ,
    BUZZER_ON
}BUZZER_State_t ;

void BUZZER_Init(BUZZER_State_t initial_state);
void BUZZER_Update(void);
void BUZZER_SetState(BUZZER_State_t state);
BUZZER_State_t BUZZER_GetState(void);

#endif /*__BUZZER_H__*/
