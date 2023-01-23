#include "Slave.h"
#include <string.h>

namespace Port {
    namespace Base{
        Slave::Slave(uint8_t _slaveId,char *_name,uint8_t _hiVersion,uint8_t _loVersion)
        {
            slaveId=_slaveId;
            strncpy(name,_name,MESSAGE_MAX_DEVICE_NAME);
            hiVersion=_hiVersion;
            loVersion=_loVersion;
            nDevices=0;
            
        }

        uint8_t Slave::addDevice(Device *device)
        {            
            devices[nDevices]=device;
            nDevices++;
            return nDevices;
        }
        Device *Slave::getDeviceById(uint8_t id)
        {
            return devices[id];
        }
        void Slave::onMessage(Message *msg)
        {
            // Para acceder al código, nos da igual el tipo al que hagamos cast al puntero.
            switch(((_ACKMessage *)msg)->code)
            {
                case ACK:{
                    if(!((ACKMessage *)msg)->code==nextACK)
                    {
                        // Error de ACK!
                    }
                }break;
                case FileTransfer:{                    
                    _FileTransferMessage *ft=(_FileTransferMessage *)msg;
                    Device *target=getDeviceById(ft->deviceId);
                    target->receiveFileTransfer(ft);
                    msgManager.sendACK(slaveId,target->deviceId,ft->reqId);
                }break;
                case FileBlock:{                    
                    _FileBlockMessage *ft=(_FileBlockMessage *)msg;
                    Device *target=getDeviceById(ft->deviceId);
                    target->receiveFileBlock(ft);
                    msgManager.sendACK(slaveId,target->deviceId,ft->reqId);
                }break;
                
            }   
        }

        void Slave::run(CommsInterface *_serial)
        {
        	::Sys::Result res;
        	this->serial=_serial;
        	_serial->init(&msgManager,&res);

        	msgManager.init(_serial);
        	_serial->sendBytes((uint8_t *)"****", 4, 2000);
        	int plusCounter=0;
        	uint8_t c;
        	while(plusCounter < 4)
        	{
        		_serial->receiveBytes(&c, 1, 2000);
        		if(c=='+')
        			plusCounter++;
        		else
        			plusCounter=0;
        	}
        	_serial->setReceiveInterrupt();
            sayHello();
            this->serial->setReceiveInterrupt();
            while(1)
            {

            	if(msgManager.hasMessage())
            	{
            		msgManager.clearMessage();
            		onMessage(&msgManager.curMessage);
            		this->serial->setReceiveInterrupt();
            	}
            }

        }
        void Slave::sayHello()
        {

            msgManager.sendHello((uint8_t *)name);
            nextACK=msgManager.getLastReqId();
            this->serial->setReceiveInterrupt();
            while(!msgManager.hasMessage());
            msgManager.sendDeviceSpecs(slaveId,(uint8_t *)name,hiVersion,loVersion);

            nextACK=msgManager.getLastReqId();
            this->serial->setReceiveInterrupt();
            while(!msgManager.hasMessage());
            Device *cDevice;
            for(int i=0;i<nDevices;i++)
            {

                cDevice=getDeviceById(i);
                msgManager.sendRegister(
                    slaveId,
                    i,
                    (uint8_t *)cDevice->deviceName,
                    cDevice->fileMask,
                    cDevice->hardwareMask

                );
                nextACK=msgManager.getLastReqId();
                this->serial->setReceiveInterrupt();
                while(!msgManager.hasMessage());
            }

        }
    }
}
