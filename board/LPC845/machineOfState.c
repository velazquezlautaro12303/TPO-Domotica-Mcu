/*******************************************************************************************************************************//**
 *
 * @file		machineOfState.c
 * @proyect		TPO_Lpc_845_Project
 * @date		18:36:31
 * @author		Velazquez Lautaro
 * @subject		INFO II
 * @course		R2051
 *
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "uart.h"
#include "Rele.h"
#include "machineOfState.h"
#include "Dimmer.h"
#include "adc.h"
#include <stdlib.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

#define IDLE 								0
#define RECIBI_A 							1
#define RECIBI_1 							2
#define RECIBI_0 							3
#define RECIBI_L							4
#define RECIBI_PORCENTAJE_DE_LUZ			5
#define RECIBI_R							6
#define RECIBI_ON_RELE						7
#define RECIBI_OFF_RELE						8
#define RECIBI_ACTIVAR_AUTOMATIZACION		9
#define RECIBI_DESACTIVAR_AUTOMATIZACION	10
#define FIX									11

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



/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static int conversionPorcentaje(int x);

/***********************************************************************************************************************************
*** CONFIGURACION DE ERRORES
**********************************************************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE FUNCIONES PUBLICAS
 **********************************************************************************************************************************/

void MdE()
{
	static uint32_t estado = IDLE;
	static uint8_t porcentaje_de_luz;
	uint8_t data;
	static uint8_t num1 = 0;
	static uint8_t num2 = 0;

	if(SerialPort_IsByteAvailable())
	{
		data = SerialPort_GetByte();
		switch(estado)
		{
			case IDLE:
				if(data == 'A')
				{
					estado = RECIBI_A;
				}
				else if(data == 'L')
				{
					estado = RECIBI_L;
				}
				else if(data == 'R')
				{
					estado = RECIBI_R;
				}
				break;

			case RECIBI_A:
				if(data == '1')
				{
					estado = RECIBI_1;
				}
				else if(data == '0')
				{
					estado = RECIBI_0;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_1:
				if(data == 'A'+'1')
				{
					EncenderAlarma();
					estado = IDLE;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_0:
				if(data == 'A'+'0')
				{
					ApagarAlarma();
					estado = IDLE;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_L:
				if(data <= '9' && data >= '0')
				{
					num1 = data;
					estado = FIX;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case FIX:
				if(data <= '9' && data >= '0')
				{
					num2 = data;
					char cadena[2] = {num1,num2};
					porcentaje_de_luz = atoi(cadena);
					timer =  conversionPorcentaje(porcentaje_de_luz);
					//estado = RECIBI_PORCENTAJE_DE_LUZ;
					estado = IDLE;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_PORCENTAJE_DE_LUZ:
				if(data == 'L' + num1 + num2)
				{
					timer =  conversionPorcentaje(porcentaje_de_luz);
					estado = IDLE;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_R:
				//if(data == '1')
				if(data == '1' && flag_automatizacion_persiana == false)
				{
					SubirPersiana();
					estado = IDLE;
					//estado = RECIBI_ON_RELE;
				}
				//else if(data == '0')
				if(data == '0' && flag_automatizacion_persiana == false)
				{
					BajarPersiana();
					estado = IDLE;
					//estado = RECIBI_OFF_RELE;
				}
				else if(data == 'U')
				{
					flag_automatizacion_persiana = true;
					estado = IDLE;
					//estado = RECIBI_ACTIVAR_AUTOMATIZACION;
				}
				else if(data == 'D')
				{
					flag_automatizacion_persiana = false;
					estado = IDLE;
					//estado = RECIBI_DESACTIVAR_AUTOMATIZACION;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_ON_RELE:
				if(data == '1' + 'R' && flag_automatizacion_persiana == false)
				{
					SubirPersiana();
					estado = IDLE;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_OFF_RELE:
				if(data == '0' + 'R' && flag_automatizacion_persiana == false)
				{
					BajarPersiana();
					estado = IDLE;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_ACTIVAR_AUTOMATIZACION:
				if(data == 'R' + 'U')
				{
					flag_automatizacion_persiana = true;
					estado = IDLE;
				}
				else
				{
					estado = IDLE;
				}
				break;

			case RECIBI_DESACTIVAR_AUTOMATIZACION:
				if(data == 'R' + 'D')
				{
					flag_automatizacion_persiana = false;
					estado = IDLE;
				}
				else
				{
					estado = IDLE;
				}
				break;
			default: break;
		}
	}
}

/***********************************************************************************************************************************
 *** IMPLEMNTACION DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static int conversionPorcentaje(int x)
{
	x = 100 - x;
	return ((x*42/100) + 50);
}

/*--------------------------------------------------------------------------------------------------------------------------------*/
