/*
 * EasyFlash.cpp
 *
 *  Created on: 8 gen 2022
 *      Author: Jose
 */

#include <Devices/Cartridge/types/EasyFlash.h>
#include <string.h>
#define EF3_RX_RDY  (0x80)
#define EF3_TX_RDY  (0x40)
#define EF3_NOT_RDY (0x00)

namespace Devices::Cartridge::types{

	EasyFlash::EasyFlash(::Port::MCU *_mcu,::Devices::Cartridge::CartridgeDevice *_device,::C64Formats::Crt *crt):Base(_mcu,_device,crt) {
		memset(efRam,0,255);


}
void EasyFlash::run()
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
		 addr=CRT_READADDR;
		 control=CRT_READCONTROL;


		if(CRT_GET_RW(control)) {

			if(!CRT_GET_ROML(control)) {
				CRT_OUTPUT_BYTE(loBuffer[addr & 0x1fff]);
			} else {
			if(!CRT_GET_ROMH(control) && hiBuffer!=0) {
				CRT_OUTPUT_BYTE(hiBuffer[addr & 0x1fff]);
			}
			}
			//control=CRT_READCONTROL;
			//if(addr>=0xdf00 && addr<=0xdfff)
			if(!CRT_GET_IO2(control))
			{
					CRT_OUTPUT_BYTE(efRam[addr & 0xFF]);
			}
		}
		else
		{
			data=CRT_READDATA;
			//control=CRT_READCONTROL;
				 if(!CRT_GET_IO1(control))
				 {
					 switch(addr & 0xff)
					 {
					 	 case 0:{

					 		curBank=crt->getBankPointer(data & 0x3f);
					 		loBuffer=curBank->loBuffer;
					 		hiBuffer=curBank->hiBuffer;
					 	 }break;
					 	 case 2:{
					 		 if(data & 0x02)
					 			 CRT_SETEXROMLO;
					 		 else
					 			 CRT_SETEXROMHI;

					 		 if((data & 0x05) == 0x05)
					 			 CRT_SETGAMELO;
					 		 else
					 			 CRT_SETGAMEHI;

					 	 }break;

					 }
				 }
				 else
				 {
					if(!CRT_GET_IO2(control))
					 //if(addr>=0xdf00 && addr<=0xdfff)
					{
						DEBUG1_ON;
						efRam[addr & 0xFF]=data;
						DEBUG1_OFF;

					}
				 }

		}
		CRT_WAITFORCLOCKEND;

			//DEBUG1_OFF;

		}
}
EasyFlash::~EasyFlash() {
	// TODO Auto-generated destructor stub
}

} /* namespace types */
