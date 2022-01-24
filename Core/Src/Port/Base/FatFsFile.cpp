/*
 * FatFsFile.cpp
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#include <Port/Base/FatFsFile.h>

namespace Port {
namespace Base {


FatFsFile::FatFsFile() {
	isOpen=false;
}
bool FatFsFile::open(char *filename, int mode,Sys_Result *res)
{
	if(isOpen)
		close();
	int mask=0;
	if(mode & Sys::CREATE_ALWAYS)
	{
		mask |= FA_CREATE_ALWAYS;
	}
	if(mode & Sys::CREATE_NEW)
	{
		mask |= FA_CREATE_NEW;
	}
	if(mode & Sys::OPEN_APPEND)
	{
		mask |= FA_OPEN_APPEND;
	}
	if(mode & Sys::OPEN_EXISTING)
	{
			mask |= FA_OPEN_EXISTING;
	}
	if(mode & Sys::READ)
	{
		mask |= FA_READ;
	}
	if(mode & Sys::WRITE)
	{
		mask |=FA_WRITE;
	}

	FRESULT fres = f_open(&file, filename, mask);
	if(fres!=FR_OK)
	{
		res->setError(getModuleName(), FatFsFile::RES_FILE_NOT_FOUND);
		return false;
	}
	isOpen=true;
	return true;
}
size_t FatFsFile::read(uint8_t *buffer,int len,Sys_Result *res)
{
	if(!isOpen)
	{
		res->setError(getModuleName(),FatFsFile::RES_FILE_NOT_OPEN);
		return -1;
	}
	uint32_t bytesRead;
	FRESULT fres = f_read(&file, (void *)buffer, len,(unsigned int *) &bytesRead);
	if (fres != FR_OK)
	{
			res->setError(getModuleName(),FatFsFile::RES_FILE_READ_ERROR);
			return -1;
	}
	return bytesRead;

}
size_t FatFsFile::write(uint8_t *buffer,int len,Sys_Result *res)
{
	if(!isOpen)
		{
			res->setError(getModuleName(),FatFsFile::RES_FILE_NOT_OPEN);
			return -1;
		}
	size_t bytesWritten;
	FRESULT fres = f_write(&file, (const void *)buffer, len, &bytesWritten);
	if (fres != FR_OK)
	{
		res->setError(getModuleName(),FatFsFile::RES_FILE_WRITE_ERROR);
		return -1;
	}
	return bytesWritten;

}
size_t FatFsFile::getSize(Sys_Result *res)
{
	if(!isOpen)
	{
		res->setError(getModuleName(),FatFsFile::RES_FILE_NOT_OPEN);
		return -1;
	}
	return f_size(&file);
}
void FatFsFile::close()
{
	if(isOpen)
	{
		f_close(&file);
	}
	isOpen=false;
}
bool FatFsFile::isEof()
{
	return f_eof(&file);
}

FatFsFile::~FatFsFile() {
	// TODO Auto-generated destructor stub
	close();
}

} /* namespace Base */
} /* namespace Port */
