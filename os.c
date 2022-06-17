#include "os.h"
#include "Main.h"
#include "triac.h"
#include "ssd.h"
#include "ssd_display.h"

static volatile uint32_t os_counter_us  ;

void OS_Init(void)
{
    os_counter_us= 0 ;

    /*Initialize timer H/W*/
    TMR_SET_PRESCALER_2;
    TMR_DISABLE_CLOCK;

  
}

void OS_Start(void)
{
    /*Start Interrupt */
    TMR_REGISTER_VALUE;
    TMR_ENABLE_INTERRUPT;
    GLOBAL_INTERRUPT_ENABLE;
    TMR_ENABLE_CLOCK;
}

void OS_Update(void) __interrupt 1 // @56 us
{
    os_counter_us += 56 ;

    TRIAC_Update();

    TMR_REGISTER_VALUE;
    TMR_CLEAR_FLAG;
}

void OS_DelayMS(void)
{
    uint32_t time_us = OS_TICK_MS * 1000UL ;
    while(os_counter_us < time_us);
    os_counter_us = 0 ;
}
