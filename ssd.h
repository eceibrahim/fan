#ifndef __SSD_H__
#define __SSD_H__

#define SSD_TASK_PERIOD_MS         (5)

typedef enum
{
    SSD_RIGHT = 0     ,
    SSD_MEDIUM_RIGHT  ,
    SSD_MEDIUM_LEFT   ,
    SSD_LEFT
}SSD_t ;

typedef enum
{
    SSD_OFF = 0,
    SSD_ON
}SSDState_t ;

typedef enum
{
    SSD_0 ,
    SSD_1 ,
    SSD_2 ,
    SSD_3 ,
    SSD_4 ,
    SSD_5 ,
    SSD_6 ,
    SSD_7 ,
    SSD_8 ,
    SSD_9 ,
    SSD_NULL ,
    SSD_H ,
    SSD_I
}SSDSymbol_t ;

void SSD_Init(SSD_t  ssd , SSDSymbol_t initial_symbol ,  SSDState_t initial_state);
void SSD_Update(void);
void SSD_SetSymbol(SSD_t ssd , SSDSymbol_t symbol);
SSDSymbol_t SSD_GetSymbol(SSD_t ssd);
void SSD_SetState(SSD_t ssd, SSDState_t state);
SSDState_t SSD_GetState(SSD_t ssd);
void SSD_SetDotState(SSDState_t state);
SSDState_t SSD_GetDotState(void);
void SSD_TurnOff(void);
void SSD_TurnOn(void);


#endif /*__SSD_H__*/
