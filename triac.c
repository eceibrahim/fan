#include "triac.h"
#include "Main.h"
#include "Port.h"
#include "fan_controller.h"

#define TRIAC_MAXIMUM_ANGLE                       (180)

extern uint8_t speed_angle ;

void TRIAC_Init(TriacState_t initial_state)
{
    GPIO_InitPortPin(TRIAC_PORT_CMD , TRIAC_PIN , GPIO_Output);
    GPIO_SetPortPinState(TRIAC_PORT_DATA ,TRIAC_PIN , initial_state);

}


void TRIAC_Update(void) // periodic interrupt released every  @56 us
{

    static uint8_t current_angle = 0 ;
    FAN_State_t fan_state ;

    fan_state = FAN_GetState() ;

    ++current_angle ;

    if((current_angle == speed_angle) && (fan_state != FAN_OFF))
    {
        GPIO_SetPortPinState(TRIAC_PORT_DATA ,TRIAC_PIN , TRIAC_ON);
    }
    else if (current_angle == 180)
    {
        current_angle = 0;
        GPIO_SetPortPinState(TRIAC_PORT_DATA ,TRIAC_PIN , TRIAC_OFF);
    }
}


