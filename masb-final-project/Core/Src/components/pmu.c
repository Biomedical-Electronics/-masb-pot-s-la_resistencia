/*
 * pmu.c
 *
 *  Created on: 6 jun. 2020
 *      Author: Vidalbana
 */

void PMU_enable(void){
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET); // habilitamos PMU
}

