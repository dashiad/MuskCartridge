/*
 * SerialInterface.h
 *
 *  Created on: 2 nov 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_STM32H743_SYS_SERIALINTERFACE_H_
#define SRC_PORT_STM32H743_SYS_SERIALINTERFACE_H_
#define DEFAULT_SERIAL_SPEED 115200

#include "stm32h7xx_hal_def.h"
#include "stm32h7xx_hal_uart.h"
#include "Sys/Result.h"
#include "Port/Base/CommsInterface.h"
#include "Port/Base/MessageManager.h"

namespace Port {
	namespace Stm32h743 {
		namespace Sys {



		class SerialInterface : public ::Port::Base::CommsInterface {
		public:
			static const char *RES_SERIAL_ERROR;
			static const char *RES_SERIAL_TIMEOUT;
			SerialInterface(UART_HandleTypeDef *_huart1);
			virtual void init(::Port::Base::MessageManager *_manager,::Sys::Result *res);
			void setReceiveInterrupt();
			void sendBytes(uint8_t *buf, uint32_t len,uint32_t timeoutMillis);
			int receiveBytes(uint8_t *buf, uint32_t len,uint32_t timeoutMillis);
			inline void Error_Handler(){}
			void changeBaudRate(int baudrate);
			::Port::Base::MessageManager *manager;
			unsigned char codeBuf[4];
		protected:
			UART_HandleTypeDef *huart1;


};

}
}
}


#endif /* SRC_PORT_STM32H743_SYS_SERIALINTERFACE_H_ */
