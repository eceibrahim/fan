#ifndef __SLIDER_H__
#define __SLIDER_H__

#define SLIDER_TASK_PERIOD_MS          (500)

void SLIDER_Init(void);
void SLIDER_Update(void);
uint8_t SLIDER_GetValue(void);

#endif /*__SLIDER_H__*/
