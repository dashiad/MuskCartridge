/*
 * MessageManager.h
 *
 *  Created on: 2 nov 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_BASE_MESSAGEMANAGER_H_
#define SRC_PORT_BASE_MESSAGEMANAGER_H_
namespace Port {
	namespace Base {
		class MessageManager;
	}
}
#include "Port/Base/Messages.h"
#include "Port/Base/CommsInterface.h"
#include <stdint.h>
typedef bool boolean;
namespace Port {
 	 namespace Base {
 	class MessageManager {
 	    public:
 	        MessageManager();
 	        void init (CommsInterface *_serial);
 			void onMessage();
 			boolean hasMessage();
 			void clearMessage(){messageFlag=false;}
 			int  getReqId();
 			int  getLastReqId(){return reqId;}
 			int getState(){return status;}
 			bool sendACK(uint8_t _slaveId,uint8_t _deviceId,int reqId);
 	        boolean sendHello(uint8_t *deviceName);
 			boolean sendDeviceSpecs(SlaveId slaveId,
 									uint8_t *name,
 									uint8_t	majorVersion,
 									uint8_t	minorVersion);
 			boolean sendRegister(
 				SlaveId slaveId,
 				DeviceId deviceId,
 				uint8_t *deviceName,
 				int fileMask,
 				int deviceMask
 			);
 	    public:
 			volatile boolean messageFlag;
 			Message curMessage;
 	    protected:
 	        CommsInterface *serial;
 	        unsigned char *buf[sizeof(_Message)];

 	        int curSize;
 	        int status;
 			int  reqId;
 	        void _reset(MessageCode code);
 	        int _flush();
 	        int _sendInt(int number);
 	        int _sendString(uint8_t *str);
 			int _sendByte(uint8_t byte);
 	        int _sendBytes(uint8_t *str,int length);
 			int _readInt();
 			int _readBytes(uint8_t *buf,int length);
 			uint8_t _readByte();
 			int _readString(uint8_t *buf);

 			boolean getACK(int _reqId);
 	};

 	 }
}



#endif /* SRC_PORT_BASE_MESSAGEMANAGER_H_ */
