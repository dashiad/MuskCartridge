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
#define TF_END						     1

#define CRT_ADDR_FIX_REU_ADDR_MASK 0x40
#define CRT_ADDR_FIX_C64_ADDR_MASK 0x80

#define CRT_REU_PREWRITE_CYCLE CRT_WAITFORPHI2LOW; \
	control=CRT_READCONTROL; \
	if(!CRT_GET_BA(control)) \
	{  \
		CRT_WAITFORCLOCKEND; \
		continue; \
	}
#define CRT_REU_PREPARE_OUTPUT CRT_WAITFORCRTWRITEREADY; \
		CRT_SETRWASOUTPUT; \
		CRT_SETADDRASOUTPUT; \
		CRT_SETDATAASOUTPUT;




#define CRT_REU_FINISH_OUTPUT CRT_WAITHOLDWRITE; \
		CRT_SETRWASINPUT; \
		CRT_SETDATAASINPUT; \
		CRT_SETADDRASINPUT; \
		if((*transferLengthReg)==TF_END) \
		{ \
			CRT_SETDMAASINPUT; \
			return; \
		} \
		(*transferLengthReg)--;

#define CRT_REU_EXECUTE (*statusReg)=0x10;\
	mask=(*commandReg) & CRT_REU_COMM_TRANSFER_TYPE_MASK;\
	if(mask==0){ runTransferToREU(baLeft,0);\
	(*statusReg)|=CRT_REU_STATUS_END_OF_BLOCK;\
	} else {\
		if(mask==1){runTransferToC64(baLeft);\
	(*statusReg)|=CRT_REU_STATUS_END_OF_BLOCK;\
	} else {\
		if(mask==2){runSwap(baLeft);\
	(*statusReg)|=CRT_REU_STATUS_END_OF_BLOCK;\
	}else{\
		if(mask==3){\
		if(runTransferToREU(baLeft,1))\
			(*statusReg)|=CRT_REU_STATUS_END_OF_BLOCK;\
		else\
			(*statusReg)|=CRT_REU_STATUS_FAULT;\
	}}}\
	}\
	if((*commandReg) & CRT_REU_COMM_LOAD)\
	{\
		*(c64BaseAddressReg)=c64AddrBackup;\
		*(reuBaseAddressReg)=REUAddrBackup;\
		*(transferLengthReg)=transferSizeBackup;\
	}\
	else\
	{\
		if((*addressControlReg) & CRT_ADDR_FIX_REU_ADDR_MASK)\
			*(reuBaseAddressReg)=REUAddrBackup;\
		if((*addressControlReg) & CRT_ADDR_FIX_C64_ADDR_MASK)\
			*(c64BaseAddressReg)=c64AddrBackup;\
	}


class REU : public BaseDevice
{
public:

	REU(::Devices::Cartridge::CartridgeDevice *cart,uint8_t *buf,int bufLen);
	virtual void run();
	virtual void init();
	virtual int runTransferToREU(int baLeft,int isCompare);
	virtual void runTransferToC64(int baLeft);
	virtual void runSwap(int baLeft);
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
	uint8_t *addressControlReg; // $DF0A 57908

	int idx2=0;
	uint16_t c64AddrBackup;
	uint32_t REUAddrBackup;
	uint8_t reuAddrStep;
	uint8_t c64AddrStep;
	int idx;
	uint16_t transferSizeBackup;



};

}

#endif /* SRC_DEVICES_CARTRIDGE_TYPES_REU_H_ */
