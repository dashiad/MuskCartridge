/*
 * DeviceDependent.h
 *
 *  Created on: 4 gen 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_MCU_H_
#define SRC_PORT_MCU_H_

#include "Sys/Module.h"
#include <stdint.h>
namespace Port {
#define CRT_OUTPUT_BYTE(X)  CRT_SETDATAASOUTPUT;CRT_SETDATA(X);CRT_HOLDDATA;CRT_SETDATAASINPUT;
#define CRT_DEFAULT_READ_PROC CRT_WAITFORCRTPHY2HIGH; \
	control=CRT_READCONTROL; \
	addr=CRT_READADDR; \
	if(CRT_GET_RW(control)) { \
		if(!CRT_GET_ROML(control)) { \
			CRT_OUTPUT_BYTE(loBuffer[addr & 0x1fff]);\
		} else { \
		if(!CRT_GET_ROMH(control) && hiBuffer!=0) {\
			CRT_OUTPUT_BYTE(hiBuffer[addr & 0x1fff]);\
		}\
		}\
	}


class MCU : public ::Sys::Module {
public:
	inline MCU(){};
	inline virtual void waitForCrtPhy2High()=0;
	inline virtual uint16_t crtReadControl()=0;
	inline virtual uint16_t crtReadAddr()=0;
	inline virtual uint16_t crtGetRomMask()=0;
	inline virtual void crtSetDataAsOutput()=0;
	inline virtual void crtSetData(uint8_t data)=0;
	inline virtual void crtHoldData()=0;
	inline virtual void crtSetDataAsInput()=0;
	inline virtual void crtWaitForClockEnd()=0;
	inline virtual void crtSetGameHi()=0;
	inline virtual void crtSetGameLo()=0;
	inline virtual void crtSetExromHi()=0;
	inline virtual void crtSetExromLo()=0;
	inline virtual void crtSetIrqHi()=0;
	inline virtual void crtSetResetHi()=0;
	inline virtual void crtSetResetLo()=0;
	inline virtual void crtSetDMAHi()=0;
	inline virtual void crtSetNMIHi()=0;

	inline virtual void crtSetIrqAsInput()=0;
	inline virtual void crtSetIrqAsOutput()=0;

	inline virtual void debug1On()=0;
	inline virtual void debug1Off()=0;

	inline virtual bool crtHasPower()=0;
	inline virtual void resetC64()=0;

	virtual ~MCU(){};
};

} /* namespace Port */

#endif /* SRC_PORT_MCU_H_ */
