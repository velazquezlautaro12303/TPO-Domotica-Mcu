/*******************************************************************************************************************************//**
 *
 * @file		uart.c
 * @proyect		TPO_Lpc_845_Project
 * @date		10:12:50
 * @author		Velazquez Lautaro
 * @subject		INFO II
 * @course		R2051
 *
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "uart.h"
#include "fsl_usart.h"
#include "fsl_clock.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

#define		UART1_TAMANIO_COLA_RX					20
#define		UART1_TAMANIO_COLA_TX					20

typedef struct
{
	uint8_t			Datos_Validos;
	uint16_t		Tamanio;
	uint8_t			Buffer[UART1_TAMANIO_COLA_RX];
	uint16_t		Indice_in, Indice_out;
}STRUCT_RX;

typedef struct
{
	uint8_t			Datos_Validos;
	uint16_t		Tamanio;
	uint8_t			Buffer[UART1_TAMANIO_COLA_TX];
	uint16_t		Indice_in, Indice_out;
}STRUCT_TX;

typedef struct
{
	STRUCT_RX					RX;
	STRUCT_TX					TX;
}UART1_Struct;

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

#define USART_CLK_FREQ CLOCK_GetFreq(kCLOCK_MainClk)

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

UART1_Struct		UART1;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static void UART1_PushTx(uint8_t dato);
static int32_t UART1_PopTx( void );
static void UART1_PushRx(uint8_t dato);
static int32_t UART1_PopRx( void );

/***********************************************************************************************************************************
*** CONFIGURACION DE ERRORES
**********************************************************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE FUNCIONES PUBLICAS
 **********************************************************************************************************************************/

void USART1_IRQHandler(void)
{
    uint8_t data;
	int32_t Temporal;

    /* If TX is ready to send, and the `Enter` key is detected, send the received characters. */
    if (kUSART_TxReady & USART_GetStatusFlags(USART1))
    {
		Temporal = UART1_PopTx();

        if(Temporal >= 0)
        {
            USART_WriteByte(USART1, Temporal);
        }
		else
		{
            USART_DisableInterrupts(USART1, kUSART_TxReadyInterruptEnable);
			UART1.TX.Datos_Validos = 0;
		}
    }

    /* If this Rx read flag is set, read data to buffer. */
    if (kUSART_RxReady & USART_GetStatusFlags(USART1))
    {
        data                      = USART_ReadByte(USART1);
		UART1_PushRx(data);
    }
}

void USARTInit(void)
{
	CLOCK_Select(kUART1_Clk_From_MainClk);

    usart_config_t config;
    /* Default config by using USART_GetDefaultConfig():
     * config.baudRate_Bps = 9600U;
     * config.parityMode = kUSART_ParityDisabled;
     * config.stopBitCount = kUSART_OneStopBit;
     * config.bitCountPerChar = kUSART_8BitsPerChar;
     * config.loopback = false;
     * config.enableRx = false;
     * config.enableTx = false;
     * config.syncMode = kUSART_SyncModeDisabled;
     */
    USART_GetDefaultConfig(&config);
    config.enableRx     = true;
    config.enableTx     = true;
    config.baudRate_Bps = 9600;

    /* Initialize the USART with configuration. */
    USART_Init(USART1, &config, USART_CLK_FREQ);

    /* Enable USART RX ready interrupt. */
    USART_EnableInterrupts(USART1, kUSART_RxReadyInterruptEnable);
    EnableIRQ(USART1_IRQn);
}

void UART1_Send(uint8_t *Datos, uint32_t Tamanio)
{
	uint32_t i;

	for(i = 0 ; i < Tamanio ; i++)
		UART1_PushTx(Datos[i]);

	return;
}

bool SerialPort_IsByteAvailable()
{
	bool tmp = false;

	if ( UART1.RX.Indice_in != UART1.RX.Indice_out )
	{
		tmp = true;
	}

	return tmp;
}

uint8_t SerialPort_GetByte()
{
	return UART1_PopRx();
}

/***********************************************************************************************************************************
 *** IMPLEMNTACION DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static void UART1_PushTx(uint8_t dato)
{
	UART1.TX.Buffer[UART1.TX.Indice_in] = dato;

	UART1.TX.Indice_in ++;
	UART1.TX.Indice_in %= UART1_TAMANIO_COLA_TX;

	if ( UART1.TX.Datos_Validos == 0 )
	{
		UART1.TX.Datos_Validos = 1;

		USART_EnableInterrupts(USART1, kUSART_TxReadyInterruptEnable);
	}
}

static int32_t UART1_PopTx( void )
{
	int32_t dato = -1;

	if ( UART1.TX.Indice_in != UART1.TX.Indice_out )
	{
		dato = (int32_t) UART1.TX.Buffer[UART1.TX.Indice_out];
		UART1.TX.Indice_out ++;
		UART1.TX.Indice_out %= UART1_TAMANIO_COLA_TX;
	}
	return dato;
}

static void UART1_PushRx(uint8_t dato)
{
	UART1.RX.Buffer[UART1.RX.Indice_in] = dato;

	UART1.RX.Indice_in ++;
	UART1.RX.Indice_in %= UART1_TAMANIO_COLA_RX;
}

static int32_t UART1_PopRx( void )
{
	int32_t dato = -1;

	if ( UART1.RX.Indice_in != UART1.RX.Indice_out )
	{
		dato = (int32_t) UART1.RX.Buffer[UART1.RX.Indice_out];
		UART1.RX.Indice_out ++;
		UART1.RX.Indice_out %= UART1_TAMANIO_COLA_RX;
	}
	return dato;
}

/*--------------------------------------------------------------------------------------------------------------------------------*/


