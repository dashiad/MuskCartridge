/*
 * REU.cpp
 *
 *  Created on: 22 gen 2022
 *      Author: Jose
 */

#include <Devices/Cartridge/types/REU.h>
#include "Port/MCU.h"
#include <string.h>
namespace Devices::Cartridge::types {

REU::REU(::Devices::Cartridge::CartridgeDevice *_cart,uint8_t *buf,int bufLen)
		: BaseDevice(_cart,buf,bufLen),
		  /* Initial values of registers, according to https://codebase64.org/doku.php?id=base:reu_registers */
		  /* Includes one extra byte for padding the 32bits integer for the reu address register. */
		 registers {0x10,0x10,0x00,0x00,0x00,0x00,0xF8,0x00,0xFF,0xFF,0x1F,0x3F}

{
	memset(buf,0,bufLen);
	statusReg=(uint8_t *)registers;
	commandReg=(uint8_t *)(registers+1);
	c64BaseAddressReg=(uint16_t *)(registers+2);
	reuBaseAddressReg=(uint32_t *)(registers+4);
	transferLengthReg=(uint16_t *)(registers+8);
	interruptReg=(uint8_t *)(registers+9);
	addressControlReg=(uint8_t *)(registers+10);
	*(c64BaseAddressReg)=1024;
	*(reuBaseAddressReg)=0;
	*(transferLengthReg)=1000;
	memset(bytesRead,0,1000);
}
void REU::init()
{
	CRT_SETEXROMHI;
	CRT_SETGAMEHI;



}
void REU::run()
{

	uint8_t data;
	uint8_t status=0;
	uint32_t addr;
	uint32_t control;
	uint8_t reg;
	uint8_t pendingCommand=0;
	uint8_t isWriting;
	int baLeft=3;

	while (1)
	{
		DWT->CYCCNT=TIM1->CNT*2;
		while(DWT->CYCCNT < 270 );
		control=CRT_READCONTROL;
		addr=CRT_READADDR;
		isWriting = !CRT_GET_RW(control);
		// Keeping track of VIC DMA Status
		//
		if(!(CRT_GET_BA(control)))
		{
			// VIC enters DMA.
			if(!baLeft)
				continue;
			baLeft--;
		}
		else
			baLeft=3;
		/*
		 *   If IO2 is not set, the only thing to watch out, is
		 *   a write into 0xFF00,to run a pending command.
		 */
		if(CRT_GET_IO2(control))
		{
			if(isWriting && addr==0xFF00 && pendingCommand)
			{
				runCommand(baLeft);
				pendingCommand=0;
			}
			// Exit here, to avoid an "else"
			CRT_WAITFORCLOCKEND;
			continue;
		}
		reg=addr & 0xFF;
		if(reg>=7)
			reg++;
		if(reg>12)
		{
			// According to https://codebase64.org/doku.php?id=base:reu_registers#introduction,
			// all the other registers return 0xFF
			CRT_OUTPUT_BYTE(0xFF);
			CRT_WAITFORCLOCKEND;
			continue;
		}
		/* Here, IO2 is active. First check if registers are being read or written */
		if(!isWriting)
		{
			/*
			 *
			 * 		Read Operation
			 */
			CRT_OUTPUT_BYTE(registers[reg]);
			if(!reg)
			{
				// If it's register 0, we clear interrupt(?) and fail.
				registers[0]^=(CRT_REU_STATUS_INTERRUPT_PEDING|CRT_REU_STATUS_FAULT);
			}
			//
			CRT_WAITFORCLOCKEND;
			continue;
		}
		/*
		 *
		 *   Write operation
		 *
		 */
		data=CRT_READDATA;
		reg=addr & 0xFF;
		if(reg==1)
		{
			(*commandReg)=data;
			if((*commandReg) & CRT_REU_COMM_IMMEDIATE)
			{
				runCommand(baLeft);
			}
			else
				pendingCommand=1;

		}
		if(reg>1 && reg<11)
			registers[reg]=data;

		CRT_WAITFORCLOCKEND;
	}
}

/*
void REU::runTransferToREU(int baLeft){
	int addr;
	int data;
	int control;
	CRT_SETDMAASOUTPUT;
	CRT_SETDMALO;
	CRT_SETDATAASINPUT;
	CRT_WAITFORCLOCKEND;
	uint8_t samples[10000];
	uint8_t delays[10000];
	int curDelay=0;
	int idx=0;
	addr=1024+40+5;
	while(idx<10000)
	{
		CRT_WAITFORPHI2LOW;
		control=CRT_READCONTROL;
		if(!CRT_GET_BA(control))
		{
			// VIC is performing  DMA..
			// Note that this can be read during the PHI2 low phase.
			CRT_WAITFORCLOCKEND;
			continue;
		}
		CRT_SETADDR(addr);
		CRT_WAITFORCRTPHY2HIGH;
		CRT_SETADDRASOUTPUT;
		while(DWT->CYCCNT<(260+curDelay));
		samples[idx]=CRT_GET_DATA;
		CRT_SETADDRASINPUT;
		delays[idx]=curDelay;
		curDelay=(curDelay+5)%200;
		if(curDelay==0)
			addr++;
		idx++;
		CRT_WAITFORCLOCKEND;
	}
	return;

}
*/

void REU::runTransferToREU(int baLeft)

{
	// First, wait for end of PHI2 high.
	// Note that always at least 1 byte will be transferred.
	// If transfer length is 0, that means 64Kb
	// So, the order of operations is: transfer, check for 1 byte left, and then decrement.

	int control;
	int addr;
	int data;
	CRT_SETDMAASOUTPUT;
	CRT_SETDMALO;
	CRT_SETDATAASINPUT;


	int idx=0;
	volatile uint8_t byte;
	CRT_WAITFORCLOCKEND;

	while(1)
	{
		CRT_WAITFORPHI2LOW;
		control=CRT_READCONTROL;
		if(!CRT_GET_BA(control))
		{
			// VIC is performing  DMA..
			// Note that this can be read during the PHI2 low phase.
			CRT_WAITFORCLOCKEND;
			continue;
		}
		if((*transferLengthReg) >=0)
		{
			 //Precharge the requested address in the data port, while the
			 // direction port is in READ

			CRT_SETADDR((*c64BaseAddressReg));
		}
		while(DWT->CYCCNT<190);


		CRT_SETADDRASOUTPUT;
		// While data stabilizes, increment C64Addr, and write it back to the register.
		(*c64BaseAddressReg)=((*c64BaseAddressReg)+1)%(64*1024);

		while(DWT->CYCCNT<390);
		byte=CRT_GET_DATA;

		CRT_SETADDRASINPUT;
		// Hopefully, data is now available


		buffer[(*reuBaseAddressReg)]=byte;
		bytesRead[idx]=byte;
		idx++;
		// Update the reuBaseAddress too.
		// According to https://codebase64.org/doku.php?id=base:reu_registers#introduction
		// after the command is finished, addresses in the registers point to the NEXT
		// address.So first addresses are incremented, then the exit condition is checked.
		(*reuBaseAddressReg)=((*reuBaseAddressReg)+1)%(bufLen);
		// Now, the checks
		if((*transferLengthReg)==1)
		{
			CRT_SETDMAHI;
			return;
		}
		(*transferLengthReg)--;

		CRT_WAITFORCLOCKEND;
	}

}

void REU::runTransferToC64(int baLeft)
{
	// First, wait for end of PHI2 high.
	// Note that always at least 1 byte will be transferred.
	// If transfer length is 0, that means 64Kb
	// So, the order of operations is: transfer, check for 1 byte left, and then decrement.

	int control;
	int addr;
	int data;
	CRT_SETDMAASOUTPUT;
	CRT_SETDMALO;
	CRT_SETDATAASINPUT;


	int idx=0;
	volatile uint8_t byte;
	int last;
	CRT_WAITFORCLOCKEND;

	while(1)
	{
		CRT_WAITFORPHI2LOW;
		last=DWT->CYCCNT;
		control=CRT_READCONTROL;
		if(!CRT_GET_BA(control))
		{
			// VIC is performing  DMA..
			// Note that this can be read during the PHI2 low phase.
			CRT_WAITFORCLOCKEND;
			continue;
		}
		if((*transferLengthReg) >=0)
		{
			 //Precharge the write address in the data port, while the
			 // direction port is in READ
			CRT_SETADDR((*c64BaseAddressReg));
			byte=buffer[(*reuBaseAddressReg)];
			CRT_SETDATA(byte);
			CRT_SETRWLO;
		}
		while(DWT->CYCCNT<190);
		CRT_SETADDRASOUTPUT;
		CRT_SETDATAASOUTPUT;
		CRT_SETRWASOUTPUT;

		// While data stabilizes, increment C64Addr, and write it back to the register.
		(*c64BaseAddressReg)=((*c64BaseAddressReg)+1)%(64*1024);
		while(DWT->CYCCNT<350);
		CRT_SETDATAASOUTOPUT;

		CRT_SETADDRASINPUT;
		// Hopefully, data is now available


		buffer[(*reuBaseAddressReg)]=byte;
		bytesRead[idx]=byte;
		idx++;
		// Update the reuBaseAddress too.
		// According to https://codebase64.org/doku.php?id=base:reu_registers#introduction
		// after the command is finished, addresses in the registers point to the NEXT
		// address.So first addresses are incremented, then the exit condition is checked.
		(*reuBaseAddressReg)=((*reuBaseAddressReg)+1)%(bufLen);
		// Now, the checks
		if((*transferLengthReg)==1)
		{
			CRT_SETDMAHI;
			return;
		}
		(*transferLengthReg)--;

		CRT_WAITFORCLOCKEND;
	}

}
void REU::runSwap(int baLeft){

}
void REU::runCompare(int baLeft){

}
REU::~REU() {
	// TODO Auto-generated destructor stub
}

} /* namespace types */
