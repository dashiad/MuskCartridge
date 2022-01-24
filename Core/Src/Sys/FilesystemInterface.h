/*
 * FilesystemInterface.h
 *
 *  Created on: 2 gen 2022
 *      Author: Jose
 */

#ifndef SRC_SYS_FILESYSTEMINTERFACE_H_
#define SRC_SYS_FILESYSTEMINTERFACE_H_
#include "Sys/Result.h"
#include "Sys/Module.h"
#include "Sys/File.h"
namespace Sys
{
	class FilesystemInterface : public Module {
	public:
		const static char *RES_FS_ERROR;
		virtual bool init(Sys::Result *res)=0;
		virtual File *createFileInstance()=0;
	};
}
#endif /* SRC_SYS_FILESYSTEMINTERFACE_H_ */
