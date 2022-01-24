/*
 * FatFsFilesystem.h
 *
 *  Created on: 2 gen 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_BASE_FATFSFILESYSTEM_H_
#define SRC_PORT_BASE_FATFSFILESYSTEM_H_

#include "Sys/FilesystemInterface.h"
#include "Sys/Result.h"
#include "fatfs.h"
#include "FatFsFile.h"

using Sys_FilesystemInterface = Sys::FilesystemInterface;
using Sys_Result = Sys::Result;
namespace Port::Base
{

	class FatFsFilesystem : public Sys_FilesystemInterface
	{

		public:
			bool init(Sys_Result *res);
			inline const char *getModuleName(){return "FatFsFilesystem";}
			inline virtual Sys::File *createFileInstance(){return new FatFsFile();}
		private:

	};
}
#endif /* SRC_PORT_BASE_FATFSFILESYSTEM_H_ */
