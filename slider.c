#include "Main.h"
#include "slider.h"
#include "os.h"

static uint16_t slider_value ;


void SLIDER_Init(void)
{
    ADC_CONFIGURE_PORT;
    ADC_SELECT_CHANNEL_1;
    ADC_RIGHT_JUSTIFIED;
    ADC_SET_CLOCK_DIV_64;
    ADC_SET_STATE(1);
    ADC_START_CONVERSION;
    slider_value = 0;
}

void SLIDER_Update(void)
{
    static uint16_t counter_ms = 0;

    counter_ms += OS_TICK_MS ;
    if(counter_ms != SLIDER_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0;

    slider_value = ADC_GET_RESULT ;
    slider_value = slider_value / 127 ;
    ADC_START_CONVERSION;
}

uint8_t SLIDER_GetValue(void)
{
    uint8_t ret ;
    ret = slider_value ;
    return ret ;
}
