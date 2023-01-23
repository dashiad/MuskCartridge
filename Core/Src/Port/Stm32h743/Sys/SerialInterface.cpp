#include "stm32h7xx_hal.h"
#include "SerialInterface.h"
#include "Port/Base/Messages.h"
#include "Sys/Result.h"
#include <string.h>
#include <stdio.h>

#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

::Port::Stm32h743::Sys::SerialInterface *current;
volatile int nn=0;
//void USART3_IRQHandler(void)

volatile int uart_rx_status=0;
volatile char *curEncoding=0;
volatile uint8_t *bufPointer;
volatile int curEncodingLength;
volatile int subStatus;
int nextInc=0;
int __tmpLen;
int __accLen;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	char nBuf[100];
	int *code= (int *)(&(current->manager->curMessage));
	//current->manager->setMessageCode(*code);
	//return;

	if(uart_rx_status==0)
	{
		unsigned char *buf= (unsigned char *)(&(current->manager->curMessage));
		uart_rx_status=0;
		int code=*((int *)buf);
		curEncoding=::Port::Base::messageEncoding[code];
		curEncodingLength=strlen((const char *)curEncoding);
		bufPointer=(uint8_t *)buf+4;
		subStatus=0;
		//ILI9341_FillScreen(WHITE);


	}
	else
	{
		bufPointer+=nextInc;
	}
	if(subStatus==0)
		uart_rx_status++;


	if(uart_rx_status >= curEncodingLength)
	{
		unsigned char *buf= (unsigned char *)(&(current->manager->curMessage));
		current->manager->onMessage();
		uart_rx_status=0;
		subStatus=0;
		nextInc=0;
		HAL_UART_Receive_IT(huart,buf,4);

	}
	else
	{
		/*sprintf(nBuf,"Next:%c [%d] [%d] [%d]",curEncoding[uart_rx_status],uart_rx_status,
				(int)(bufPointer-(unsigned char *)(&(current->manager->curMessage)))
				,__tmpLen);
		ILI9341_DrawText(nBuf, FONT4, 0, uart_rx_status*20, BLACK, WHITE);*/

		switch(curEncoding[uart_rx_status])
		{
			case 'i':
			{
				HAL_UART_Receive_IT(huart,(uint8_t *)bufPointer,4);
				nextInc=sizeof(int);
			}break;
			case 'b':{
				HAL_UART_Receive_IT(huart,(uint8_t *)bufPointer,1);
				nextInc=sizeof(char);
			}break;
			case 'x':{
				if(subStatus==0)
				{
					HAL_UART_Receive_IT(huart,((uint8_t *)(bufPointer)),4);
					nextInc=4;
					subStatus=1;
				}
				else
				{
					if(subStatus==1){
						__tmpLen=*(int *)((uint8_t *)(bufPointer)-4);
						nextInc=__tmpLen;
						__accLen=__tmpLen;
						if(__accLen>8000)
						{
							HAL_UART_Receive_IT(huart,(uint8_t *)bufPointer,255);
							__accLen=255;
							subStatus=2;
						}
						else
						{
							HAL_UART_Receive_IT(huart,(uint8_t *)bufPointer,__accLen);
							subStatus=0;
						}
					}
					else
					{
						// subStatus==2
						if(__tmpLen-__accLen<255)
						{
							nextInc=__tmpLen-__accLen;
							HAL_UART_Receive_IT(huart,(uint8_t *)bufPointer,nextInc);
							subStatus=0;
						}
						else
						{
							__accLen+=255;
							nextInc=255;
							HAL_UART_Receive_IT(huart,(uint8_t *)bufPointer,255);
						}

					}

				}
			}break;

			case 's':{
				if(subStatus==0)
				{
					HAL_UART_Receive_IT(huart,(uint8_t *)&__tmpLen,4);
					nextInc=0;
					// No adelanto aun el puntero.
					subStatus=1;
				}
				else
				{
					((uint8_t *)(bufPointer))[__tmpLen]=0;
					nextInc=__tmpLen;
					HAL_UART_Receive_IT(huart,(uint8_t *)bufPointer,__tmpLen);
					subStatus=0;

				}
			}break;
		}
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_ErrorCallback can be implemented in the user file.
   */
}

namespace Port {
	namespace Stm32h743 {
		namespace Sys {
const char *SerialInterface::RES_SERIAL_ERROR    ="Serial error";
const char *SerialInterface::RES_SERIAL_TIMEOUT   ="Serial timeout";


SerialInterface::SerialInterface(UART_HandleTypeDef *_huart1):CommsInterface("SerialInterface")
{
	huart1=_huart1;
	current=this;
}

void SerialInterface::init(::Port::Base::MessageManager *_manager,::Sys::Result *res)
{
	manager=_manager;
	  huart1->Instance = USART3;
	  huart1->Init.BaudRate = DEFAULT_SERIAL_SPEED;
	  huart1->Init.WordLength = UART_WORDLENGTH_8B;
	  huart1->Init.StopBits = UART_STOPBITS_1;
	  huart1->Init.Parity = UART_PARITY_NONE;
	  huart1->Init.Mode = UART_MODE_TX_RX;
	  huart1->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart1->Init.OverSampling = UART_OVERSAMPLING_16;
	  huart1->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	  huart1->Init.ClockPrescaler = UART_PRESCALER_DIV1;
	  huart1->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	  if (HAL_UART_Init(huart1) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_UARTEx_SetTxFifoThreshold(huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_UARTEx_SetRxFifoThreshold(huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_UARTEx_DisableFifoMode(huart1) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /* USER CODE BEGIN USART3_Init 2 */

	  /* USER CODE END USART3_Init 2 */



}
void SerialInterface::changeBaudRate(int baudrate)
{
	  huart1->Init.BaudRate = baudrate;
	  if (HAL_UART_Init(huart1) != HAL_OK)
	  {
		  int h;
		  h=11;
	  }

}
void SerialInterface::setReceiveInterrupt()
{
	//HAL_UART_Receive_IT (huart1, (unsigned char *)&(current->manager->curMessage), 4);
	HAL_UART_Receive_IT (huart1, (unsigned char *)&(current->manager->curMessage), 4);
}
void SerialInterface::sendBytes(uint8_t *buf, uint32_t len,uint32_t timeoutMillis)
{

	HAL_UART_Transmit(huart1,buf,len,HAL_MAX_DELAY);
}
int SerialInterface::receiveBytes(uint8_t *buf, uint32_t len,uint32_t timeoutMillis)
{

		HAL_StatusTypeDef result;

			result=HAL_UART_Receive(huart1,buf,len,HAL_MAX_DELAY);
		return 0;
}

}
	}
}
