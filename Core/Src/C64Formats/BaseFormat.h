/*
 * BaseFormat.h
 *
 *  Created on: 1 gen 2022
 *      Author: Jose
 */

#ifndef SRC_C64FORMATS_BASEFORMAT_H_
#define SRC_C64FORMATS_BASEFORMAT_H_
#include "Sys/File.h"
#include "Sys/Module.h"
#include <stdbool.h>



using Sys_File=Sys::File;
using Sys_Result=Sys::Result;
using Sys_Module=Sys::Module;
namespace C64Formats {

	class BaseFormat : public Sys_Module {
		public:
			static const char *RES_FILE_TOO_BIG;
			static const char *RES_FILE_FORMAT_ERROR;

			BaseFormat(uint8_t *_mainBuffer, uint32_t _buflen);
			bool loadFromFile(Sys_File *file,Sys_Result *res);
			inline uint8_t *getBuffer(){return mainBuffer;}
			inline virtual const char *getModuleName(){return "BaseFormat";}
			virtual ~BaseFormat();
		protected:
			virtual bool parse(Sys_Result *res)=0;
			int readBuf(uint8_t *buf, uint32_t size,Sys_Result *res);
			Sys_File *file;
			uint8_t *mainBuffer;
			uint32_t buflen;
	};
}

#endif /* SRC_C64FORMATS_BASEFORMAT_H_ */
