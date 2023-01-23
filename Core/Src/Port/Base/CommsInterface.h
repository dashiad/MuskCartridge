#ifndef _COMMSINTERFACE_H_
#define _COMMSINTERFACE_H_
#include "Port/Base/Messages.h"
namespace Port {
	namespace Base {
		class CommsInterface;
	}
}
#include "Port/Base/MessageManager.h"
#include "Sys/Module.h"
#include "Sys/Result.h"
namespace Port {
	namespace Base{
		class CommsInterface : public ::Sys::Module{
		public:
			static const char *RES_INVALID_MESSAGE;
			CommsInterface(const char *_moduleName);
			virtual bool ready(){return true;}
			virtual void init(::Port::Base::MessageManager *manager,::Sys::Result *res)=0;
			virtual void select(){}
			virtual void setReceiveInterrupt(){}
			virtual void deselect(){}
			virtual const char *getModuleName(){return moduleName;}
			virtual void sendBytes(uint8_t *buf, uint32_t len,uint32_t timeoutMillis)=0;
			virtual int receiveBytes(uint8_t *buf, uint32_t len,uint32_t timeoutMillis)=0;
		protected:

			char moduleName[MAX_MODULE_NAME];
		};
	}
}

#endif
