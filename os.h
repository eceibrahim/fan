#ifndef __OS_H__
#define __OS_H__

#define OS_TICK_MS             (5)

void OS_Init(void);
void OS_Start(void);
void OS_Update(void) __interrupt 1 ;
void OS_DelayMS(void) ;

#endif /*__OS_H__*/
