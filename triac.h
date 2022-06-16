#ifndef __TRIAC_H__
#define __TRIAC_H__

typedef enum
{
    TRIAC_OFF =0 ,
    TRIAC_ON
}TriacState_t ;

void TRIAC_Init(TriacState_t initial_state);
void TRIAC_Update(void) ;


#endif /*__TRIAC_H__*/
