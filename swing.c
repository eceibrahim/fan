#include "swing.h"
#include "Main.h"
#include "Port.h"
#include "buzzer.h"
#include "slider.h"
#include "os.h"

static uint8_t current_swing ;
static uint8_t previous_swing ;

static const uint8_t swing_values[] =
{
    0b00000000,
    0b00000001,
    0b00000010,
    0b00000011,
    0b00000100,
    0b00000101,
    0b00000110,
    0b00000111,
    0b00001000
};

static uint8_t SWING_GetBitStatus(uint8_t swing , uint8_t poistion);

void SWING_Init(void)
{
    GPIO_InitPortPin(SWING_PORT_CMD , SWING_PIN_0 ,GPIO_Output);
    GPIO_InitPortPin(SWING_PORT_CMD , SWING_PIN_1 ,GPIO_Output);
    GPIO_InitPortPin(SWING_PORT_CMD , SWING_PIN_2 ,GPIO_Output);
    GPIO_InitPortPin(SWING_PORT_CMD , SWING_PIN_3 ,GPIO_Output);

    current_swing = 0;
    previous_swing = 0 ;
}

void SWING_Update(void)
{

    uint8_t slider_value ;
    static uint16_t counter_ms = 0;

    counter_ms += OS_TICK_MS ;
    if(counter_ms != SWING_TASK_PERIOD_MS)
    {
        return ;
    }
    counter_ms = 0;


    slider_value = SLIDER_GetValue();
    current_swing = swing_values[slider_value];

    GPIO_SetPortPinState(SWING_PORT_DATA , SWING_PIN_0 ,SWING_GetBitStatus(current_swing , 0));
    GPIO_SetPortPinState(SWING_PORT_DATA , SWING_PIN_1 ,SWING_GetBitStatus(current_swing , 1));
    GPIO_SetPortPinState(SWING_PORT_DATA , SWING_PIN_2 ,SWING_GetBitStatus(current_swing , 2));
    GPIO_SetPortPinState(SWING_PORT_DATA , SWING_PIN_3 ,SWING_GetBitStatus(current_swing , 3));
    if(current_swing != previous_swing)
    {
        BUZZER_SetState(BUZZER_ON);
    }
    previous_swing = current_swing ;
}

static uint8_t SWING_GetBitStatus(uint8_t swing , uint8_t position)
{
    uint8_t ret ;
    ret = (swing & (1<< position)) ? 1 : 0;
    return ret;
}
