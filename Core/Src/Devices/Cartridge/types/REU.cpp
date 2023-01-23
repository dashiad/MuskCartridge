/*
 * REU.cpp
 *
 *  Created on: 22 gen 2022
 *      Author: Jose
 */

#include <Devices/Cartridge/types/REU.h>
#include "Port/MCU.h"
#include <string.h>
#include "Port/Base/FatFsFile.h"
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
	*(reuBaseAddressReg)=458752;
	*(transferLengthReg)=1;
	c64AddrBackup=*(c64BaseAddressReg);
	REUAddrBackup=*(reuBaseAddressReg);
	transferSizeBackup=*(transferLengthReg);
	GPIOE->OSPEEDR=0xAAAAAAAA;
	*((volatile uint16_t *)&GPIOA->OSPEEDR)=0xAAAA;
	*((volatile uint16_t *)&GPIOD->OSPEEDR)=0xAAAA;
	idx=0;
	reuAddrStep=1;
	c64AddrStep=1;
	for(int i=0;i<700;i++)
	{
		buf[458752+i]=i%20;
	}





}
void REU::init()
{
	CRT_SETEXROMHI;
	CRT_SETGAMEHI;
	CRT_SETRWASINPUT;
	CRT_SETDMAASINPUT;
	CRT_SETRWLO;
	CRT_SETDMALO;
	//CRT_SETDMAHI;
	//CRT_SETDMAASOUTPUT;



}
void REU::run()
{

	uint8_t data;
	uint32_t addr;
	uint32_t control;
	uint8_t reg;
	uint8_t pendingCommand=0;
	uint8_t isWriting;
	uint8_t isIo2;
	uint8_t mask;
	int baLeft=3;
	int flag=0;
	uint8_t byte;
	int sum=0;
	int cnts[6][20];
	int cntcnt=0;
	int subidx=0;
	uint8_t subBuff[200];
	uint8_t subBuff2[1024];
	bool isCompare;
	int temp;
	idx2=0;



	while (1)
	{
		CRT_WAITFORCRTPHY2HIGH;
		control=CRT_READCONTROL;
		addr=CRT_READADDR;

		isWriting = !CRT_GET_RW(control);
		isIo2=!CRT_GET_IO2(control);
		/*
		 *   If IO2 is not set, the only thing to watch out, is
		 *   a write into 0xFF00,to run a pending command.
		 */
		if(!isIo2)
		{
			if(addr==0xFF00 && pendingCommand)
			{
				//runCommand(baLeft);
				CRT_REU_EXECUTE
				pendingCommand=0;
			}
			// Exit here, to avoid an "else"
			CRT_WAITFORCLOCKEND;
			continue;
		}
		reg=addr & 0xFF;
		// As the baseREUAddress is stored as a 32 bit int, but the REU uses just 24,
		// registers above $DF07 are 1 byte higher in the registers array.
		if(reg>=7)
			reg++;
		if(!isWriting)
		{
						/*
						 *
						 * 		Read Operation
						 */
						if(reg>12)
						{
							// According to https://codebase64.org/doku.php?id=base:reu_registers#introduction,
							// all the other registers return 0xFF
							CRT_OUTPUT_BYTE(0xFF);
							CRT_WAITFORCLOCKEND;
							continue;
						}

						if(reg==6)
						{
							CRT_OUTPUT_BYTE(registers[reg] | 0xF8);
						}
						else
						{
							CRT_OUTPUT_BYTE(registers[reg]);
							if(!reg)
							{
								// If it's register 0, we clear interrupt(?) and fail.
								registers[0]=0x10;
							}
						}
						//
						CRT_WAITFORCLOCKEND;
						continue;

		}
		CRT_WAITHOLDWRITE;
		data=CRT_READDATA;


				if(reg==1)
				{
					(*commandReg)=data;
					if(data & CRT_REU_COMM_EXECUTE)
					{

						if((*commandReg) & CRT_REU_COMM_IMMEDIATE)
						{
							(*statusReg)=0x10;

							switch((*commandReg) & CRT_REU_COMM_TRANSFER_TYPE_MASK)
								{
								case 0:{
									isCompare=false;
									/*
									 *   It'd be great to have the following code in different
									 *   functions...But that is costing > 70 cycles which we cant afford
									 *   to lose..
									 */
									/**************************************************************
									 *
									 *
									 *     TRANSFER TO REU
									 *
									 */

										CRT_SETDMAASOUTPUT;
										CRT_SETDATAASINPUT;
										CRT_WAITFORCLOCKEND;
										sum=0;
										subidx=0;
										DWT->CYCCNT=0;

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

											(*c64BaseAddressReg)+=c64AddrStep;
											if((*c64BaseAddressReg)>=(64*1024))
												(*c64BaseAddressReg)=0;
											CRT_WAITFORCRTWRITEREADY;
											CRT_SETADDRASOUTPUT;
											temp=(*reuBaseAddressReg);
											(*reuBaseAddressReg)+=reuAddrStep;
											if(*reuBaseAddressReg >= bufLen)
												(*reuBaseAddressReg)=0;

											//CRT_WAITHOLDWRITE;
											while(DWT->CYCCNT<360);

											byte=CRT_GET_DATA;

											CRT_SETADDRASINPUT;

											buffer[temp]=byte;
											if((*transferLengthReg)==TF_END) // || (isCompare && !byte))
											{

												(*transferLengthReg)=1;
												CRT_SETDMAASINPUT;
												CRT_SETRWASINPUT;
												break;
											}

											(*transferLengthReg)--;


											CRT_WAITFORCLOCKEND;
										}
									/*************************************************************
									 *
									 *    END TRANSFER TO REU
									 *
									 */
								(*statusReg)|=(CRT_REU_STATUS_END_OF_BLOCK|CRT_REU_STATUS_INTERRUPT_PEDING);

								}break;
								case 1:{
									runTransferToC64(baLeft);

								(*statusReg)|=(CRT_REU_STATUS_END_OF_BLOCK|CRT_REU_STATUS_INTERRUPT_PEDING);
								}break;
								case 2:{
									runSwap(baLeft);
								(*statusReg)|=(CRT_REU_STATUS_END_OF_BLOCK|CRT_REU_STATUS_INTERRUPT_PEDING);
								}break;
								case 3:{
									if(runTransferToREU(baLeft,1))
										(*statusReg)|=(CRT_REU_STATUS_END_OF_BLOCK|CRT_REU_STATUS_INTERRUPT_PEDING);
									else
										(*statusReg)|=CRT_REU_STATUS_FAULT;
								}break;
								default:{
									idx=0;
								}

								}

							if((*commandReg) & CRT_REU_COMM_LOAD)
							{

								*(c64BaseAddressReg)=c64AddrBackup;
								*(reuBaseAddressReg)=REUAddrBackup;
								*(transferLengthReg)=transferSizeBackup;
							}
							CRT_SETDATAASINPUT;

							//(*commandReg)&=0x20;
						}
						else
						{
							pendingCommand=1;
						}
						/**(c64BaseAddressReg)=1024;
							*(reuBaseAddressReg)=458752;
							*(transferLengthReg)=700;*/
						CRT_WAITFORCLOCKEND;
						continue;

					}

				}
		/*
		 *
		 *   Write operation
		 *
		 */
		if(reg>1 && reg<11)
		{
			if(reg==6)
				data&=0x07;
			registers[reg]=data;
			if(reg==11)
			{
				if((*addressControlReg) & CRT_ADDR_FIX_REU_ADDR_MASK)
					reuAddrStep=0;
				else
					reuAddrStep=1;
				if((*addressControlReg) & CRT_ADDR_FIX_C64_ADDR_MASK)
					c64AddrStep=0;
				else
					c64AddrStep=1;
			}
			// Refresh the backup copies.
			// This is done here because i get the feeling we have more spare time here
			// than when an operation is initiated.

			c64AddrBackup=(*c64BaseAddressReg);
			REUAddrBackup=(*reuBaseAddressReg);
			transferSizeBackup=(*transferLengthReg);
		}

		CRT_WAITFORCLOCKEND;
	}
}

