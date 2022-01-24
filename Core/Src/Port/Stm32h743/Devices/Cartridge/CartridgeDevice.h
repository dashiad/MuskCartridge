/*
 * CartridgeDevice.h
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_STM32H743_DEVICES_CARTRIDGE_CARTRIDGEDEVICE_H_
#define SRC_PORT_STM32H743_DEVICES_CARTRIDGE_CARTRIDGEDEVICE_H_
#include <Port/Stm32h743/MCU.h>
#include "Devices/Cartridge/CartridgeDevice.h"

using Devices_Cartridge=Devices::Cartridge::CartridgeDevice;
namespace Port::Stm32h743::Devices {

class CartridgeDevice : public Devices_Cartridge
{
public:
	CartridgeDevice(::Port::MCU *_mcu,Sys_FilesystemInterface *_fs,uint8_t *workBuffer,uint32_t buflen);
	inline void holdReset(){}
	inline void releaseReset(){}
	inline void waitForC64On(){}
	virtual ~CartridgeDevice();
};
}

#endif /* SRC_PORT_STM32H743_DEVICES_CARTRIDGE_CARTRIDGEDEVICE_H_ */
