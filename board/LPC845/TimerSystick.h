/*******************************************************************************************************************************//**
 *
 * @file		TimerSystick.h		
 * @date		28 nov. 2021
 * @author		Velazquez Lautaro
 * @subject		INFO II
 * @course		R2051
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef LPC845_TIMERSYSTICK_H_
#define LPC845_TIMERSYSTICK_H_

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include <stdbool.h>
#include <stdint.h>

/***********************************************************************************************************************************
 *** DEFINES (publicos)
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** MACROS
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** TIPO DE DATOS PUBLICOS
 **********************************************************************************************************************************/

typedef uint32_t tiempo;

typedef enum
{
	PERIODIC,
	SINGLE_SHOT
}timer_types;

typedef enum
{
	TIMER_1 = 0,
	TIMER_2,
	TIMER_3,
	TIMER_4,
	TIMER_5,
	TIMER_MAX
}timer_id;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES (extern)
 **********************************************************************************************************************************/



/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES
 **********************************************************************************************************************************/

/********************************************************************************************************
 * @brief	Inicializacion del Modulo Systick Timer.
 *
 * @param[in] 	ninguno
 * @return		nada
********************************************************************************************************/

void 	TIMER_Systick_Init(void);

/********************************************************************************************************
 * @brief	Cuenta la cantidad de tiempo espeficada en valor (normalmente miliSegundos) y provee
 * 			la información de que se termino de contar a través de un flag que puede se encuestado
 * 			en cualquier momento por la funcion TIMER_Get_Event o llama dentro de la misma
 * 			interrupcion al puntero a funcion que se pasa como argumento (en el caso de que sea
 * 			NULL se sigue teniendo el flag).
 *
 * @param[in]	timer_id id 			identificador del timer.
 * @param[in]	tiempo valor 			normalmente espeficado en mSec depende de .
 * @param[in]	timer_types tipo 		Periodic se autorecarga con el valor especificado
 * 										Single_Shot solo genera una vez el flag, el valor debe
 * 										ser recargado manualmente para voler a utilizar el timer.
 * @param[in]	void (*handler)(void) 	puntero a la funcion a ser llamada cuando se vence el timer.
 * 										IMPORTANTE!: esta funcion debe ser breve ya que forma parte
 * 										de la rutina de interrupcion del Systick.
 *
 * @return		true					Se pudo arrancar el timer.
 * 				false					Parametros fuera de rango, o el timer ya estaba en funcionamiento.
********************************************************************************************************/
void 	TIMER_Start(timer_id id, tiempo valor, timer_types tipo ,void (*handler)(void));

/********************************************************************************************************
 * @brief	Para el timer, borra la cuenta, el puntero y el flag.
 *
 * @param[in]	time_id id	identificador del timer.
 *
 * @return		true		si el resultado fue satisfactorio.
 * 				false		si ocurrio un problema.
********************************************************************************************************/
void 	TIMER_Stop(timer_id id);

/********************************************************************************************************
 * @brief	Funcion para encuestar y saber si se vencio el timer. Equivalente a preguntar por un
 * 			flag.
 * 			IMPORTANTE!: en caso de que el timer expiro, el flag es borrado.
 *
 * @param[in] timer_id	id 	identificador del timer que se desea encuestar.
 *
 * @return		true		si el timer expiro
 * 				false		si el timer no expiro desde la ultima encuestra.
********************************************************************************************************/
bool 	TIMER_Get_Event(timer_id id);

/********************************************************************************************************
 * @fn		TIMER_ProcessEvent
 * @brief	Es la funcion central y es privada al modulo, se encarga de ir descontando los timers
 * 			incializados, llamados a los punteros a funcion provistos y marcando los flags de los timers
 * 			ya vencidos. Es llamada en la interrupcion del modulo de Systick.
 * 			En el caso de que el timer tenga autorecarga, vuelve a cargar automaticamente el timer
 * 			con el valor original provisto en la funcion Start o sacado desde el archivo de configuracion.
 *
 * @param[in]	void
 * @return		void
********************************************************************************************************/
void TIMER_ProcessEvent(void);


/***********************************************************************************************************************************
 *** FIN DEL MODULO
 **********************************************************************************************************************************/

#endif /* LPC845_TIMERSYSTICK_H_ */
