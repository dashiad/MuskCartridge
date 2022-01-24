/*
 * Result.h
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#ifndef SRC_SYS_RESULT_H_
#define SRC_SYS_RESULT_H_
#include <stdbool.h>

namespace Sys {

class Result {
public:
	Result();
	inline bool isErrored(){return hasError;}
	void setError(const char *errModule,const char *errMessage);
	inline bool isOk(){return !hasError;}
	virtual ~Result();
protected:
	bool hasError;
	const char *errMessage;
	const char *errModule;
};

} /* namespace Sys */

#endif /* SRC_SYS_RESULT_H_ */
