/*
 * timers.c
 *
 *  Created on: 29 may. 2020
 *      Author: Vidalbana
 */

#include "components/timers.h"
#include "components/masb_comm_s.h"

extern TIM_HandleTypeDef	htim2;

extern struct CA_Configuration_S	caConfiguration;
extern struct CV_Configuration_S	cvConfiguration;

void Sampling_Period(periodo){
	// Usamos el timer 2 para calcular el tiempo entre muestras de la cronoamperometria
	HAL_TIM_Base_DeInit(&htim2); // desinicializar el timer

	  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	  TIM_MasterConfigTypeDef sMasterConfig = {0};

	  htim2.Instance = TIM2;
	  htim2.Init.Prescaler = 8399;
	  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim2.Init.Period = periodo;	// cambiamos el periodo al de la cronoamperometria
	  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }

	HAL_TIM_Base_Init(&htim2); // inicializar el timer
	HAL_TIM_Base_Start_IT(&htim2); // volvemos a iniciar el funcionamiento del timer

}



