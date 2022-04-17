/*******************************************************************************************************************************//**
 *
 * @file		Dimmer.c
 * @proyect		TPO_Lpc_845_Project
 * @date		17:27:10
 * @author		Velazquez Lautaro
 * @subject		INFO II
 * @course		R2051
 *
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "Dimmer.h"
#include "fsl_debug_console.h"
#include "Timer.h"
#include "fsl_gpio.h"
#include "fsl_ctimer.h"
#include <stdio.h>
#include <time.h>
#include "uart.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

#define CTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)

#define DIMMER_0 21

#define DIMMER_ON  1
#define DIMMER_OFF 0

#define PORT_0 0
#define PORT_1 1

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

static ctimer_match_config_t matchConfig0;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

int timer = 1;

/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static gpio_pin_config_t config =
{
	kGPIO_DigitalOutput,
 	0,
};

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status)
{
	matchConfig0.matchValue = (timer*CTIMER_CLK_FREQ)/10000;
	matchConfig0.outControl = kCTIMER_Output_Set;
	CTIMER_SetupMatch(CTIMER0, kCTIMER_Match_0, &matchConfig0);
	CTIMER_Reset(CTIMER0);
}

/***********************************************************************************************************************************
*** CONFIGURACION DE ERRORES
**********************************************************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE FUNCIONES PUBLICAS
 **********************************************************************************************************************************/

void DetectorCruceXCero_Init()
{
	GPIO_PortInit(GPIO, PORT_1);
	GPIO_PinInit(GPIO, PORT_1, DIMMER_0, &config);

    /* Connect trigger sources to PINT */
    SYSCON_AttachSignal(SYSCON, kPINT_PinInt0, kSYSCON_GpioPort0Pin1ToPintsel);

    /* Initialize PINT */
    PINT_Init(PINT);

    /* Setup Pin Interrupt 0 for rising edge */
    PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableRiseEdge, pint_intr_callback);

    /* Enable callbacks for PINT0 by Index */
    PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0);

    ctimer_config_t config;
    CTIMER_GetDefaultConfig(&config);
    CTIMER_Init(CTIMER0, &config);

    /* Configuration 0 */
    matchConfig0.enableCounterReset = false;
    matchConfig0.enableCounterStop  = false;
    matchConfig0.matchValue         = CTIMER_CLK_FREQ/10000;
    matchConfig0.outControl         = kCTIMER_Output_NoAction;
    matchConfig0.outPinInitState    = false;
    matchConfig0.enableInterrupt    = false;

    CTIMER_SetupMatch(CTIMER0, kCTIMER_Match_0, &matchConfig0);
    CTIMER_StartTimer(CTIMER0);
}

/***********************************************************************************************************************************
 *** IMPLEMNTACION DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------*/

