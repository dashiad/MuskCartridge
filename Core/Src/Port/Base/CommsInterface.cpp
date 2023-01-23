#include "Port/Base/CommsInterface.h"
#include <string.h>
namespace Port {
namespace Base {
const char *CommsInterface::RES_INVALID_MESSAGE    ="Invalid message code received";

/**
 *
 *    CLASS COMMSINTERFACE
 *
 *
 */
CommsInterface::CommsInterface( const char *_moduleName){
		strncpy(moduleName,_moduleName,MAX_MODULE_NAME);
}


}
}
