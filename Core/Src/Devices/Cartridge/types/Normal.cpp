/*
 * Normal.cpp
 *
 *  Created on: 4 gen 2022
 *      Author: Jose
 */

#include <Devices/Cartridge/types/Normal.h>


namespace Devices::Cartridge::types {
void Normal::run()
{
	uint16_t control;
	uint16_t addr;
	uint8_t *loBuffer=curBank->loBuffer;
	uint8_t *hiBuffer=curBank->hiBuffer;
	while(1)
	{
		CRT_DEFAULT_READ_PROC
		CRT_WAITFORCLOCKEND;

	}
}

Normal::~Normal() {
	// TODO Auto-generated destructor stub
}

} /* namespace types */

