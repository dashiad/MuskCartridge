/*
 * BaseFormat.cpp
 *
 *  Created on: 1 gen 2022
 *      Author: Jose
 */

#include "BaseFormat.h"
#include <stdbool.h>



namespace C64Formats {
const char *BaseFormat::RES_FILE_TOO_BIG="File too big";
const char *BaseFormat::RES_FILE_FORMAT_ERROR="File format error";

	BaseFormat::BaseFormat(uint8_t *_mainBuffer, uint32_t _buflen)
	{
		// TODO Auto-generated constructor stub
		mainBuffer=_mainBuffer;
		buflen=_buflen;
		file=0;
	}

	bool BaseFormat::loadFromFile(Sys_File *_file, Sys_Result *res)
	{
		file=_file;
		size_t fileSize=file->getSize(res);
		if(fileSize > buflen)
		{
			// Ignoring here space used by headers,etc..If the total file size is greater than the
			// available buffer, just bail out
			res->setError(getModuleName(),BaseFormat::RES_FILE_TOO_BIG);
			return false;
		}
		return parse(res);
	}

	int BaseFormat::readBuf(uint8_t *buf, uint32_t size, Sys_Result *res)
	{
		return file->read(buf, size, res);
	}

BaseFormat::~BaseFormat() {
	// TODO Auto-generated destructor stub

}
}

