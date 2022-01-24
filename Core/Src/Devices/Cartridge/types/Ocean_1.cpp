/*
 * MagicDesk.cpp
 *
 *  Created on: 8 gen 2022
 *      Author: Jose
 */

#include <Devices/Cartridge/types/Ocean_1.h>

namespace Devices::Cartridge::types{

Ocean_1::Ocean_1(::Port::MCU *_mcu,::Devices::Cartridge::CartridgeDevice *_device,::C64Formats::Crt *crt):Base(_mcu,_device,crt) {

	CRT_SET_AS_16K;

}
void Ocean_1::run()
{
	uint16_t control;
	uint16_t addr;
	uint8_t data;
	bool isWriting=false;
	uint8_t *loBuffer=curBank->loBuffer;
	uint8_t *hiBuffer=curBank->hiBuffer;

	while(1)
	{
		CRT_DEFAULT_READ_PROC
		if(!(CRT_GET_RW(control)))
		{
			control=CRT_READCONTROL;
			if(!CRT_GET_IO1(control))
			{
				data=CRT_READDATA;
				curBank=crt->getBankPointer(data & 0x1f);
				loBuffer=curBank->loBuffer;
				hiBuffer=curBank->hiBuffer;
			}
		}
		DEBUG1_OFF;
		CRT_WAITFORCLOCKEND;

			//DEBUG1_OFF;

		}
}
Ocean_1::~Ocean_1() {
	// TODO Auto-generated destructor stub
}

} /* namespace types */
