#ifndef __PORT_H__
#define __PORT_H__

#define MODULE_BUZZER                   (1)
#define MODULE_SSD                      (1)
#define MODULE_TRIAC                    (1)
#define MODULE_SLIDER                   (1)
#define MODULE_PB                       (1)
#define MODULE_SWING                    (1)
#define MODULE_LCD                      (1)



#if MODULE_BUZZER
#define BUZZER_PORT_CMD                 GPIOA_CMD
#define BUZZER_PORT_DATA                GPIOA_DATA
#define BUZZER_PIN                      GPIO_PIN_5
#endif /*MODULE_BUZZER*/


#if MODULE_SSD
#define SSD_DATA_PORT_CMD               GPIOD_CMD
#define SSD_DATA_PORT                   GPIOD_DATA
#define SSD_DATA_PINS                   GPIO_PIN_ALL

#define SSD_RIGHT_PORT_CMD              GPIOB_CMD
#define SSD_RIGHT_PORT_DATA             GPIOB_DATA
#define SSD_RIGHT_PIN                   GPIO_PIN_4

#define SSD_MEDIUM_RIGHT_PORT_CMD       GPIOB_CMD
#define SSD_MEDIUM_RIGHT_PORT_DATA      GPIOB_DATA
#define SSD_MEDIUM_RIGHT_PIN            GPIO_PIN_5

#define SSD_MEDIUM_LEFT_PORT_CMD        GPIOB_CMD
#define SSD_MEDIUM_LEFT_PORT_DATA       GPIOB_DATA
#define SSD_MEDIUM_LEFT_PIN             GPIO_PIN_6

#define SSD_LEFT_PORT_CMD               GPIOB_CMD
#define SSD_LEFT_PORT_DATA              GPIOB_DATA
#define SSD_LEFT_PIN                    GPIO_PIN_7

#define SSD_DOT_PORT_CMD                GPIOD_CMD
#define SSD_DOT_PORT_DATA               GPIOD_DATA
#define SSD_DOT_PIN                     GPIO_PIN_7
#endif /*MODULE_SSD*/


#if MODULE_TRIAC
#define TRIAC_PORT_CMD                  GPIOC_CMD
#define TRIAC_PORT_DATA                 GPIOC_DATA
#define TRIAC_PIN                       GPIO_PIN_4
#endif /*MODULE_TRIAC*/


#if MODULE_PB
#define PB_PLUS_PORT_CMD                GPIOB_CMD
#define PB_PLUS_PORT_DATA               GPIOB_DATA
#define PB_PLUS_PIN                     GPIO_PIN_0

#define PB_MINUS_PORT_CMD               GPIOB_CMD
#define PB_MINUS_PORT_DATA              GPIOB_DATA
#define PB_MINUS_PIN                    GPIO_PIN_1

#define PB_DISPLAY_PORT_CMD             GPIOB_CMD
#define PB_DISPLAY_PORT_DATA            GPIOB_DATA
#define PB_DISPLAY_PIN                  GPIO_PIN_2

#define PB_TIMER_PORT_CMD               GPIOB_CMD
#define PB_TIMER_PORT_DATA              GPIOB_DATA
#define PB_TIMER_PIN                    GPIO_PIN_3
#endif /*MODULE_PB*/


#if MODULE_SWING
#define SWING_PORT_CMD                  GPIOC_CMD
#define SWING_PORT_DATA                 GPIOC_DATA
#define SWING_PIN_0                     GPIO_PIN_0
#define SWING_PIN_1                     GPIO_PIN_1
#define SWING_PIN_2                     GPIO_PIN_2
#define SWING_PIN_3                     GPIO_PIN_3
#endif /*MODULE_SWING*/


#if MODULE_LCD
#define LCD_DATA_PORT_CMD              GPIOD_CMD
#define LCD_DATA_PORT                  GPIOD_DATA
#define LCD_DATA_PINS                  GPIO_PIN_ALL

#define LCD_E_PORT_CMD                 GPIOE_CMD
#define LCD_E_PORT_DATA                GPIOE_DATA
#define LCD_E_PIN                      GPIO_PIN_1

#define LCD_RS_PORT_CMD               GPIOE_CMD
#define LCD_RS_PORT_DATA              GPIOE_DATA
#define LCD_RS_PIN                    GPIO_PIN_0
#endif /*MODULE_LCD*/

#endif /*__PORT_H__*/
