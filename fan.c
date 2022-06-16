#include "os.h"
#include "Main.h"
#include "push_button.h"
#include "slider.h"
#include "fan_controller.h"
#include "swing.h"
#include "speed.h"
#include "ssd_display.h"
#include "lcd_display.h"
#include "ssd.h"
#include "lcd.h"
#include "buzzer.h"
#include "triac.h"

uint16_t __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;

int main(void)
{

    OS_Init() ;
    PB_Init(PB_PLUS , PB_RELEASED);
    PB_Init(PB_MINUS , PB_RELEASED);
    PB_Init(PB_DISPLAY , PB_RELEASED);
    PB_Init(PB_TIMER , PB_RELEASED);
    TRIAC_Init(TRIAC_OFF);
    SLIDER_Init();
    FAN_Init();
    SWING_Init();
    SPEED_Init(SPEED_MINIMUM);
    LCD_InitDisplay();
    LCD_Init();
    SSD_InitDisplay();
    SSD_Init(SSD_RIGHT , SSD_NULL , SSD_OFF);
    SSD_Init(SSD_MEDIUM_RIGHT , SSD_NULL , SSD_OFF) ;
    SSD_Init(SSD_MEDIUM_LEFT , SSD_NULL , SSD_OFF );
    SSD_Init(SSD_LEFT , SSD_NULL , SSD_OFF);
    BUZZER_Init(BUZZER_OFF);
    OS_Start();

    while(1)
    {
        OS_DelayMS();
        SSD_UpdateDisplay();
        SSD_Update() ;
        PB_Update();
        SLIDER_Update();
        FAN_Update();
        SWING_Update();
        SPEED_Update();
        LCD_UpdateDisplay();
        LCD_Update();
        BUZZER_Update();
    }
  



    return 0 ;
}
