/*******************************************************************************************************************************//**
 *
 * @file		ADC.c
 * @proyect		TPO_Lpc_845_Project
 * @date		14:13:19
 * @author		Velazquez Lautaro
 * @subject		INFO II
 * @course		R2051
 *
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include <adc.h>
#include "fsl_clock.h"
#include "fsl_power.h"
#include "fsl_debug_console.h"
#include "uart.h"
#include <stdlib.h>
#include "Rele.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

#define DEMO_ADC_CLOCK_SOURCE          kCLOCK_Fro
#define DEMO_ADC_BASE                  ADC0
#define DEMO_ADC_SAMPLE_CHANNEL_NUMBER 0U
#define ADC_CHANNEL_1				   1U
#define DEMO_ADC_CLOCK_DIVIDER         1U

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

bool flag_automatizacion_persiana = false;

/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static adc_result_info_t adcResultInfoStruct;
static adc_result_info_t adcResultInfoStructlight;
static const uint32_t g_Adc_12bitFullRange = 4096U;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static void ADC_Configuration(void);

/***********************************************************************************************************************************
*** CONFIGURACION DE ERRORES
**********************************************************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE FUNCIONES PUBLICAS
 **********************************************************************************************************************************/

void adc_Init(void)
{
    /* Attach FRO clock to ADC0. */
    CLOCK_Select(kADC_Clk_From_Fro);	/*ADC clock source select // Establece el  FRO con un 0 en SYSCON->ADCCLKSEL */
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1U);	/*ADC clock divider // Se utiliza para dividir el clock en este caso pone 1 en SYSCON->ADCCLKDIV*/
    /* Power on ADC0. */
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);	/*SYSCON->PDRUNCFG->FROOUT_PD coloca un 0 en el bit 0*///sirve para alimentar el FRO
    uint32_t frequency = CLOCK_GetFreq(DEMO_ADC_CLOCK_SOURCE) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
    ADC_DoSelfCalibration(DEMO_ADC_BASE, frequency);
    ADC_Configuration();		//base->CTRL CLKDIV = 0x1
}

void SensorDeTemperatura_Read(void)
{
    ADC_DoSoftwareTriggerConvSeqA(DEMO_ADC_BASE);		//limpia buffer
    /* Wait for the converter to be done. */
	while (!ADC_GetChannelConversionResult(DEMO_ADC_BASE, DEMO_ADC_SAMPLE_CHANNEL_NUMBER, &adcResultInfoStruct))
	{
	}

	uint8_t tmp[3];
    sprintf(tmp,"T%i",(int)(((adcResultInfoStruct.result * 3300) / g_Adc_12bitFullRange) / 100));
	UART1_Send(tmp,3);
    //PRINTF("%c%i",tmp[0],tmp[1]);
}

void SensorDeIluminacion_Read()
{
    ADC_DoSoftwareTriggerConvSeqA(DEMO_ADC_BASE);		//limpia buffer
    /* Wait for the converter to be done. */
	while (!ADC_GetChannelConversionResult(DEMO_ADC_BASE, ADC_CHANNEL_1, &adcResultInfoStructlight))
	{
	}

	uint8_t data;

	if(adcResultInfoStructlight.result > 0x555)
	{
		data = 1;
	}
	else
	{
		data = 0;
	}

	if(flag_automatizacion_persiana)
	{
		if(data == 1)
		{
			SubirPersiana();
		}
		else
		{
			BajarPersiana();
		}
	}
}
/***********************************************************************************************************************************
 *** IMPLEMNTACION DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static void ADC_Configuration(void)
{
    adc_config_t adcConfigStruct;
    adc_conv_seq_config_t adcConvSeqConfigStruct;

/* Configure the converter. */
    adcConfigStruct.clockMode = kADC_ClockSynchronousMode; /* Using sync clock source. */                             /* FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE */
    adcConfigStruct.clockDividerNumber = DEMO_ADC_CLOCK_DIVIDER;
    adcConfigStruct.enableLowPowerMode = false;
    adcConfigStruct.voltageRange = kADC_HighVoltageRange;

    ADC_Init(DEMO_ADC_BASE, &adcConfigStruct);

    /* Enable channel DEMO_ADC_SAMPLE_CHANNEL_NUMBER's conversion in Sequence A. */
    adcConvSeqConfigStruct.channelMask 		= (1U << DEMO_ADC_SAMPLE_CHANNEL_NUMBER) | (1U << ADC_CHANNEL_1); /* Includes channel DEMO_ADC_SAMPLE_CHANNEL_NUMBER. */
    adcConvSeqConfigStruct.triggerMask      = 0U;
    adcConvSeqConfigStruct.triggerPolarity  = kADC_TriggerPolarityPositiveEdge;
    adcConvSeqConfigStruct.enableSingleStep = false;
    adcConvSeqConfigStruct.enableSyncBypass = false;
    adcConvSeqConfigStruct.interruptMode    = kADC_InterruptForEachSequence;
    ADC_SetConvSeqAConfig(DEMO_ADC_BASE, &adcConvSeqConfigStruct);
    ADC_EnableConvSeqA(DEMO_ADC_BASE, true); /* Enable the conversion sequence A. */
    /* Clear the result register. */
    ADC_DoSoftwareTriggerConvSeqA(DEMO_ADC_BASE);
    while (!ADC_GetChannelConversionResult(DEMO_ADC_BASE, DEMO_ADC_SAMPLE_CHANNEL_NUMBER, &adcResultInfoStruct))
    {
    }
    //ADC_GetConvSeqAGlobalConversionResult(DEMO_ADC_BASE, &adcResultInfoStruct);
}

/*--------------------------------------------------------------------------------------------------------------------------------*/
