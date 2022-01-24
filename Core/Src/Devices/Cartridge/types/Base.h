/*
 * Base.h
 *
 *  Created on: 4 gen 2022
 *      Author: Jose
 */

#ifndef SRC_DEVICES_CARTRIDGE_TYPES_BASE_H_
#define SRC_DEVICES_CARTRIDGE_TYPES_BASE_H_
namespace Devices::Cartridge::types {
	class Base;
}
#include "Devices/Cartridge/CartridgeDevice.h"
#include "C64Formats/Crt.h"
#include "Port/stm32h743/MCU.h"
#include <stdbool.h>

namespace Devices::Cartridge::types {
class Base {
public:
	inline Base(::Port::MCU *_mcu,::Devices::Cartridge::CartridgeDevice *_device,::C64Formats::Crt *_crt)
	{
		device=_device;
		mcu=_mcu;
		crt=_crt;
	}
	inline void init()
	{
		curBank=crt->getBankPointer(0);
		if(crt->getExrom())
				CRT_SETEXROMHI;
			else
				CRT_SETEXROMLO;
			if(crt->getGame())
				CRT_SETGAMEHI;
			else
				CRT_SETGAMELO;
	}
	virtual inline void runCrt(){run();}
	virtual void run()=0;
	inline bool defaultReadHandler(uint16_t control,uint16_t addr )
	{
		bool doWrite=false;
		uint8_t curByte=0;
		if(!CRT_GET_ROML(control))
		{
			curByte=curBank->loBuffer[addr & 0x1fff];
			doWrite=true;
		}
		else
		{
			if(!CRT_GET_ROMH(control))
			{
				curByte=curBank->hiBuffer[addr & 0x1fff];
				doWrite=true;
			}
		}
		if(doWrite)
		{
			DEBUG1_ON;
			CRT_SETDATAASOUTPUT;
			CRT_SETDATA(curByte);
			CRT_HOLDDATA;
			CRT_SETDATAASINPUT;
			DEBUG1_OFF;

		}
		return doWrite;
	}
	virtual ~Base();
protected:
	::Devices::Cartridge::CartridgeDevice *device;
	::Port::MCU *mcu;
	::C64Formats::Crt *crt;
	::C64Formats::CRT_BANK *curBank;
};

}
#endif /* SRC_DEVICES_CARTRIDGE_TYPES_BASE_H_ */
