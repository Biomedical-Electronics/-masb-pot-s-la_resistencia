/*
 * adc.c
 *
 *  Created on: May 21, 2020
 *      Author: Vidalbana
 */

#include "components/adc.h"

extern	ADC_HandleTypeDef	hadc1;

uint32_t	Vref=0;
uint32_t	Vadc=0;

const float Rtia=10;
float	Icell=0,
		Vcell=0;

void ADC_values(void){
	HAL_ADC_Start(&hadc1); // iniciamos la conversion
	HAL_ADC_PollForConversion(&hadc1, 200); // esperamos que finalize la conversion

	Vref = HAL_ADC_GetValue(&hadc1); // leemos el resultado de la conversion y lo guardamos en VRef

	Vcell=(1.65-Vref)*2;

	HAL_ADC_Start(&hadc1); // iniciamos la conversion
	HAL_ADC_PollForConversion(&hadc1, 200); // esperamos que finalize la conversion

	Vadc = HAL_ADC_GetValue(&hadc1); // leemos el resultado de la conversion y lo guardamos en Vadc

	Icell= ((Vadc-1.65)*2)/Rtia;
}
