#include "Messages.h"
namespace Port
{
    namespace Base {

    char *messageEncoding[__LAST_MESSAGE__]={
    		"",
			"ibbi", // ACK=1,
			"ibbis", // Error,
			"ibbiis", // FileTransfer,
			"ibbix", // FileBlock,
			"ibbis", // FileRequest,
			"ib", // Ping,
			"ibbis", // Mount,
			"ibbis", // DeviceAction,
			"ibb", // Reset,
			"iis", // Hello,
			"iibbbs", // DeviceSpecs,
			"ibbi", // DeviceStatus,
			"iibbiis" // Register

    };
    }
}
