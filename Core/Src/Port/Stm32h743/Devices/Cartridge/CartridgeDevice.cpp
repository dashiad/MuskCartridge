/*
 * CartridgeDevice.cpp
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#include <Port/Stm32h743/Devices/Cartridge/CartridgeDevice.h>

namespace Port::Stm32h743::Devices {


CartridgeDevice::CartridgeDevice(::Port::MCU *_mcu,Sys_FilesystemInterface *_fs,uint8_t *workBuffer,uint32_t buflen):
		Devices_Cartridge(_mcu,_fs,workBuffer,buflen)
		{

			DWT->CYCCNT = 0;

	     	// Enable CPU cycle counter
	     	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			__DSB();

			// Set PA8 as alternate mode 1 (TIM1_CH1)
			MODIFY_REG(GPIOA->AFR[1], GPIO_AFRH_AFSEL8, GPIO_AFRH_AFSEL8_0);
			MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE8, GPIO_MODER_MODE8_1);

			// No prescaler, timer runs at ABP2 timer clock speed (168 MHz)
			TIM1->PSC = 0;

			// CC1 and CC2 channel is input, IC1 and IC2 is mapped on TI1
			MODIFY_REG(TIM1->CCMR1,
	                TIM_CCMR1_CC1S|TIM_CCMR1_CC2S,
	                TIM_CCMR1_CC1S_0|TIM_CCMR1_CC2S_1);

			// TI1FP1 active on falling edge. TI1FP2 active on rising edge
			MODIFY_REG(TIM1->CCER,
	                TIM_CCER_CC1P|TIM_CCER_CC1NP|TIM_CCER_CC2P|TIM_CCER_CC2NP,
	                TIM_CCER_CC1P);
					//0);

			// Select TI1FP1 as trigger
			MODIFY_REG(TIM1->SMCR, TIM_SMCR_TS|TIM_SMCR_SMS, TIM_SMCR_TS_2|TIM_SMCR_TS_0);

			// Set reset mode
			TIM1->SMCR |= TIM_SMCR_SMS_2; // SLAVEMODE_RESET

			// Enable capture 1 and 2
			TIM1->CCER |= TIM_CCER_CC1E; //|TIM_CCER_CC2E;

			// Disable all TIM1 (and TIM8) interrupts
			TIM1->DIER = 0;
			// Enable counter
			TIM1->CR1 |= TIM_CR1_CEN;

		}

CartridgeDevice::~CartridgeDevice() {
	// TODO Auto-generated destructor stub
}


} /* namespace Port */
