/*
 * FatFsFilesystem.cpp
 *
 *  Created on: 2 gen 2022
 *      Author: Jose
 */

#include <Port/Base/FatFsFilesystem.h>
#include "Port/Base/FatFsFile.h"
#include "fatfs.h"
using Sys_FilesystemInterface = Sys::FilesystemInterface;
using Sys_Result = Sys::Result;
static FATFS fs;
namespace Port::Base{


	bool FatFsFilesystem::init(Sys_Result *res)
	{
		FRESULT f_res;
		f_res=f_mount(&fs, (TCHAR const*)SDPath, 0);
		if (f_res != FR_OK)
		{
			res->setError(getModuleName(), FatFsFilesystem::RES_FS_ERROR);
			return false;
		}

		return true;

	}

}
