/*
 * CartridgeDevice.h
 *
 *  Created on: 2 gen 2022
 *      Author: Jose
 */

#ifndef SRC_DEVICES_CARTRIDGE_CARTRIDGEDEVICE_H_
#define SRC_DEVICES_CARTRIDGE_CARTRIDGEDEVICE_H_
#include <stdint.h>
#include "Sys/Module.h"
namespace Devices::Cartridge {
class CartridgeDevice;
}
#include "Sys/FilesystemInterface.h"
#include <Port/MCU.h>
#include "C64Formats/Crt.h"
#include "Sys/Result.h"
#include "Devices/Cartridge/types/Base.h"
#include "Devices/Cartridge/types/BaseDevice.h"
#include "Port/Stm32h743/MCU.h"


using Crt=C64Formats::Crt;

using Sys_FilesystemInterface=Sys::FilesystemInterface;
using Sys_File=Sys::File;

namespace Devices::Cartridge {
typedef enum CrtDevice {
	CRT_DEVICE_NONE,
	CRT_DEVICE_REU = 1
} crtDevice;
class CartridgeDevice : public ::Sys::Module{
public:
	CartridgeDevice(::Port::MCU *_mcu,Sys_FilesystemInterface *_fs,uint8_t *workBuffer,uint32_t buflen);
	bool mount(char *fileName,::Sys::Result *res);
	bool mountDevice(crtDevice deviceId);
	virtual const char *getModuleName(){return "CartridgeDevice";}
	virtual Crt *getCrt(){return crtFile;}
	virtual void holdReset()=0;
	void init(bool resetC64=false);
	void reset();
	virtual void releaseReset()=0;
	virtual void waitForC64On()=0;
	virtual void getHandler(::Sys::Result *res);
	virtual inline ::Port::MCU *getMCU(){return mcu;}
	virtual ~CartridgeDevice();


private:
	void run();
	::Port::MCU *mcu;
	::Devices::Cartridge::types::BaseDevice *curDevice;
	uint8_t *mainBuffer;
	int bufLen;
	Crt *crtFile;
	Sys_FilesystemInterface *fs;
	Sys_File *curFile;
	types::Base *handler;
};
}
#endif /* SRC_DEVICES_CARTRIDGE_CARTRIDGEDEVICE_H_ */
