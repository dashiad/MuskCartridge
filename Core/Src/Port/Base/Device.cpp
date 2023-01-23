#include "Device.h"
#include <string.h>
#include <stdio.h>
#include "Sys/File.h"
#include "Port/Stm32h743/Sys/SDCard.h"
#include "Port/Stm32h743/Devices/Cartridge/CartridgeDevice.h"
extern uint8_t cart_buffer[512*1024];;
namespace Port {
    namespace Base{
        Device::Device(Slave *_slave, char *_deviceName,int _fileMask, int _hardwareMask)
        {
            parent=_slave;
            strncpy(deviceName,_deviceName,MESSAGE_MAX_DEVICE_NAME);
            deviceId=_slave->addDevice(this);
            fileMask=_fileMask;
            hardwareMask=_hardwareMask;
            

        }
        void Device::receiveFileTransfer(_FileTransferMessage *msg)
        {
        	::Sys::Result res;
        	FatFsFilesystem fs;

            curFile = fs.createFileInstance();
            //curFile->open((char *)(msg->fileName), Sys::CREATE_NEW,&res);

            sprintf(lastFile,"0:/%s",(char *)(msg->fileName),255);
            curFile->open(lastFile, Sys::CREATE_ALWAYS | Sys::WRITE,&res);



        }
        void Device::receiveFileBlock(_FileBlockMessage *msg)
        {
        	::Sys::Result res;

            curFile->write(msg->block,msg->length,&res);
            if(msg->length < MESSAGE_MAX_FILE_BLOCK_SIZE)
            {
            	curFile->close();
            	 Port::Stm32h743::Sys::SDCard sdcard;
            	 sdcard.init(&res);
            	 Port::Stm32h743::MCU MCU;
            	 MCU.resetC64();
            	 Port::Stm32h743::Devices::CartridgeDevice cartDevice(&MCU,&sdcard,cart_buffer,sizeof(cart_buffer));

            	 cartDevice.mount(lastFile,&res);
            }
        }
    }
}
