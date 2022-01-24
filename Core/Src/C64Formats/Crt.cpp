/*
 * Crt.cpp
 *
 *  Created on: 1 gen 2022
 *      Author: Jose
 */

#include "Crt.h"
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fatfs.h"

namespace C64Formats {

	const char *Crt::RES_INVALID_SIGNATURE="Invalid signature";
	const char *Crt::RES_INVALID_HEADER="Invalid header";
	const char *Crt::RES_INVALID_CRT_VERSION="Invalid CRT version";
	const char *Crt::RES_INVALID_CHIP_SIGNATURE="Invalid chip signature";
	const char *Crt::RES_CHIP_HEADER_ERROR="Invalid chip header";
	const char *Crt::RES_UNKNOWN_CHIP_TYPE="Unknown chip type";
	const char *Crt::RES_TOO_MANY_BANKS="Too many banks";
	const char *Crt::RES_INVALID_BANK="Invalid bank";
	const char *Crt::CRT_SIGNATURE="C64 CARTRIDGE   ";
	const char *Crt::CRT_CHIP_SIGNATURE="CHIP";
	const uint16_t Crt::CRT_VERSION_1_0=0x100;
	const uint16_t Crt::CRT_VERSION_1_1=0x101;


	Crt::Crt(uint8_t *_mainBuffer,uint32_t _buflen):BaseFormat(_mainBuffer, _buflen) {
		// TODO Auto-generated constructor stub

	}
	bool Crt::parse(Sys_Result *res)
	{
		// Init all banks to 0
		for(int k=0;k<MAX_BANK;k++)
		{
			banks[k].loBuffer=0;
			banks[k].hiBuffer=0;
		}
		uint32_t len=readBuf((uint8_t *)&header, sizeof(header),res);
		if(!res->isOk())
			return false;
		if (len != sizeof(CRT_HEADER) ||
			memcmp(CRT_SIGNATURE, header.signature, sizeof(header.signature)) != 0)
		{
			res->setError(getModuleName(),Crt::RES_INVALID_SIGNATURE);
			return false;
		}
		header.header_length = __REV(header.header_length);
		header.version = __REV16(header.version);
		header.cartridge_type = (CRT_TYPE)__REV16(header.cartridge_type);

		if (header.header_length != sizeof(CRT_HEADER))
		{
	        if (header.header_length != 0x20)
	        {
	        	res->setError(getModuleName(),Crt::RES_INVALID_HEADER);
	        	return false;
	        }

		}

		if (header.version < CRT_VERSION_1_0 || header.version > CRT_VERSION_1_1)
	    {
		        res->setError(getModuleName(),Crt::RES_INVALID_HEADER);
		        return false;
		}

		nBanks=0;
		int chipLength=0;
		uint8_t *buf=mainBuffer;
		mainBuffer[0]=0;
		int lastBank=0;
		while (!file->isEof() && res->isOk())
		{
			lastBank=parseChip(res,buf);
			if(lastBank>=0)
				buf+=banks[lastBank].header.image_size;
		}
		file->close();
		return res->isOk();

	}


	int Crt::parseChip(::Sys::Result *res,uint8_t *buf)
	{
		CRT_CHIP_HEADER header;
		uint32_t len=readBuf((uint8_t *)&header, sizeof(CRT_CHIP_HEADER),res);
		if(!res->isOk())
		{
			return false;
		}
		if (len != sizeof(CRT_CHIP_HEADER) ||
		memcmp(CRT_CHIP_SIGNATURE, header.signature, sizeof(header.signature)) != 0)
		{
			return false;
		}

		header.packet_length = __REV(header.packet_length);
		header.chip_type = __REV16(header.chip_type);
		header.bank = __REV16(header.bank);
		header.start_address = __REV16(header.start_address);
		header.image_size = __REV16(header.image_size);
		// From KFF: Note: packet length > image size + chip header in "Expert Cartridge" CRT file
		if (header.packet_length < (header.image_size + sizeof(CRT_CHIP_HEADER)))
		{
			res->setError(getModuleName(),Crt::RES_CHIP_HEADER_ERROR);
			return -1;
		}
	 	// Right now, no more than MAX_BANK banks will be allowed.
	 	if(header.bank>=MAX_BANK)
	 	{
	 		res->setError(getModuleName(),Crt::RES_TOO_MANY_BANKS);
	 		return -1;
	 	}

	 	memcpy((void *)&banks[header.bank].header,&header,sizeof(CRT_CHIP_HEADER));

	 	if(header.start_address==0x8000)
	 		banks[header.bank].loBuffer=buf;
	 	else{
	 	//  start_address== 0xA000 || 0xE000
	 		banks[header.bank].hiBuffer=buf;
	 	}
	 	// If it's a 16Kb chip, the high buffer pointer is set too.
	 	if(header.image_size==0x4000)
	 		 banks[header.bank].hiBuffer=buf+0x2000;
	 	if(readBuf(buf, header.image_size,res)!=header.image_size)
	 	{
	 		res->setError(getModuleName(),Crt::RES_INVALID_BANK);
	 		return -1;
	 	}

	 return header.bank;
}




Crt::~Crt() {
	// TODO Auto-generated destructor stub
}

}
