/*
 * NullHWFactory.h
 *
 *  Created on: 5 mar 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_BASE_NULLHWFACTORY_H_
#define SRC_PORT_BASE_NULLHWFACTORY_H_
#include "HWFactory.h"
namespace Port {
namespace Base {

class NullCommsInterface : public CommsInterface{
public:

	NullCommsInterface();
	virtual void initialize(::Sys::Result *res);
	virtual void initialize(CommsInterface *_remote,::Sys::Result *res);
	virtual void send(Message *msg,::Sys::Result *res);

protected:
	inline virtual void sendBytes(uint8_t *buf, uint32_t len,uint32_t timeoutMillis,::Sys::Result *res){}
	inline virtual int receiveBytes(uint8_t *buf, uint32_t len,uint32_t timeoutMillis,::Sys::Result *res){return len;}
	CommsInterface *remote;
};

class NullHWFactory: public HWFactory {
public:
	NullHWFactory();
	virtual MasterRepr *getMasterRepr(Slave *_slave);
	virtual SlaveRepr *getSlaveRepr(uint8_t index, Master *_master);
	virtual UIRepr *getUIRepr(Master *_master)=0;
	virtual ~NullHWFactory();
protected:

	NullCommsInterface *masterComms;

};

} /* namespace Base */
} /* namespace Port */

#endif /* SRC_PORT_BASE_NULLHWFACTORY_H_ */
