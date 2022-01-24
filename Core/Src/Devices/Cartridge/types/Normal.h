/*
 * Normal.h
 *
 *  Created on: 4 gen 2022
 *      Author: Jose
 */

#ifndef SRC_DEVICES_CARTRIDGE_TYPES_NORMAL_H_
#define SRC_DEVICES_CARTRIDGE_TYPES_NORMAL_H_
#include "Base.h"
namespace Devices::Cartridge::types {

class Normal : public Base
{
public:
	inline Normal(::Port::MCU *mcu,::Devices::Cartridge::CartridgeDevice *device,::C64Formats::Crt *crt):Base(mcu,device,crt){}
	void run();

	virtual ~Normal();
};
}


#endif /* SRC_DEVICES_CARTRIDGE_TYPES_NORMAL_H_ */
