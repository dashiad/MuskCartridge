/*
 * Module.h
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#ifndef SRC_SYS_MODULE_H_
#define SRC_SYS_MODULE_H_

namespace Sys {
#define MAX_MODULE_NAME 40
class Module {
public:
	Module(){};
	virtual const char *getModuleName()=0;
	virtual ~Module(){};
};

} /* namespace Sys */

#endif /* SRC_SYS_MODULE_H_ */
