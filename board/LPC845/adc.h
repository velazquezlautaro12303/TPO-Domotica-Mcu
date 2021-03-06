/*******************************************************************************************************************************//**
 *
 * @file		ADC.h		
 * @date		26 sep. 2021
 * @author		Velazquez Lautaro
 * @subject		INFO II
 * @course		R2051
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef LPC845_SENSORDETEMPERATURA_H_
#define LPC845_SENSORDETEMPERATURA_H_

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "fsl_adc.h"

/***********************************************************************************************************************************
 *** DEFINES (publicos)
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** MACROS
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** TIPO DE DATOS PUBLICOS
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES (extern)
 **********************************************************************************************************************************/

extern bool flag_automatizacion_persiana;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES
 **********************************************************************************************************************************/

void adc_Init(void);
void SensorDeTemperatura_Read(void);
void SensorDeIluminacion_Read();

/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

#endif /* LPC845_SENSORDETEMPERATURA_H_ */
