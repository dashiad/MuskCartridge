/*
 * MagicDesk.h
 *
 *  Created on: 8 gen 2022
 *      Author: Jose
 */

#ifndef SRC_DEVICES_CARTRIDGE_TYPES_MAGICDESK_H_
#define SRC_DEVICES_CARTRIDGE_TYPES_MAGICDESK_H_
#include "Devices/Cartridge/types/Base.h"
namespace Devices::Cartridge::types{

class MagicDesk : public Base {
public:
	MagicDesk(::Port::MCU *_mcu,::Devices::Cartridge::CartridgeDevice *_device,::C64Formats::Crt *crt);
	void run();
	virtual ~MagicDesk();
};

} /* namespace types */


#endif /* SRC_DEVICES_CARTRIDGE_TYPES_MAGICDESK_H_ */
