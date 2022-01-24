/*
 * Result.h
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_STM32H743_SYS_RESULT_H_
#define SRC_PORT_STM32H743_SYS_RESULT_H_
#include "Sys/Result.h"
using Sys_Result = Sys::Result;
namespace Port::Stm32h743::Sys {

class Result:public Sys_Result {
public:
	Result();
	virtual ~Result();
};

} /* namespace Sys */


#endif /* SRC_PORT_STM32H743_SYS_RESULT_H_ */
