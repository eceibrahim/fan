#include "ssd.h"
#include "Port.h"
#include "Main.h"

#define SSD_MAX_N                   (4)

static SSDSymbol_t ssd_symbols[SSD_MAX_N];

static SSDState_t ssd_dot_state ;

static SSD_t current_ssd ;
static SSD_t previous_ssd ;

static const ssd_data[] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b00000000,
    0b01110110,
    0b00110000,
};

static void SSD_PutData(uint8_t data);

void SSD_Init(SSD_t  ssd , SSDSymbol_t initial_symbol ,  SSDState_t initial_state)
{
    GPIO_InitPortPin(SSD_DATA_PORT_CMD , SSD_DATA_PINS , GPIO_Output);
    GPIO_InitPortPin(SSD_DOT_PORT_CMD , SSD_DOT_PIN , GPIO_Output) ;

    switch(ssd)
    {
    case SSD_RIGHT :
        {
            GPIO_InitPortPin(SSD_RIGHT_PORT_CMD , SSD_RIGHT_PIN , GPIO_Output);
            break;
        }
    case SSD_MEDIUM_RIGHT:
        {
            GPIO_InitPortPin(SSD_MEDIUM_RIGHT_PORT_CMD , SSD_MEDIUM_RIGHT_PIN , GPIO_Output);
            break ;
        }
    case SSD_MEDIUM_LEFT :
        {
            GPIO_InitPortPin(SSD_MEDIUM_LEFT_PORT_CMD , SSD_MEDIUM_LEFT_PIN , GPIO_Output);
            break;
        }
    case SSD_LEFT:
        {
            GPIO_InitPortPin(SSD_LEFT_PORT_CMD , SSD_LEFT_PIN , GPIO_Output);
            break ;
        }
    default :
        {
            /*Should not be here !*/
            break ;
        }
    }
    SSD_SetState(ssd , initial_state);
    SSD_SetSymbol(ssd , initial_symbol);
    SSD_SetDotState(SSD_OFF);
    current_ssd = SSD_RIGHT ;
}

void SSD_Update(void)
{
    SSDSymbol_t symbol ;

    /*Turn off all ssds*/
    SSD_SetState(SSD_RIGHT , SSD_OFF);
    SSD_SetState(SSD_MEDIUM_RIGHT , SSD_OFF);
    SSD_SetState(SSD_MEDIUM_LEFT , SSD_OFF );
    SSD_SetState(SSD_LEFT , SSD_OFF);

    /*Put data*/
    symbol = SSD_GetSymbol(current_ssd) ;
    SSD_PutData(ssd_data[symbol]);

    /*Turn on current ssd*/
    SSD_SetState(current_ssd , SSD_ON);

    previous_ssd = current_ssd ;

    /*Go to next ssd*/
    if(current_ssd ==  SSD_LEFT)
    {
        current_ssd = SSD_RIGHT ;
    }
    else
    {
        ++ current_ssd ;
    }
}

void SSD_SetSymbol(SSD_t ssd , SSDSymbol_t symbol)
{
    ssd_symbols[ssd] = symbol ;
}

SSDSymbol_t SSD_GetSymbol(SSD_t ssd)
{
    SSDSymbol_t ret ;
    ret = ssd_symbols[ssd] ;
    return ret ;
}

void SSD_SetState(SSD_t ssd, SSDState_t state)
{
    switch(ssd)
    {
    case SSD_RIGHT :
        {
            GPIO_SetPortPinState(SSD_RIGHT_PORT_DATA , SSD_RIGHT_PIN , state);
            break;
        }
    case SSD_MEDIUM_RIGHT:
        {
            GPIO_SetPortPinState(SSD_MEDIUM_RIGHT_PORT_DATA , SSD_MEDIUM_RIGHT_PIN , state);
            break ;
        }
    case SSD_MEDIUM_LEFT :
        {
            GPIO_SetPortPinState(SSD_MEDIUM_LEFT_PORT_DATA , SSD_MEDIUM_LEFT_PIN , state);
            GPIO_SetPortPinState(SSD_DOT_PORT_DATA , SSD_DOT_PIN ,ssd_dot_state);
            break;
        }
    case SSD_LEFT:
        {
            GPIO_SetPortPinState(SSD_LEFT_PORT_DATA , SSD_LEFT_PIN , state);
            break ;
        }
    default :
        {
            /*Should not be here !*/
            break ;
        }
    }
}

SSDState_t SSD_GetState(SSD_t ssd)
{
    SSDState_t ret = SSD_OFF;
    switch(ssd)
    {
    case SSD_RIGHT :
        {
            ret = GPIO_GetPortPin(SSD_RIGHT_PORT_DATA , SSD_RIGHT_PIN );
            break;
        }
    case SSD_MEDIUM_RIGHT:
        {
            ret = GPIO_GetPortPin(SSD_MEDIUM_RIGHT_PORT_DATA , SSD_MEDIUM_RIGHT_PIN );
            break ;
        }
    case SSD_MEDIUM_LEFT :
        {
            ret = GPIO_GetPortPin(SSD_MEDIUM_LEFT_PORT_DATA , SSD_MEDIUM_LEFT_PIN);
            break;
        }
    case SSD_LEFT:
        {
            ret = GPIO_GetPortPin(SSD_LEFT_PORT_DATA , SSD_LEFT_PIN);
            break ;
        }
    default :
        {
            /*Should not be here !*/
            break ;
        }
    }
    return ret;
}

void SSD_SetDotState(SSDState_t state)
{
    ssd_dot_state =  state ;
}

SSDState_t SSD_GetDotState(void)
{
    SSDState_t ret ;
    ret = ssd_dot_state ;
    return ret;
}

static void SSD_PutData(uint8_t data)
{
    GPIO_SetPort(SSD_DATA_PORT ,data);
}

void SSD_TurnOff(void)
{
    SSD_SetState(previous_ssd , SSD_OFF);
}

void SSD_TurnOn(void)
{
    SSD_PutData(ssd_data[ssd_symbols[previous_ssd]]);
    SSD_SetState(previous_ssd , SSD_ON);
}

