/*
 * CartridgeDevice.cpp
 *
 *  Created on: 2 gen 2022
 *      Author: Jose
 */

#include "CartridgeDevice.h"
#include "Devices/Cartridge/types/Normal.h"
#include "Devices/Cartridge/types/MagicDesk.h"
#include "Devices/Cartridge/types/Ocean_1.h"
#include "Devices/Cartridge/types/EasyFlash.h"
#include "Devices/Cartridge/types/REU.h"


namespace Devices::Cartridge
{
	CartridgeDevice::CartridgeDevice(::Port::MCU *_mcu,Sys_FilesystemInterface *_fs,uint8_t *_mainBuffer,uint32_t _buflen) {
		// TODO Auto-generated constructor stub
		mcu=_mcu;
		fs=_fs;
		mainBuffer=_mainBuffer;
		curDevice=0;
		bufLen=_buflen;
		curFile=0;
		handler=0;
		crtFile=0;
	}
	void CartridgeDevice::reset()
	{
		if(curFile)
			delete curFile;
		if(handler)
			delete handler;
		if(crtFile)
			delete crtFile;
		if(curDevice)
			delete curDevice;
	}
	void CartridgeDevice::init(bool resetC64)
	{
		CRT_SETIRQASINPUT;
		CRT_SETDMAHI;
		CRT_SETNMIHI;
		CRT_SETRESETHI;

		if(CRT_HASPOWER && resetC64)
			mcu->resetC64();
		else
			while(!(CRT_HASPOWER));
	}

	bool CartridgeDevice::mount(char *fileName,::Sys::Result *res)
	{
		reset();


		crtFile=new Crt(mainBuffer,bufLen);

		curFile=fs->createFileInstance();
		curFile->open(fileName, Sys::READ, res);
		if(!res->isOk())
		{
			return false;
		}
		crtFile->loadFromFile(curFile,res);
		getHandler(res);
		if(res->isOk())
		{
		run();
		}
		return true;
	}

	void CartridgeDevice::run()
	{

		init(true);
		handler->init();
		while(CRT_READADDR!=0xFFFC);
		handler->runCrt();
	}

	void CartridgeDevice::getHandler(::Sys::Result *res)
	{
		switch(crtFile->getType())
		{
			case C64Formats::CRT_NORMAL_CARTRIDGE:{
				handler = new ::Devices::Cartridge::types::Normal(mcu,this,crtFile);
			}break;
			case C64Formats::CRT_MAGIC_DESK_DOMARK_HES_AUSTRALIA:{
				handler = new ::Devices::Cartridge::types::MagicDesk(mcu,this,crtFile);
			}break;
			case C64Formats::CRT_EASYFLASH:
			{
				handler=new ::Devices::Cartridge::types::EasyFlash(mcu,this,crtFile);
			}break;
			case C64Formats::CRT_OCEAN_TYPE_1:{
				handler=new ::Devices::Cartridge::types::Ocean_1(mcu,this,crtFile);
			}
			default:{}
		}
	}

	bool CartridgeDevice::mountDevice(crtDevice deviceId)
	{
		reset();

		switch(deviceId)
		{
			case crtDevice::CRT_DEVICE_REU:
			{
				curDevice=new ::Devices::Cartridge::types::REU(this,mainBuffer,bufLen);

			}break;
		}
		init(false);
		curDevice->init();
		while(CRT_READADDR!=0xFFFC);
		curDevice->run();
		return true;
	}

	CartridgeDevice::~CartridgeDevice() {
	// TODO Auto-generated destructor stub
		reset();
	}

}
