/*
 * EasyFlash.h
 *
 *  Created on: 8 gen 2022
 *      Author: Jose
 */

#ifndef SRC_DEVICES_CARTRIDGE_TYPES_EASYFLASH_1_H_
#define SRC_DEVICES_CARTRIDGE_TYPES_OCEAN_1_H_
#include "Devices/Cartridge/types/Base.h"
namespace Devices::Cartridge::types{

class EasyFlash : public Base {
public:
	EasyFlash(::Port::MCU *_mcu,::Devices::Cartridge::CartridgeDevice *_device,::C64Formats::Crt *crt);
	void run();
	virtual ~EasyFlash();
private:
	uint8_t efRam[255];
};

} /* namespace types */


#endif /* SRC_DEVICES_CARTRIDGE_TYPES_EASYFLASH_1_H_ */
