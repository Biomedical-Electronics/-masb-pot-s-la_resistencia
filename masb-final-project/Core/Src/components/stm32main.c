/*
 * stm32main.c
 *
 *  Created on: May 19, 2020
 *      Author: berta
 */

#include "components/stm32main.h"
#include "components/pmu.h"
#include "components/masb_comm_s.h"
#include "components/chronoamperometry.h"
#include "components/cyclic_voltammetry.h"
#include "main.h"

struct CA_Configuration_S caCOnfiguration;
struct CV_Configuration_S cvCOnfiguration;

void setup(void) {

	MASB_COMM_S_waitForMessage(); // esperamos un mensaje
	PMU_enable(); // encendemos el pmu

}

void loop(void){

	if (MASB_COMM_S_dataReceived()) { // si recibimos un mensaje

		switch (MASB_COMM_S_command()){ // creamos una estructura para configurar el tipo de comando

			case START_CV_MEAS: // si el host quiere hav¡cer una cv
				// configuramos la cv con sus parametros
				CV_start(MASB_COMM_S_getCvConfiguration()); // ejecutamos la cv
				break;

			case START_CA_MEAS: // si el host quiere hav¡cer una ca
				// configuramos la ca con sus parametros
				CA_start(MASB_COMM_S_getCaConfiguration()); // ejecutamos la ca
				break;

			case STOP_MEAS: // si se quiere parar
				break; // paramos

			default:
				break;

		}

	}


}
