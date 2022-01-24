/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Address2_Pin GPIO_PIN_2
#define Address2_GPIO_Port GPIOE
#define Address3_Pin GPIO_PIN_3
#define Address3_GPIO_Port GPIOE
#define Address4_Pin GPIO_PIN_4
#define Address4_GPIO_Port GPIOE
#define Address5_Pin GPIO_PIN_5
#define Address5_GPIO_Port GPIOE
#define Address6_Pin GPIO_PIN_6
#define Address6_GPIO_Port GPIOE
#define button1_Pin GPIO_PIN_0
#define button1_GPIO_Port GPIOC
#define button2_Pin GPIO_PIN_1
#define button2_GPIO_Port GPIOC
#define Data_0_Pin GPIO_PIN_0
#define Data_0_GPIO_Port GPIOA
#define Data1_Pin GPIO_PIN_1
#define Data1_GPIO_Port GPIOA
#define Data2_Pin GPIO_PIN_2
#define Data2_GPIO_Port GPIOA
#define Data3_Pin GPIO_PIN_3
#define Data3_GPIO_Port GPIOA
#define Data4_Pin GPIO_PIN_4
#define Data4_GPIO_Port GPIOA
#define Data5_Pin GPIO_PIN_5
#define Data5_GPIO_Port GPIOA
#define Data6_Pin GPIO_PIN_6
#define Data6_GPIO_Port GPIOA
#define Data7_Pin GPIO_PIN_7
#define Data7_GPIO_Port GPIOA
#define SPI_CS_Pin GPIO_PIN_4
#define SPI_CS_GPIO_Port GPIOC
#define button3_Pin GPIO_PIN_5
#define button3_GPIO_Port GPIOC
#define TFT_DC_Pin GPIO_PIN_1
#define TFT_DC_GPIO_Port GPIOB
#define Address7_Pin GPIO_PIN_7
#define Address7_GPIO_Port GPIOE
#define Address8_Pin GPIO_PIN_8
#define Address8_GPIO_Port GPIOE
#define Address9_Pin GPIO_PIN_9
#define Address9_GPIO_Port GPIOE
#define Address10_Pin GPIO_PIN_10
#define Address10_GPIO_Port GPIOE
#define Address11_Pin GPIO_PIN_11
#define Address11_GPIO_Port GPIOE
#define Address12_Pin GPIO_PIN_12
#define Address12_GPIO_Port GPIOE
#define Address13_Pin GPIO_PIN_13
#define Address13_GPIO_Port GPIOE
#define Address14_Pin GPIO_PIN_14
#define Address14_GPIO_Port GPIOE
#define Address15_Pin GPIO_PIN_15
#define Address15_GPIO_Port GPIOE
#define CS_del_TFT_Pin GPIO_PIN_12
#define CS_del_TFT_GPIO_Port GPIOB
#define BA_Pin GPIO_PIN_8
#define BA_GPIO_Port GPIOD
#define DMA_Pin GPIO_PIN_9
#define DMA_GPIO_Port GPIOD
#define ROMH_Pin GPIO_PIN_10
#define ROMH_GPIO_Port GPIOD
#define RESET_Pin GPIO_PIN_13
#define RESET_GPIO_Port GPIOD
#define NMI_Pin GPIO_PIN_14
#define NMI_GPIO_Port GPIOD
#define PHI2_COPIA_Pin GPIO_PIN_15
#define PHI2_COPIA_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_7
#define LED0_GPIO_Port GPIOC
#define IRQ_Pin GPIO_PIN_0
#define IRQ_GPIO_Port GPIOD
#define R_W_Pin GPIO_PIN_1
#define R_W_GPIO_Port GPIOD
#define IO1_Pin GPIO_PIN_3
#define IO1_GPIO_Port GPIOD
#define EMAG_Pin GPIO_PIN_4
#define EMAG_GPIO_Port GPIOD
#define EXROM_Pin GPIO_PIN_5
#define EXROM_GPIO_Port GPIOD
#define IO_2_Pin GPIO_PIN_6
#define IO_2_GPIO_Port GPIOD
#define ROML_Pin GPIO_PIN_7
#define ROML_GPIO_Port GPIOD
#define power_Pin GPIO_PIN_6
#define power_GPIO_Port GPIOB
#define debug_Pin GPIO_PIN_9
#define debug_GPIO_Port GPIOB
#define Address0_Pin GPIO_PIN_0
#define Address0_GPIO_Port GPIOE
#define Address_1_Pin GPIO_PIN_1
#define Address_1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
