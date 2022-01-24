/*
 * BaseDevice.h
 *
 *  Created on: 22 gen 2022
 *      Author: Jose
 */

#ifndef SRC_DEVICES_CARTRIDGE_TYPES_BASEDEVICE_H_
#define SRC_DEVICES_CARTRIDGE_TYPES_BASEDEVICE_H_
namespace Devices::Cartridge::types {
	class BaseDevice;
}
#include "Devices/Cartridge/CartridgeDevice.h"
namespace Devices {
namespace Cartridge {
namespace types {

class BaseDevice {
public:
	BaseDevice(::Devices::Cartridge::CartridgeDevice *_cart,uint8_t *buf,int bufLen);
	virtual void init(){}
	inline void runDevice(){run();}
	virtual void run()=0;
	virtual ~BaseDevice();
protected:
	::Devices::Cartridge::CartridgeDevice *cart;
	uint8_t *buffer;
	int bufLen;
};

}
}
}


#endif /* SRC_DEVICES_CARTRIDGE_TYPES_BASEDEVICE_H_ */
