/*
 * MagicDesk.cpp
 *
 *  Created on: 8 gen 2022
 *      Author: Jose
 */

#include <Devices/Cartridge/types/MagicDesk.h>

namespace Devices::Cartridge::types{

MagicDesk::MagicDesk(::Port::MCU *_mcu,::Devices::Cartridge::CartridgeDevice *_device,::C64Formats::Crt *crt):Base(_mcu,_device,crt) {

	CRT_SET_AS_8K;

}
void MagicDesk::run()
{
	uint16_t control;
	uint16_t addr;
	uint8_t data;
	bool isWriting=false;
	uint8_t *loBuffer=curBank->loBuffer;
	uint8_t *hiBuffer=curBank->hiBuffer;
	while(1)
	{
			CRT_WAITFORCRTPHY2HIGH;
			control=CRT_READCONTROL;
			addr=CRT_READADDR;
			if(CRT_GET_RW(control)) {
				if(!CRT_GET_ROML(control)) {
					CRT_OUTPUT_BYTE(loBuffer[addr & 0x1fff]); }
			}
			else
			{
				// IO1 is being activated later in the cycle, so
				// control is re-read here.
				control=CRT_READCONTROL;
				if(!(CRT_GET_IO1(control)) )
				{
					data=CRT_READDATA;
					CRT_SET_AS_8K;
					if(!(data & 0x80))
					{
					curBank=crt->getBankPointer(data & 0x3f);
						loBuffer=curBank->loBuffer;
						hiBuffer=curBank->hiBuffer;
					}
					else
					{
						CRT_DISCONNECT;
					}
				}

		}
		CRT_WAITFORCLOCKEND;
	}
}
MagicDesk::~MagicDesk() {
	// TODO Auto-generated destructor stub
}

} /* namespace types */
