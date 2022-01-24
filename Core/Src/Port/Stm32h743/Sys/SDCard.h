/*
 * SDCard.h
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_STM32H743_SYS_SDCARD_H_
#define SRC_PORT_STM32H743_SYS_SDCARD_H_
#include "Port/Base/FatFsFilesystem.h"
using Port_Base_FatFsFilesystem = Port::Base::FatFsFilesystem;
namespace Port::Stm32h743::Sys
{
	class SDCard : public Port_Base_FatFsFilesystem{
	};
}

#endif /* SRC_PORT_STM32H743_SYS_SDCARD_H_ */
