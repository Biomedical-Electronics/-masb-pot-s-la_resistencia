/**
  ******************************************************************************
  * @file		cyclic_voltammetry.c
  * @brief		Gestión de la voltammetría cíclica.
  * @author		Albert Álvarez Carulla
  * @copyright	Copyright 2020 Albert Álvarez Carulla. All rights reserved.
  ******************************************************************************
  */

#include "components/cyclic_voltammetry.h"
#include "components/dac.h"
#include "components/adc.h"
#include "components/timers.h"
#include "components/masb_comm_s.h"

extern struct	CV_Configuration_S	cvConfiguration;
extern struct	Data_S				data;
extern TIM_HandleTypeDef	htim3;

double vObjetivo=0;
uint8_t	number=0;
uint8_t Measure_number=0;

void CV_start(void){ // iniciamos la voltametria ciclica

	Write_DAC(cvConfiguration.eBegin); // mandamos al DAC el valor de Vcell (eBegin del usuario)
	vObjetivo=cvConfiguration.eVertex1; // fijamos vObjetivo al eVertex 1 del usuario
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET); // cerramos el relé
	Sampling_Period_CV(); // iniciamos el timer
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim3) {
	// cuando haya pasado el periodo entre muestras
	cycles=cvConfiguration.cycles;

	Measure_number++; // cada vez que hacemos una medida incrementamos el indice

	// mandamos los datos que el host pide
	data.point=Measure_number; // el numero de medida
	data.timeMs=Measure_number*caConfiguration.samplingPeriodMs; // el tiempo transcurrido
	data.voltage=ADC_v(); // canviar struct ADC // el voltaje
	data.current=ADC_i(); // y la corriente

	MASB_COMM_S_sendData(data); // mandamos los valores

	while (number<cycles){

		Vcell=ADC_v(); // leemos la tension de la celda
		vObjetivo = cvConfiguration.eVertex1; // fijamos la tension objetivo

		if(Vcell!=vObjetivo){ // si la tension en la celda y la objetivo no son iguales
			Vcell=Vcell+cvConfiguration.eStep; // sumamos eStep
			} else { // si las tensiones son iguales
				vObjetivo=cvConfiguration.eVertex2; // cambiamos la tension objetivo
		}

		if(Vcell!=vObjetivo){ // si la tension en la celda y la objetivo no son iguales
			Vcell=Vcell-cvConfiguration.eStep; // restamos eStep
			} else { // si las tensiones son iguales
				vObjetivo=cvConfiguration.eBegin; // cambiamos la tension objetivo
		}

	number++;
	}
}
