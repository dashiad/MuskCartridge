/*
 * Module.h
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#ifndef SRC_SYS_MODULE_H_
#define SRC_SYS_MODULE_H_

namespace Sys {

class Module {
public:
	Module(){};
	virtual const char *getModuleName()=0;
	virtual ~Module(){};
};

} /* namespace Sys */

#endif /* SRC_SYS_MODULE_H_ */
