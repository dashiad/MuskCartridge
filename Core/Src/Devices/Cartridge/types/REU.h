/*
 * REU.h
 *
 *  Created on: 22 gen 2022
 *      Author: Jose
 */

#ifndef SRC_DEVICES_CARTRIDGE_TYPES_REU_H_
#define SRC_DEVICES_CARTRIDGE_TYPES_REU_H_
#include "Devices/Cartridge/types/BaseDevice.h"
namespace Devices::Cartridge::types {

#define CRT_REU_STATUS_INTERRUPT_PEDING 0x80
#define CRT_REU_STATUS_END_OF_BLOCK 	0x40
#define CRT_REU_STATUS_FAULT			0x20
#define CRT_REU_STATUS_SIZE 			0x10
#define CRT_REU_COMM_EXECUTE			0x80
#define CRT_REU_COMM_LOAD				0x20
#define CRT_REU_COMM_IMMEDIATE			0x10
#define CRT_REU_COMM_TRANSFER_TYPE_MASK 0x03

class REU : public BaseDevice
{
public:

	REU(::Devices::Cartridge::CartridgeDevice *cart,uint8_t *buf,int bufLen);
	virtual void run();
	inline virtual void runCommand(int baLeft)
	{
		switch((*commandReg) & CRT_REU_COMM_TRANSFER_TYPE_MASK)
		{
		case 0:{runTransferToREU(baLeft);}break;
		case 1:{runTransferToC64(baLeft);}break;
		case 2:{runSwap(baLeft);}break;
		case 3:{runCompare(baLeft);}break;
		}
	}
	virtual void init();
	virtual void runTransferToREU(int baLeft);
	virtual void runTransferToC64(int baLeft);
	virtual void runSwap(int baLeft);
	virtual void runCompare(int baLeft);
	virtual ~REU();
private:

	// Note: The REU only has 11 registers, but 12 bytes will be needed because
	// reuBaseAddressReg is a 24 bit address, that we'll be storing in a 32 bit field.
	// When the accessed register is 0x07-0x0A, 1 will be added to account for that extra byte.
	uint8_t registers[12];
	uint8_t *statusReg; // $DF00, 57088
	uint8_t *commandReg; // $DF01, 57089
	uint16_t *c64BaseAddressReg; // $DF02,$DF03 57090, 57091
	uint32_t *reuBaseAddressReg; // $DF04,$DF05,$DF06  57902,57903,57904
	uint16_t *transferLengthReg; // $DF07, $DF08 57905 57906
	uint8_t *interruptReg;  // $DF09 57907
	uint8_t *addressControlReg; // $DF10 57908
	uint8_t bytesRead[1000];

};

}

#endif /* SRC_DEVICES_CARTRIDGE_TYPES_REU_H_ */
