/*
 * File.h
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#ifndef SRC_SYS_FILE_H_
#define SRC_SYS_FILE_H_
#include "Result.h"
#include "Module.h"
#include "fatfs.h"
#include <stdint.h>
namespace Sys {
typedef enum OpeningModes
{
	CREATE_ALWAYS=0x01,
	CREATE_NEW=0x02,
	OPEN_APPEND=0x04,
	OPEN_EXISTING=0x08,
	READ=0x10,
	WRITE=0x20
} OpeningModes;

class File : public Module {
public:
	static const char *RES_FILE_NOT_OPEN;
	static const char *RES_FILE_NOT_FOUND;
	static const char *RES_FILE_READ_ERROR;
	static const char *RES_FILE_WRITE_ERROR;
	File();
	/* Mode is a mask composed by OpeningModes */
	virtual bool open(char *filename, int mode,Result *res)=0;
	virtual size_t read(uint8_t *buffer,int len,Result *res)=0;
	virtual size_t write(uint8_t *buffer,int len,Result *res)=0;
	virtual bool isEof()=0;
	virtual void close()=0;
	virtual size_t getSize(Result *res)=0;
	virtual ~File();
};

} /* namespace Sys */

#endif /* SRC_SYS_FILE_H_ */
