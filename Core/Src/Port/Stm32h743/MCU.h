/*
 * DeviceDependent.h
 *
 *  Created on: 5 gen 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_STM32H743_MCU_H_
#define SRC_PORT_STM32H743_MCU_H_

#include "stm32h7xx_hal.h"
#define PIN_HIGH GPIO_PIN_SET
#define PIN_LOW  GPIO_PIN_RESET
#define SET_PIN(X,Y,Z) HAL_GPIO_WritePin(X, Y, GPIO_PIN_SET);

#define CRT_CTRL_GPIO GPIOD
#define CRT_PIN_IRQ 		GPIO_PIN_0
#define CRT_PIN_IRQ_MASK 	GPIO_PIN_0
#define CRT_PIN_RW  		GPIO_PIN_1
#define CRT_PIN_RW_MASK 	GPIO_PIN_1
#define CRT_PIN_IO1 		GPIO_PIN_3
#define CRT_PIN_IO1_MASK 	GPIO_PIN_3
#define CRT_PIN_GAME 		GPIO_PIN_4
#define CRT_PIN_GAME_MASK 	GPIO_PIN_4
#define CRT_PIN_EXROM 		GPIO_PIN_5
#define CRT_PIN_EXROM_MASK 	GPIO_PIN_5
#define CRT_PIN_IO2 		GPIO_PIN_6
#define CRT_PIN_IO2_MASK 	GPIO_PIN_6
#define CRT_PIN_ROML 		GPIO_PIN_7
#define CRT_PIN_ROML_MASK 	GPIO_PIN_7
#define CRT_PIN_BA 			GPIO_PIN_8
#define CRT_PIN_BA_MASK 	GPIO_PIN_8
#define CRT_PIN_DMA  		GPIO_PIN_9
#define CRT_PIN_DMA_MASK 	GPIO_PIN_9
#define CRT_PIN_ROMH 		GPIO_PIN_10
#define CRT_PIN_ROMH_MASK 	GPIO_PIN_10
#define CRT_PIN_RESET 		GPIO_PIN_13
#define CRT_PIN_NMI 		GPIO_PIN_14

#define CRT_5V_REGISTER		GPIOB
#define CRT_PIN_5V			GPIO_PIN_6
#define CRT_GETROMMASK		(CRT_PIN_ROMH_MASK | CRT_PIN_ROML_MASK)
#define CRT_WAITFORCRTPHY2HIGH  DWT->CYCCNT=TIM1->CNT*2;while(DWT->CYCCNT < 270 );
#define CRT_WAITFORCRTWRITEREADY while(DWT->CYCCNT<160);
//#define CRT_WAITFORCRTWRITEREADY while(DWT->CYCCNT<250);
#define CRT_WAITHOLDWRITE   while(DWT->CYCCNT<360);
//#define CRT_WAITHOLDWRITE   while(DWT->CYCCNT<450);

#define CRT_READCONTROL     GPIOD->IDR
#define CRT_READADDR		GPIOE->IDR
#define CRT_SETADDR(X)	    GPIOE->ODR=X
#define CRT_READDATA		(GPIOA->IDR & 0xff)

#define CRT_SETDATA(X) *((volatile uint8_t *)&GPIOA->ODR) = X
#define CRT_GET_DATA	(*((volatile uint8_t *)&GPIOA->IDR) & 0xFF)
#define CRT_HOLDDATA	while(DWT->CYCCNT<450);
#define CRT_SETDATAASINPUT	*((volatile uint16_t *)&GPIOA->MODER) = 0x0000
#define CRT_SETDATAASOUTPUT	*((volatile uint16_t *)&GPIOA->MODER) = 0x5555
#define CRT_WAITFORCLOCKEND	 while(DWT->CYCCNT<470);
#define CRT_WAITFORPHI2LOW   DWT->CYCCNT=TIM1->CNT*2;


#define CRT_SETGAMEHI		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_GAME, GPIO_PIN_SET)
#define CRT_SETGAMELO		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_GAME, GPIO_PIN_RESET)

#define CRT_SETEXROMHI		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_EXROM, GPIO_PIN_SET)
#define CRT_SETEXROMLO		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_EXROM, GPIO_PIN_RESET)

#define CRT_SETIRQHI		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_IRQ, GPIO_PIN_SET);
#define CRT_SETNMIHI		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_NMI, GPIO_PIN_SET);

#define CRT_SETIRQLO		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_IRQ, GPIO_PIN_RESET);
#define CRT_SETDMALO		GPIOD->BSRR|=GPIO_BSRR_BR9;
#define CRT_SETDMAHI		GPIOD->BSRR|=GPIO_BSRR_BS9;
#define CRT_SETNMILO		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_NMI, GPIO_PIN_RESET);
#define CRT_SETRWLO		    GPIOD->BSRR|=GPIO_BSRR_BR1;
#define CRT_SETRWHI		    GPIOD->BSRR|=GPIO_BSRR_BS1;


#define CRT_SETRWASINPUT    GPIOD->MODER &=~(GPIO_MODER_MODE1);
#define CRT_SETRWASOUTPUT   GPIOD->MODER |=(GPIO_MODER_MODE1_0);

#define CRT_SETADDRASINPUT  *((volatile uint32_t *)&GPIOE->MODER)=0x00000000;
#define CRT_SETADDRASOUTPUT *((volatile uint32_t *)&GPIOE->MODER)=0x55555555;


#define CRT_SETIRQASINPUT	GPIOD->MODER &=~(GPIO_MODER_MODE0);
#define CRT_SETIRQASOUTPUT	GPIOD->MODER |=(GPIO_MODER_MODE0_0);

#define CRT_SETDMAASINPUT	GPIOD->MODER &=~(GPIO_MODER_MODE9);
#define CRT_SETDMAASOUTPUT	GPIOD->MODER |=(GPIO_MODER_MODE9_0);

#define CRT_SETRESETASINPUT	GPIOD->MODER &=~(GPIO_MODER_MODE13);
#define CRT_SETRESETASOUTPUT	GPIOD->MODER |=(GPIO_MODER_MODE13_0);

#define CRT_SETNMIASINPUT	GPIOD->MODER &=~(GPIO_MODER_MODE14);
#define CRT_SETNMIASOUTPUT	GPIOD->MODER |=(GPIO_MODER_MODE14_0);

#define CRT_SETRESETHI		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_RESET, GPIO_PIN_SET);
#define CRT_SETRESETLO		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_RESET, GPIO_PIN_RESET);



#define CRT_SETNMIHI		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_NMI, GPIO_PIN_SET);
#define CRT_SET_AS_8K       HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_EXROM, GPIO_PIN_RESET);HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_GAME, GPIO_PIN_SET);
#define CRT_SET_AS_16K      HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_EXROM, GPIO_PIN_RESET);HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_GAME, GPIO_PIN_RESET);
#define CRT_SET_AS_ULTIMAX  HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_EXROM, GPIO_PIN_SET);HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_GAME, GPIO_PIN_RESET);
#define CRT_DISCONNECT		HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_EXROM, GPIO_PIN_SET);HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_GAME, GPIO_PIN_SET);

#define CRT_GET_RW(X)		(X & CRT_PIN_RW_MASK)
#define CRT_GET_IO1(X) 		(X & CRT_PIN_IO1_MASK)
#define CRT_GET_IO2(X)		(X & CRT_PIN_IO2_MASK)
#define CRT_GET_ROML(X)		(X & CRT_PIN_ROML_MASK)
#define CRT_GET_ROMH(X)		(X & CRT_PIN_ROMH_MASK)
#define CRT_GET_BA(X)		(X & CRT_PIN_BA_MASK)



#define DEBUG1_ON			GPIOB->BSRR|=GPIO_BSRR_BS9;
#define DEBUG1_OFF			GPIOB->BSRR|=GPIO_BSRR_BR9;
#define CRT_HASPOWER 		HAL_GPIO_ReadPin(CRT_5V_REGISTER,CRT_PIN_5V)==GPIO_PIN_SET
#define RESET_C64			HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_RESET, GPIO_PIN_RESET);HAL_Delay(1);HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_RESET, GPIO_PIN_SET);

#include <Port/MCU.h>
namespace Port::Stm32h743 {

class MCU : public ::Port::MCU{
public:
	MCU();
	inline virtual void waitForCrtPhy2High()     {DWT->CYCCNT=TIM1->CNT*1.5;while(DWT->CYCCNT < 245 );};
	inline virtual uint16_t crtReadControl()     {return GPIOD->IDR;}
	inline virtual uint16_t crtReadAddr()		 {return GPIOE->IDR;}
	inline virtual uint16_t crtGetRomMask()		 {return CRT_PIN_ROML_MASK | CRT_PIN_ROMH_MASK;}
	inline virtual void crtSetDataAsOutput()	 {*((volatile uint16_t *)&GPIOA->MODER) = 0x5555;}
	inline virtual void crtSetData(uint8_t data) {*((volatile uint8_t *)&GPIOA->ODR) = data;}
	inline virtual void crtHoldData()			 {while(DWT->CYCCNT<400);}
	inline virtual void crtSetDataAsInput()		 {*((volatile uint16_t *)&GPIOA->MODER) = 0x0000;};
	inline virtual void crtWaitForClockEnd()	 {while(DWT->CYCCNT<450);}

	inline virtual void crtSetGameHi()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_GAME, GPIO_PIN_SET);}
	inline virtual void crtSetGameLo()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_GAME, GPIO_PIN_RESET);}

	inline virtual void crtSetExromHi()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_EXROM, GPIO_PIN_SET);}
	inline virtual void crtSetExromLo()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_EXROM, GPIO_PIN_RESET);}

	inline virtual void crtSetIrqHi()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_IRQ, GPIO_PIN_SET);}
	inline virtual void crtSetIrqAsInput()		 {GPIOD->MODER &=~(GPIO_MODER_MODE0);}
	inline virtual void crtSetIrqAsOutput()		 {GPIOD->MODER |=~(GPIO_MODER_MODE0_0);}

	inline virtual void crtSetResetHi()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_RESET, GPIO_PIN_SET);}
	inline virtual void crtSetResetLo()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_RESET, GPIO_PIN_RESET);}

	inline virtual void crtSetDMAHi()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_DMA, GPIO_PIN_SET);}

	inline virtual void crtSetNMIHi()			 {HAL_GPIO_WritePin(CRT_CTRL_GPIO, CRT_PIN_NMI, GPIO_PIN_SET);}

	inline virtual void debug1On()				 {GPIOB->BSRR|=GPIO_BSRR_BS9;}
	inline virtual void debug1Off()				 {GPIOB->BSRR|=GPIO_BSRR_BR9;}




	inline virtual bool crtHasPower(){return HAL_GPIO_ReadPin(CRT_5V_REGISTER,CRT_PIN_5V)==GPIO_PIN_SET;}
	inline virtual void resetC64(){crtSetResetLo();HAL_Delay(1);crtSetResetHi();}

	inline virtual const char *getModuleName() {return "Stm32h743_MCU";}
	virtual ~MCU();
	//#define SET_CONTROL_PIN(X,Y) SET_PIN(CTRL_GPIO,X,Y)
	//#define SET_IRQ_AS_INPUT CTRL_GPIO->MODER &=~(GPIO_MODER_MODE0);
};

} /* namespace Stm32h743 */


#endif /* SRC_PORT_STM32H743_MCU_H_ */
