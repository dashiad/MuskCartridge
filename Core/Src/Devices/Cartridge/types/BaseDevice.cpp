/*
 * BaseDevice.cpp
 *
 *  Created on: 22 gen 2022
 *      Author: Jose
 */

#include <Devices/Cartridge/types/BaseDevice.h>

namespace Devices {
namespace Cartridge {
namespace types {


BaseDevice::BaseDevice(::Devices::Cartridge::CartridgeDevice *_cart,uint8_t *_buffer, int _bufLen) {
	// TODO Auto-generated constructor stub
	cart=_cart;
	buffer=_buffer;
	bufLen=_bufLen;
}

BaseDevice::~BaseDevice() {
	// TODO Auto-generated destructor stub
}

}
}
}

