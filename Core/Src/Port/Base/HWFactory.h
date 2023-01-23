/*
 * HWFactory.h
 *
 *  Created on: 18 feb 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_BASE_HWFACTORY_H_
#define SRC_PORT_BASE_HWFACTORY_H_
#include "Sys/Result.h"
#include "Sys/Module.h"
#include "Port/Base/Messages.h"
#include "Port/Base/Slave.h"
namespace Port {
namespace Base {

#define MAX_SLAVES 5
#define DEFAULT_TIMEOUT 1
#define MAX_SLAVE_DEVICES 5




class MasterRepr;
class SlaveRepr;
class UIRepr;
class Master;
class Slave;


class HWFactory {
public:
	virtual MasterRepr *getMasterRepr(Slave *_slave)=0;
	virtual SlaveRepr *getSlaveRepr(uint8_t index,Master *_master)=0;
	virtual UIRepr *getUIRepr(Master *_master)=0;
};


class UIRepr {
public:
	UIRepr(Master *_master,CommsInterface *_comms);
	CommsInterface *comms;
protected:
	Master *master;


};

class DeviceRepr {
public:
	DeviceRepr(SlaveRepr *_slave,DeviceId _deviceId,char *_deviceName,uint32_t _fileMask,uint32_t _deviceMask);
	inline void setStatus(DeviceStatusCode _status){status=_status;}
	inline DeviceStatusCode getStatus(){return status;}
	inline char *getName(){return deviceName;}
	inline DeviceId getId(){return id;}
	char deviceName[MESSAGE_MAX_DEVICE_NAME];
protected:

	DeviceStatusCode status;
	DeviceId id;
	SlaveRepr *slave;
	uint32_t deviceMask;
	uint32_t fileMask;

};


class SlaveRepr {
public:
	SlaveRepr(SlaveId _id,Master *_master,CommsInterface *_comms);
	void reset();
	void setName(char *name);
	inline SlaveId getId(){return id;}
	void setNDevices(int _nDevices);
	bool isLocked();
	void setLocked(bool _locked){locked=_locked;}
	virtual DeviceRepr *addDevice(
			DeviceId id,
			char *deviceName,
			uint32_t fileMask,
			uint32_t deviceMask);
	DeviceRepr *getDeviceByName(char *name);
	~SlaveRepr();
	CommsInterface *comms;
protected:
	Master *master;
	SlaveId id;
	bool isConnected;
	bool locked;
	char boardName[MESSAGE_MAX_BOARD_NAME];
	DeviceRepr *devices[MAX_SLAVE_DEVICES];
	int nDevices;
};





class MasterRepr {
public:
	MasterRepr(Slave *_slave,CommsInterface *_comms);
	~MasterRepr();
protected:
	Slave *slave;
	CommsInterface *comms;
};



class Master  {
public:
	Master(HWFactory *factory);
	virtual void run();
	UIRepr *getUI();
	virtual void setUIConnected();
	/* Message callbacks */

	virtual void onACK(SlaveRepr *slave,Message *msg,::Sys::Result *res);
	virtual void onError(SlaveRepr *slave,Message *msg,::Sys::Result *res);
	virtual void onHello(SlaveRepr *slave,Message *msg,::Sys::Result *res);
	virtual void onDeviceStatus(SlaveRepr *slave,Message *msg,::Sys::Result *res);
protected:
	virtual void processMessage(SlaveRepr *slave,Message *received,::Sys::Result *res);
	virtual void processUIMessages();
	virtual void processSlaveMessages(uint8_t idx);

	SlaveRepr *slaves[MAX_SLAVES];
	uint8_t currentSlave;
	UIRepr *ui;
	bool UIConnected;
	int lastDeviceId;

	::Sys::Result res;
};



} /* namespace Base */
} /* namespace Port */

#endif /* SRC_PORT_BASE_HWFACTORY_H_ */
