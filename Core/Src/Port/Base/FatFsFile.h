/*
 * FatFsFile.h
 *
 *  Created on: 3 gen 2022
 *      Author: Jose
 */

#ifndef SRC_PORT_BASE_FATFSFILE_H_
#define SRC_PORT_BASE_FATFSFILE_H_
#include "Sys/File.h"
#include "Sys/Result.h"
#include "fatfs.h"
using Sys_File=Sys::File;
using Sys_Result=Sys::Result;
namespace Port::Base {
class FatFsFile : public Sys_File{
	public:

		FatFsFile();
		bool open(char *filename, int mode,Sys_Result *res);
		size_t read(uint8_t *buffer,int len,Sys_Result *res);
		size_t write(uint8_t *buffer,int len,Sys_Result *res);
		size_t getSize(Sys_Result *res);
		bool isEof();
		void close();
		inline const char *getModuleName(){return "FatFsFile";}
		~FatFsFile();
	private:
		bool isOpen;
		FIL file;
	};

} /* namespace Port */

#endif /* SRC_PORT_BASE_FATFSFILE_H_ */
