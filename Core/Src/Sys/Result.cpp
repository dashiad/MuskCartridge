/*
 * Result.cpp
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#include <Sys/Result.h>

namespace Sys {

Result::Result() {
	// TODO Auto-generated constructor stub
	hasError=false;
}

void Result::setError(const char *_errModule,const char *_errMessage)
{
	errModule=_errModule;
	errMessage=_errMessage;
}

Result::~Result() {
	// TODO Auto-generated destructor stub
}

} /* namespace Sys */
