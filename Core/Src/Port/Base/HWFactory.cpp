/*
 * HWFactory.cpp
 *
 *  Created on: 18 feb 2022
 *      Author: Jose
 */

#include <Port/Base/HWFactory.h>
#include <string.h>

namespace Port {
namespace Base {


/**
 *
 *     CLASS Master
 *
 *
 */
Master::Master(HWFactory *factory)
{
	UIConnected=false;
	for(int i=0;i<MAX_SLAVES;i++)
	{
		slaves[i]=factory->getSlaveRepr(i,this);
	}
	lastDeviceId=0;
	ui=factory->getUIRepr(this);


}
UIRepr *Master::getUI()
{return ui;}

	void Master::run()
	{
		while(1)
		{
			if(UIConnected)
			{
				processUIMessages();
			}
			for(int i=0;i<MAX_SLAVES;i++)
			{
				currentSlave=i;
				slaves[i]->comms->select();
				processSlaveMessages(i);
				slaves[i]->comms->deselect();
			}
		}
	}
	void Master::setUIConnected(){}
	void Master::processUIMessages(){}

	void Master::processSlaveMessages(uint8_t i)
	{
		SlaveRepr *slave=slaves[i];
		uint8_t messageCode;

			if(!slave->isLocked())
			{
				PingMessage ping;
				ping.code=Ping;
				ping.id=i;
				Message received;
				/*slave->comms->send((Message *)&ping, &res);
				while(slave->comms->receive(&received, &res))
				{
					processMessage(slave,&received,&res);
				}*/
			}

	}
	void Master::processMessage(SlaveRepr *slave,Message *received, ::Sys::Result *res)
	{
		MessageCode code=*((MessageCode *)received);
				switch(code)
				{
					case ACK:{
						onACK(slave,received,res);
						return;
					}break;
					case Error:{
						onError(slave,received,res);
					}break;
					case Hello:{
						onHello(slave,received,res);
					}break;
					case DeviceStatus:{
						onDeviceStatus(slave,received,res);
					}
					case FileRequest:
					case FileTransfer:
					case Ping:
					case Mount:
					case DeviceAction:
					case Reset:
					case DeviceSpecs:

					case FileBlock:{

					}break;
				}
	}

	void Master::onACK(SlaveRepr *slave,Message *msg,::Sys::Result *res)
	{
		return;
	}
	void Master::onError(SlaveRepr *slave,Message *msg,::Sys::Result *res)
	{
		// First, send it to the UI
		//if(UIConnected)
		//	ui->comms->send(msg,res);
	}
	void Master::onDeviceStatus(SlaveRepr *slave,Message *msg,::Sys::Result *res)
	{
		// Send it to the UI
		//if(UIConnected)
		//ui->comms->send(msg,res);
	}
	void Master::onHello(SlaveRepr *slave,Message *msg,::Sys::Result *res)
	{

	}
 /**
  *  SlaveRepresentation methods
  *
  *
  */
SlaveRepr::SlaveRepr(SlaveId _id,Master *_master,CommsInterface *_comms)
{
	 id=_id;
	 master=_master;
	 comms=_comms;
	 for(int i=0;i<MAX_SLAVE_DEVICES;i++)
		 devices[i]=0;
	 reset();

}
void SlaveRepr::reset()
{
	locked=false;
	for(int i=0;i<MAX_SLAVE_DEVICES;i++)
	{
		if(devices[i]!=0)
			delete devices[i];
	}
	nDevices=0;
}

void SlaveRepr::setName(char *name)
{
	strncpy(boardName,name,MESSAGE_MAX_BOARD_NAME);
}
void SlaveRepr::setNDevices(int _nDevices)
{
	nDevices=_nDevices;
}

DeviceRepr *SlaveRepr::addDevice(DeviceId id,char *deviceName,uint32_t fileMask,uint32_t deviceMask)
{
	if(getDeviceByName((char *)deviceName))
			return 0;
	DeviceRepr *newDevice=new DeviceRepr(this,id,deviceName,fileMask,deviceMask);
	for(int i=0;i<MAX_SLAVE_DEVICES;i++)
	{
		if(devices[i]==0)
		{
			devices[i]=newDevice;
			return newDevice;
		}
	}
	delete newDevice;
	return 0;
}
DeviceRepr *SlaveRepr::getDeviceByName(char *name)
{
	for(int i=0;i<MAX_SLAVE_DEVICES;i++)
	{
		if(devices[i]!=0)
		{
			if(!strcmp(devices[i]->deviceName,name))
					return devices[i];
		}
	}
	return 0;
}
bool SlaveRepr::isLocked()
{
	return false;
}
SlaveRepr::~SlaveRepr()
{
	delete comms;
	for(int i=0;i<MAX_SLAVE_DEVICES;i++)
	{
			delete devices[i];
	}
}

/**
 *
 *   DeviceRepr
 *
 */
DeviceRepr::DeviceRepr(SlaveRepr *_slave,DeviceId deviceId,char *_deviceName,uint32_t _fileMask,uint32_t _deviceMask)
{
	slave=_slave;
	id=deviceId;
	strncpy(deviceName,_deviceName,MESSAGE_MAX_DEVICE_NAME);
	fileMask=_fileMask;
	deviceMask=_deviceMask;
}


/**
 *    UIRepr
 */

UIRepr::UIRepr(Master *_m2,CommsInterface *_comms)
{

	comms=_comms;
}


/**
 *   MasterRepr
 */
MasterRepr::MasterRepr(Slave *_slave, CommsInterface *_comms)
{
	slave=_slave;
	comms=_comms;
}
MasterRepr::~MasterRepr()
{
	delete comms;
}

} /* namespace Base */
} /* namespace Port */
