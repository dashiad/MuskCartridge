/*
 * NullHWFactory.cpp
 *
 *  Created on: 5 mar 2022
 *      Author: Jose
 */

#include <Port/Base/NullHWFactory.h>

namespace Port {
namespace Base {

NullCommsInterface::NullCommsInterface():CommsInterface("NullCommsInterface")
{


}
void NullCommsInterface::initialize(::Sys::Result *res)
{

}
void NullCommsInterface::initialize(CommsInterface *_remote,::Sys::Result *res)
{
	remote=_remote;
	res->setOk();
	initialize(res);
}
void NullCommsInterface::send(Message *msg, ::Sys::Result *res)
{
	//remote->receive(msg,res);
}



NullHWFactory::NullHWFactory() {
	/* The master comms interface is created now. In this way, we can connect
		 * slaves to it, even if they're created before the master, and there's no need
		 * to retrieve this comms pointer from the master to attach it to the slaves.
		 */
		//masterComms=new NullCommsInterface();
}

MasterRepr *NullHWFactory::getMasterRepr(Slave *_slave)
{
	return new ::Port::Base::MasterRepr(_slave,masterComms);
}
SlaveRepr *NullHWFactory::getSlaveRepr(uint8_t index,Master *_master)
{
	/*NullCommsInterface *slaveComms=new NullCommsInterface();
	::Sys::Result res;
	slaveComms->initialize(masterComms,&res);
	return new ::Port::Base::SlaveRepr(index,_master,slaveComms);*/
}

NullHWFactory::~NullHWFactory() {

}

} /* namespace Base */
} /* namespace Port */
