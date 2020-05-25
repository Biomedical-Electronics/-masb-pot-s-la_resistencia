/**
  ******************************************************************************
  * @file		chronoamperometry.c
  * @brief		Gestión de la cronoamperometría.
  * @author		Albert Álvarez Carulla
  * @copyright	Copyright 2020 Albert Álvarez Carulla. All rights reserved.
  ******************************************************************************
  */

#include "components/chronoamperometry.h"
#include "components/dac.h"
#include "components/timer.h"
#include "components/adc.h"

extern struct CA_Configuration_S caConfiguration;
extern struct Data_S data;

void CA_start(void){ // iniciamos la cronoamperometria

	Write_DAC(caConfiguration.eDC); // mandamos al DAC el valor de Vcell (eDC del usuario)

	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET); /// cerramos el relé

	SamplingPeriod(); // iniciamos el timer

	Measure_number=0; // creamos un indice para poder calcular el numero de medidas que vamos haciendo
						// lo usaremos de referencia para saber el tiempo transcurrido
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim2) { // callback del timer, hacemos las medidas

	Measures=ca.Configuration.measurementTime/(caConfiguration.samplingPeriodMs*10e(-3)); // calculamos el total de medidas que corresponden al sampling period

	Measure_number++; // cada vez que hacemos una medida incrementamos el indice

	// struct del ADC
	// mandamos los datos que el host pide
	data.point=Measure_number; // el numero de medida
	data.timeMs=Measure_number*caConfiguration.samplingPeriodMs; // el tiempo transcurrido
	data.voltage=ADC_values.Vcell; // canviar struct ADC // el voltaje
	data.current=ADC_values.Icell; // y la corriente

	MASB_COMM_S_sendData(data); // mandamos los valores

	if (Measure_number==Measures){ // si hemos terminado el ciclo (el numero de medidas es el correspondiente al sampling period
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET); // encendemos el relé
		HAL_TIM_Base_Stop_IT(&htim2); // paramos el timer
	}

}
