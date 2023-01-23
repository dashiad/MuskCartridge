#ifndef _DEVICE_H_
#define _DEVICE_H_
#include "Messages.h"

#include "Port/Base/FatFsFilesystem.h"
#include "Port/Base/FatFsFile.h"
namespace Port {
    namespace Base {
        class Device;
    }
}
#include "Slave.h"
namespace Port {
    namespace Base {        
        class Device
        {
            public:
            Device(Slave *_parent, char *_deviceName,int _fileMask, int _hardwareMask);
            uint8_t getId();
            void receiveFileTransfer(_FileTransferMessage *msg);
            void receiveFileBlock(_FileBlockMessage *msg);                        
            Slave *parent;
            char lastFile[255];
            char deviceName[MESSAGE_MAX_DEVICE_NAME];
            uint8_t deviceId;
            unsigned int fileMask;
            unsigned int hardwareMask;
            ::Sys::File *curFile;
        };
    }
}
#endif