int REU::runTransferToREU(int baLeft,int isCompare)

{
	// First, wait for end of PHI2 high.
	// Note that always at least 1 byte will be transferred.
	// If transfer length is 0, that means 64Kb
	// So, the order of operations is: transfer, check for 1 byte left, and then decrement.

	int control;
	int sum=0;
	int subidx=0;
	uint8_t subBuff[200];
	int onEntry=DWT->CYCCNT;
	CRT_WAITFORCLOCKEND
	CRT_SETDMAASOUTPUT;



	int idx=0;
	volatile uint8_t byte;
	while(1)
	{

		CRT_WAITFORPHI2LOW;
		subBuff[subidx]=DWT->CYCCNT;
					subidx++;
					if(subidx==200)
						subidx=0;
		CRT_SETDATAASINPUT;
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

		CRT_WAITFORCRTWRITEREADY;
		CRT_SETADDRASOUTPUT;
		//DEBUG1_ON;
		// While data stabilizes, increment C64Addr, and write it back to the register.
		(*c64BaseAddressReg)+=c64AddrStep;
		if((*c64BaseAddressReg)>=(64*1024))
			(*c64BaseAddressReg)=0;

		CRT_WAITHOLDWRITE;
		//DEBUG1_OFF;
		byte=CRT_GET_DATA;

		CRT_SETADDRASINPUT;
		// Hopefully, data is now available
		if(!isCompare)
		{
			buffer[(*reuBaseAddressReg)]=byte;
			/*subBuff[subidx]=byte;
			subidx++;
			if(subidx==200)
				subidx=0;*/
		}
		else
			byte=(buffer[(*reuBaseAddressReg)]==byte?1:0);
		// Update the reuBaseAddress too.
		// According to https://codebase64.org/doku.php?id=base:reu_registers#introduction
		// after the command is finished, addresses in the registers point to the NEXT
		// address.So first addresses are incremented, then the exit condition is checked.
		(*reuBaseAddressReg)+=reuAddrStep;
		if(*reuBaseAddressReg >= bufLen)
			(*reuBaseAddressReg)=0;
		// Now, the checks
		sum+=byte;
		if((*transferLengthReg)==TF_END || (isCompare && !byte))
		{
			if((*transferLengthReg)==TF_END)
				(*transferLengthReg)=1;
			/*if(dump[idx2].type!=0 ||
			dump[idx2].REUAddr!=REUAddrBackup ||
			dump[idx2].c64Addr!=c64AddrBackup ||
			dump[idx2].tlength!=transferSizeBackup ||
			sum != dump[idx2].sum1
			)
			{
				__asm__("BKPT");
			}
			idx2++;*/
			CRT_SETDMAASINPUT;
			CRT_SETRWASINPUT;
			if(isCompare)
				return byte;
			return 1;
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
	//CRT_WAITFORCLOCKEND
	int sum=0;
	CRT_SETDMAASOUTPUT;
	CRT_WAITFORCLOCKEND;
	int control;
	//DWT->CYCCNT=TIM1->CNT*2;

	while(1)
	{

		CRT_REU_PREWRITE_CYCLE
		//Precharge the write address in the data port, while the
		// direction port is in READ
		CRT_SETADDR((*c64BaseAddressReg));
		CRT_SETDATA(buffer[(*reuBaseAddressReg)]);
		sum+=buffer[(*reuBaseAddressReg)];

		//CRT_REU_PREPARE_OUTPUT;
		CRT_WAITFORCRTWRITEREADY;
		//DEBUG1_ON;
		CRT_SETRWASOUTPUT;
		CRT_SETADDRASOUTPUT;
		CRT_SETDATAASOUTPUT;

		// While data stabilizes, increment C64Addr, and write it back to the register.
		(*c64BaseAddressReg)+=c64AddrStep;
		if((*c64BaseAddressReg)>=(64*1024))
			(*c64BaseAddressReg)=0;
		(*reuBaseAddressReg)+=reuAddrStep;
		if((*reuBaseAddressReg)>=bufLen)
			(*reuBaseAddressReg)=0;

		CRT_WAITHOLDWRITE;
		CRT_SETRWASINPUT;
		CRT_SETDATAASINPUT;
		CRT_SETADDRASINPUT;
		if((*transferLengthReg)==TF_END)
		{
			/*if((dump[idx2].type!=1 ||
				dump[idx2].REUAddr!=REUAddrBackup ||
				dump[idx2].c64Addr!=c64AddrBackup ||
				dump[idx2].tlength!=transferSizeBackup ||
				sum != dump[idx2].sum1) && idx2!=274
			)
			{
				__asm__("BKPT");
			}
			idx2++;*/
			CRT_SETDMAASINPUT;
			return;
		}
		(*transferLengthReg)--;

		//DEBUG1_OFF

		// Update the reuBaseAddress too.
		// According to https://codebase64.org/doku.php?id=base:reu_registers#introduction
		// after the command is finished, addresses in the registers point to the NEXT
		// address.So first addresses are incremented, then the exit condition is checked.
		// Now, the checks
		CRT_WAITFORCLOCKEND;
	}

}
void REU::runSwap(int baLeft){
	// First, wait for end of PHI2 high.
		// Note that always at least 1 byte will be transferred.
		// If transfer length is 0, that means 64Kb
		// So, the order of operations is: transfer, check for 1 byte left, and then decrement.
		int sum1=0,sum2=0;
		int control;
		CRT_SETDMAASOUTPUT;
		CRT_SETDATAASINPUT;
		CRT_WAITFORCLOCKEND
		int idx=0;
		volatile uint8_t byte;

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
				if(idx==1)
					CRT_SETDATA(buffer[(*reuBaseAddressReg)]);
			}
			CRT_WAITFORCRTWRITEREADY;
			if(idx==0)
			{
				CRT_SETADDRASOUTPUT;
				//CRT_WAITHOLDWRITE;
				while(DWT->CYCCNT < 360 );
				byte=CRT_GET_DATA;
				sum1+=byte;
				CRT_SETADDRASINPUT;
				idx=1;
			}
			else
			{
				CRT_REU_PREPARE_OUTPUT;
				buffer[(*reuBaseAddressReg)]=byte;
				sum2+=byte;
				// While data stabilizes, increment C64Addr, and write it back to the register.
				CRT_WAITHOLDWRITE;
				CRT_SETRWASINPUT;
				CRT_SETDATAASINPUT;
				CRT_SETADDRASINPUT;
				if((*transferLengthReg)==TF_END)
				{
				/*	if(dump[idx2].type!=0 ||
									dump[idx2].REUAddr!=REUAddrBackup ||
									dump[idx2].c64Addr!=c64AddrBackup ||
									dump[idx2].tlength!=transferSizeBackup ||
									sum1 != dump[idx2].sum1 ||
									sum2 != dump[idx2].sum2
								)
								{
									__asm__("BKPT");
								}*/

					CRT_SETDMAASINPUT;
					return;
				}
				//(*transferLengthReg)--;
				idx=0;
				(*c64BaseAddressReg)+=c64AddrStep;
				if((*c64BaseAddressReg)>=(64*1024))
					(*c64BaseAddressReg)=0;
				(*reuBaseAddressReg)+=reuAddrStep;
				if((*reuBaseAddressReg)>=bufLen)
					(*reuBaseAddressReg)=0;

				if((*transferLengthReg)==TF_END)
				{
					(*transferLengthReg)=1;
					CRT_SETDMAASINPUT;
					return;
				}
				(*transferLengthReg)--;
			}
			CRT_WAITFORCLOCKEND;
		}
}
REU::~REU() {
	// TODO Auto-generated destructor stub
}

} /* namespace types */
