#ifndef __MAIN_H__
#define __MAIN_H__

#include <pic16f877a.h>
#include <stdint.h>

#define MODULE_GPIO        (1)
#define MODULE_ADC         (1)
#define MODULE_TMR         (1)


#if MODULE_GPIO
#define GPIO_Output     (0)
#define GPIO_Input      (1)
#define GPIO_PIN_0      (0x01)
#define GPIO_PIN_1      (0x02)
#define GPIO_PIN_2      (0x04)
#define GPIO_PIN_3      (0x08)
#define GPIO_PIN_4      (0x10)
#define GPIO_PIN_5      (0x20)
#define GPIO_PIN_6      (0x40)
#define GPIO_PIN_7      (0x80)
#define GPIO_PIN_ALL    (0xFF)
#define GPIOA_CMD       TRISA
#define GPIOA_DATA      PORTA
#define GPIOB_CMD       TRISB
#define GPIOB_DATA      PORTB
#define GPIOD_CMD       TRISD
#define GPIOD_DATA      PORTD
#define GPIOC_CMD       TRISC
#define GPIOC_DATA      PORTC
#define GPIOE_CMD       TRISE
#define GPIOE_DATA      PORTE
#define GPIO_InitPortPin(GPIOx , pin , initial_mode)   (GPIOx = (initial_mode) ? (GPIOx|pin) : (GPIOx&(~pin)))
#define GPIO_SetPortPinState(GPIOx, pin , state)       (GPIOx = (state) ? (GPIOx|pin) : (GPIOx&(~pin)))
#define GPIO_GetPortPin(GPIOx,pin)                     ((GPIOx & pin > 0) ? 1 : 0)
#define GPIO_SetPort(GPIOx,value)                      (GPIOx = value)
#define GPIO_GetPort(GPIOx)                            (GPIOx)
#endif  /*MODULE_GPIO*/

#if MODULE_ADC
#define ADC_SELECT_CHANNEL_1    CHS2=0;\
                                CHS1=0;\
                                CHS0=1;\
                                TRISA|=0x02
#define ADC_SET_STATE(STATE)   (ADON=STATE)
#define ADC_RIGHT_JUSTIFIED    (ADFM = 1)
#define ADC_SET_CLOCK_DIV_64    ADCS0=0;\
                                ADCS1=1;\
                                ADCS2=1
#define ADC_START_CONVERSION   (GO = 1)
#define ADC_CONFIGURE_PORT     (PCFG1=1)
#define ADC_GET_RESULT         ((((uint16_t)ADRESH)<<8)|(ADRESL))
#endif  /*MODULE_ADC*/

#if MODULE_TMR
#define TMR_SET_PRESCALER_2  	PS2 = 0; \
								PS1 = 0; \
								PS0 = 0; \
								PSA = 0
#define TMR_ENABLE_INTERRUPT	      (TMR0IE = 1)
#define GLOBAL_INTERRUPT_ENABLE	      (GIE = 1)
#define GLOBAL_INTERRUPT_DISABLE      (GIE = 0)
#define TMR_ENABLE_CLOCK              (T0CS=0)
#define TMR_DISABLE_CLOCK             (T0CS=1)
#define TMR_CLEAR_FLAG			      (TMR0IF = 0)
#define TMR_REGISTER_VALUE       	  (TMR0=200)
#endif  /*MODULE_TMR*/

#endif /*__MAIN_H__*/
