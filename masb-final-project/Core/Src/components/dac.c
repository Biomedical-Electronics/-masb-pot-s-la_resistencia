/*
 * dac.c
 *
 *  Created on: 23 may. 2020
 *      Author: user
 */

#include "components/dac.h"

extern I2C_HandleTypeDef hi2c1;
uint32_t Vcell;

uint8_t Vdac[2];

void DAC_VALUES(Vcell){

	Vdac[0]=0x00; // registre on escrivim
	Vdac[1]=1.65-(Vcell/2);

	// enviar Vdac al dac
	HAL_I2C_Master_Transmit(&hi2c1, 0xC1, Vdac, 2, 10);

}
