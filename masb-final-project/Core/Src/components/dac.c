/*
 * dac.c
 *
 *  Created on: 23 may. 2020
 *      Author: user
 */

#include "components/dac.h"

extern I2C_HandleTypeDef hi2c1;

const float Reference_voltage = 4,
				Resolution = 4096;

uint8_t Data_dac[2];
uint16_t Vdac;
uint16_t Output_V;

void Write_DAC(double Vcell){

	Vdac = 1.65-(Vcell/2);

	// The DAC used has a 12-Bit IC resultion (0-4096) and the output voltage is given by:
	// Output voltage = (Reference voltage / resolution)*Digital value
	Output_V=(Reference_voltage/Resolution)*Vdac;

	// Vcell_dac is a uint8_t so we must send the double Vcell in two bytes
	Data_dac[0]= (Output_V>>8); // little endian, important digits at the back
	Data_dac[1]=Output_V; // sending the rest of the digits

	// Sending the data to the DAC with address 0xC0 (write)
	HAL_I2C_Master_Transmit(&hi2c1, 0xC0, Data_dac, 2, 10);

}
