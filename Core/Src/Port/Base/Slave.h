#ifndef _SLAVE_H_
#define _SLAVE_H_
#include <stdint.h>
#include "Messages.h"
#include "MessageManager.h"

namespace Port {
    namespace Base {
        class Slave;
    }
}
#include "Device.h"
#define MAX_DEVICES_PER_SLAVE 5
namespace Port
{
    namespace Base
    {

        class Slave
        {
            public:
            Slave(uint8_t _slaveId,char *_name,uint8_t _hiVersion,uint8_t _loVersion);
            void initializeDevices();
            void onMessage(Message *msg);
            Device *getDeviceById(uint8_t deviceId);
            uint8_t addDevice(Device *device);
            void run(CommsInterface *serial);
            void sayHello();  
            void process();
            private:
            MessageManager msgManager;
            uint8_t slaveId;
            char name[MESSAGE_MAX_BOARD_NAME];
            uint8_t hiVersion;
            uint8_t loVersion;
            Device *devices[MAX_DEVICES_PER_SLAVE];
            uint8_t nDevices;
            int nextACK;
            CommsInterface *serial;
            

        };
    }
}

#endif
