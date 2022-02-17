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

typedef struct _reudump
{
	uint8_t type;
	uint32_t REUAddr;
	uint16_t c64Addr;
	uint16_t tlength;
	uint32_t sum1;
	uint32_t sum2;
} reudump;
reudump dump[]={
		{0,458752,1209,8,816,0},
		{0,393216,1209,8,815,0},
		{0,327680,1209,8,814,0},
		{0,262144,1209,8,813,0},
		{0,196608,1209,8,812,0},
		{0,131072,1209,8,811,0},
		{0,65536,1209,8,810,0},
		{0,0,1209,8,809,0},
		{0,458752,1209,8,808,0}, //
		{0,393216,1209,8,807,0},
		{0,327680,1209,8,806,0},
		{0,262144,1209,8,805,0},
		{0,196608,1209,8,804,0},
		{0,131072,1209,8,803,0},
		{0,65536,1209,8,802,0},
		{0,0,1209,8,801,0},
		{0,458752,1209,8,800,0},
		{0,393216,1209,8,799,0},
		{0,327680,1209,8,798,0},
		{0,262144,1209,8,797,0},
		{0,196608,1209,8,796,0},
		{0,131072,1209,8,795,0},
		{0,65536,1209,8,794,0},
		{0,0,1209,8,793,0},
		{0,458752,1209,8,792,0},
		{0,393216,1209,8,791,0},
		{0,327680,1209,8,790,0},
		{0,262144,1209,8,789,0},
		{0,196608,1209,8,788,0},
		{0,131072,1209,8,787,0},
		{0,65536,1209,8,786,0},
		{0,0,1209,8,785,0},
		{0,458752,1209,8,784,0},
		{0,393216,1209,8,783,0},
		{0,327680,1209,8,782,0},
		{0,262144,1209,8,781,0},
		{0,196608,1209,8,780,0},
		{0,131072,1209,8,779,0},
		{0,65536,1209,8,778,0},
		{0,0,1209,8,777,0},
		{0,458752,1209,8,776,0},
		{0,393216,1209,8,775,0},
		{0,327680,1209,8,774,0},
		{0,262144,1209,8,773,0},
		{0,196608,1209,8,772,0},
		{0,131072,1209,8,771,0},
		{0,65536,1209,8,770,0},
		{0,0,1209,8,769,0},
		{0,458752,1209,8,768,0},
		{0,393216,1209,8,767,0},
		{0,327680,1209,8,766,0},
		{0,262144,1209,8,765,0},
		{0,196608,1209,8,764,0},
		{0,131072,1209,8,763,0},
		{0,65536,1209,8,762,0},
		{0,0,1209,8,761,0},
		{0,458752,1209,8,760,0},
		{0,393216,1209,8,759,0},
		{0,327680,1209,8,758,0},
		{0,262144,1209,8,757,0},
		{0,196608,1209,8,756,0},
		{0,131072,1209,8,755,0},
		{0,65536,1209,8,754,0},
		{0,0,1209,8,753,0},
		{0,458752,1209,8,752,0},
		{0,393216,1209,8,751,0},
		{0,327680,1209,8,750,0},
		{0,262144,1209,8,749,0},
		{0,196608,1209,8,748,0},
		{0,131072,1209,8,747,0},
		{0,65536,1209,8,746,0},
		{0,0,1209,8,745,0},
		{0,458752,1209,8,744,0},
		{0,393216,1209,8,743,0},
		{0,327680,1209,8,742,0},
		{0,262144,1209,8,741,0},
		{0,196608,1209,8,740,0},
		{0,131072,1209,8,739,0},
		{0,65536,1209,8,738,0},
		{0,0,1209,8,737,0},
		{0,458752,1209,8,736,0},
		{0,393216,1209,8,735,0},
		{0,327680,1209,8,734,0},
		{0,262144,1209,8,733,0},
		{0,196608,1209,8,732,0},
		{0,131072,1209,8,731,0},
		{0,65536,1209,8,730,0},
		{0,0,1209,8,729,0},
		{0,458752,1209,8,728,0},
		{0,393216,1209,8,727,0},
		{0,327680,1209,8,726,0},
		{0,262144,1209,8,725,0},
		{0,196608,1209,8,724,0},
		{0,131072,1209,8,723,0},
		{0,65536,1209,8,722,0},
		{0,0,1209,8,721,0},
		{0,458752,1209,8,720,0},
		{0,393216,1209,8,719,0},
		{0,327680,1209,8,718,0},
		{0,262144,1209,8,717,0},
		{0,196608,1209,8,716,0},
		{0,131072,1209,8,715,0},
		{0,65536,1209,8,714,0},
		{0,0,1209,8,713,0},
		{0,458752,1209,8,712,0},
		{0,393216,1209,8,711,0},
		{0,327680,1209,8,710,0},
		{0,262144,1209,8,709,0},
		{0,196608,1209,8,708,0},
		{0,131072,1209,8,707,0},
		{0,65536,1209,8,706,0},
		{0,0,1209,8,705,0},
		{0,458752,1209,8,704,0},
		{0,393216,1209,8,703,0},
		{0,327680,1209,8,702,0},
		{0,262144,1209,8,701,0},
		{0,196608,1209,8,700,0},
		{0,131072,1209,8,699,0},
		{0,65536,1209,8,698,0},
		{0,0,1209,8,697,0},
		{0,458752,1209,8,696,0},
		{0,393216,1209,8,695,0},
		{0,327680,1209,8,694,0},
		{0,262144,1209,8,693,0},
		{0,196608,1209,8,692,0},
		{0,131072,1209,8,691,0},
		{0,65536,1209,8,690,0},
		{0,0,1209,8,689,0},
		{0,458752,1209,8,688,0},
		{0,393216,1209,8,687,0},
		{0,327680,1209,8,686,0},
		{0,262144,1209,8,685,0},
		{0,196608,1209,8,684,0},
		{0,131072,1209,8,683,0},
		{0,65536,1209,8,682,0},
		{0,0,1209,8,681,0},
		{0,458752,1209,8,680,0},
		{0,393216,1209,8,679,0},
		{0,327680,1209,8,678,0},
		{0,262144,1209,8,677,0},
		{0,196608,1209,8,676,0},
		{0,131072,1209,8,675,0},
		{0,65536,1209,8,674,0},
		{0,0,1209,8,673,0},
		{0,458752,1209,8,672,0},
		{0,393216,1209,8,671,0},
		{0,327680,1209,8,670,0},
		{0,262144,1209,8,669,0},
		{0,196608,1209,8,668,0},
		{0,131072,1209,8,667,0},
		{0,65536,1209,8,666,0},
		{0,0,1209,8,665,0},
		{0,458752,1209,8,664,0},
		{0,393216,1209,8,663,0},
		{0,327680,1209,8,662,0},
		{0,262144,1209,8,661,0},
		{0,196608,1209,8,660,0},
		{0,131072,1209,8,659,0},
		{0,65536,1209,8,658,0},
		{0,0,1209,8,657,0},
		{0,458752,1209,8,656,0},
		{0,393216,1209,8,655,0},
		{0,327680,1209,8,654,0},
		{0,262144,1209,8,653,0},
		{0,196608,1209,8,652,0},
		{0,131072,1209,8,651,0},
		{0,65536,1209,8,650,0},
		{0,0,1209,8,649,0},
		{0,458752,1209,8,648,0},
		{0,393216,1209,8,647,0},
		{0,327680,1209,8,646,0},
		{0,262144,1209,8,645,0},
		{0,196608,1209,8,644,0},
		{0,131072,1209,8,643,0},
		{0,65536,1209,8,642,0},
		{0,0,1209,8,641,0},
		{0,458752,1209,8,640,0},
		{0,393216,1209,8,639,0},
		{0,327680,1209,8,638,0},
		{0,262144,1209,8,637,0},
		{0,196608,1209,8,636,0},
		{0,131072,1209,8,635,0},
		{0,65536,1209,8,634,0},
		{0,0,1209,8,633,0},
		{0,458752,1209,8,632,0},
		{0,393216,1209,8,631,0},
		{0,327680,1209,8,630,0},
		{0,262144,1209,8,629,0},
		{0,196608,1209,8,628,0},
		{0,131072,1209,8,627,0},
		{0,65536,1209,8,626,0},
		{0,0,1209,8,625,0},
		{0,458752,1209,8,624,0},
		{0,393216,1209,8,623,0},
		{0,327680,1209,8,622,0},
		{0,262144,1209,8,621,0},
		{0,196608,1209,8,620,0},
		{0,131072,1209,8,619,0},
		{0,65536,1209,8,618,0},
		{0,0,1209,8,617,0},
		{0,458752,1209,8,616,0},
		{0,393216,1209,8,615,0},
		{0,327680,1209,8,614,0},
		{0,262144,1209,8,613,0},
		{0,196608,1209,8,612,0},
		{0,131072,1209,8,611,0},
		{0,65536,1209,8,610,0},
		{0,0,1209,8,609,0},
		{0,458752,1209,8,608,0},
		{0,393216,1209,8,607,0},
		{0,327680,1209,8,606,0},
		{0,262144,1209,8,605,0},
		{0,196608,1209,8,604,0},
		{0,131072,1209,8,603,0},
		{0,65536,1209,8,602,0},
		{0,0,1209,8,601,0},
		{0,458752,1209,8,600,0},
		{0,393216,1209,8,599,0},
		{0,327680,1209,8,598,0},
		{0,262144,1209,8,597,0},
		{0,196608,1209,8,596,0},
		{0,131072,1209,8,595,0},
		{0,65536,1209,8,594,0},
		{0,0,1209,8,593,0},
		{0,458752,1209,8,592,0},
		{0,393216,1209,8,591,0},
		{0,327680,1209,8,590,0},
		{0,262144,1209,8,589,0},
		{0,196608,1209,8,588,0},
		{0,131072,1209,8,587,0},
		{0,65536,1209,8,586,0},
		{0,0,1209,8,585,0},
		{0,458752,1209,8,584,0},
		{0,393216,1209,8,583,0},
		{0,327680,1209,8,582,0},
		{0,262144,1209,8,581,0},
		{0,196608,1209,8,580,0},
		{0,131072,1209,8,579,0},
		{0,65536,1209,8,578,0},
		{0,0,1209,8,577,0},
		{0,458752,1209,8,576,0},
		{0,393216,1209,8,575,0},
		{0,327680,1209,8,574,0},
		{0,262144,1209,8,573,0},
		{0,196608,1209,8,572,0},
		{0,131072,1209,8,571,0},
		{0,65536,1209,8,570,0},
		{0,0,1209,8,569,0},
		{0,458752,1209,8,568,0},
		{0,393216,1209,8,567,0},
		{0,327680,1209,8,566,0},
		{0,262144,1209,8,565,0},
		{0,196608,1209,8,564,0},
		{0,131072,1209,8,563,0},
		{0,65536,1209,8,562,0},
		{0,0,1209,8,561,0},
		{1,0,1217,8,561,0},
		{0,0,1209,8,0,0},
		{1,65536,1217,8,562,0},
		{0,65536,1209,8,0,0},
		{1,131072,1217,8,563,0},
		{0,131072,1209,8,0,0},
		{1,196608,1217,8,564,0},
		{0,196608,1209,8,0,0},
		{1,262144,1217,8,565,0},
		{0,262144,1209,8,0,0},
		{1,327680,1217,8,566,0},
		{0,327680,1209,8,0,0},
		{1,393216,1217,8,567,0},
		{0,393216,1209,8,0,0},
		{1,458752,1217,8,568,0},
		{0,458752,1209,8,0,0},
		{1,0,1217,8,0,0},
		{0,29184,39936,512,67922,0},
		{1,29184,39936,512,67922,0},
		{0,196608,42496,9984,373526,0},
		{0,206592,42496,9984,384121,0},
		{0,216576,57408,384,23511,0},
		{0,216960,57408,384,23258,0},
		{0,217344,57408,384,23005,0},
		{0,217728,57408,384,22616,0},
		{0,218112,57408,384,22290,0},
		{0,218496,57408,384,21932,0},
		{0,218880,57408,384,21537,0},
		{0,219264,57408,384,21172,0},
		{0,219648,57408,384,20782,0},
		{0,220032,57408,384,20255,0},
		{0,220416,57408,384,19729,0},
		{0,220800,57408,384,19251,0},
		{0,221184,57408,384,18773,0},
		{0,221568,57408,384,18295,0},
		{0,221952,57408,384,17807,0},
		{0,222336,57408,384,17319,0},
		{0,222720,57408,384,16523,0},
		{0,223104,57408,384,15759,0},
		{0,223488,57408,384,14883,0},
		{0,223872,57408,384,14023,0},
		{0,224256,57408,384,13163,0},
		{0,224640,57408,384,12367,0},
		{0,225024,57408,384,11610,0},
		{0,225408,57408,384,11089,0},
		{0,225792,57408,384,10643,0},
		{0,226176,57408,384,10158,0},
		{0,226560,57408,384,9488,0},
		{0,226944,57408,384,9080,0},
		{0,227328,57408,384,8655,0},
		{0,227712,57408,384,8117,0},
		{0,228096,57408,384,7565,0},
		{0,228480,57408,384,6957,0},
		{0,228864,57408,384,6469,0},
		{0,229248,57408,384,5912,0},
		{0,229632,57408,384,5435,0},
		{0,230016,57408,384,4906,0},
		{0,230400,57408,384,4521,0},
		{0,230784,57408,384,4192,0},
		{0,231168,57408,384,3871,0},
		{0,231552,57408,384,3630,0},
		{0,231936,57408,384,3388,0},
		{0,232320,57408,384,2861,0},
		{0,232704,57408,384,2376,0},
		{0,233088,57408,384,1634,0},
		{0,233472,57408,384,1159,0},
		{0,233856,57408,384,770,0},
		{0,234240,57408,384,770,0},
		{0,234624,57408,384,770,0},
		{0,28672,51712,512,77952,0},
		{1,29184,39936,512,67922,0},
		{2,235008,57344,6144,201979,0},
		{2,55040,2,254,14626,0},
		{2,54784,788,32,5634,0},
		{2,55040,2,254,545,14626},
		{2,54784,788,32,1,5634},
		{0,241152,40960,3328,175426,0},
		{2,55040,2,254,14593,545},
		{2,54784,788,32,5634,1},
		{2,55040,2,254,655,14593},
		{2,54784,788,32,4,5634},
		{0,244480,40960,3328,103822,0},
		{2,55040,2,254,14827,655},
		{2,54784,788,32,5634,4},
		{2,55040,2,254,591,14827},
		{2,54784,788,32,0,5634},
		{0,247808,40960,3328,121454,0},
		{2,55040,2,254,14828,591},
		{2,54784,788,32,5634,0},
		{2,55040,2,254,594,14828},
		{2,54784,788,32,7,5634},
		{0,251136,40960,3328,137901,0},
		{2,55040,2,254,14829,594},
		{2,54784,788,32,5634,7},
		{2,55040,2,254,501,14829},
		{2,54784,788,32,5,5634},
		{0,254464,40960,3328,106931,0},
		{2,55040,2,254,14830,501},
		{2,54784,788,32,5634,5},
		{2,55040,2,254,463,14830},
		{2,54784,788,32,5,5634},
		{0,257792,40960,3328,95363,0},
		{2,55040,2,254,14832,463},
		{2,54784,788,32,5634,5},
		{2,55040,2,254,495,14832},
		{2,54784,788,32,0,5634},
		{0,18944,35584,1024,85424,0},
		{2,55040,2,254,14833,495},
		{2,54784,788,32,5634,0},
		{2,55040,2,254,492,14833},
		{2,54784,788,32,4,5634},
		{0,26368,35584,2304,229611,0},
		{2,55040,2,254,15089,492},
		{2,54784,788,32,5634,4},
		{2,55040,2,254,492,15089},
		{2,54784,788,32,2,5634},
		{0,19968,35584,2304,225499,0},
		{2,55040,2,254,14835,492},
		{2,54784,788,32,5634,2},
		{2,55040,2,254,492,14835},
		{2,54784,788,32,4,5634},
		{0,16640,35584,2304,251627,0},
		{2,55040,2,254,14836,492},
		{2,54784,788,32,5634,4},
		{2,55040,2,254,492,14836},
		{2,54784,788,32,2,5634},
		{0,14336,35584,2304,241250,0},
		{2,55040,2,254,14837,492},
		{2,54784,788,32,5634,2},
		{2,55040,2,254,492,14837},
		{2,54784,788,32,4,5634},
		{0,11008,35584,3328,375788,0},
		{2,55040,2,254,14838,492},
		{2,54784,788,32,5634,4},
		{2,55040,2,254,825,14838},
		{2,54784,788,32,42,5634},
		{0,55296,40960,4096,29816,0},
		{2,55040,2,254,14841,825},
		{2,54784,788,32,5634,42},
		{2,55040,2,254,471,14841},
		{2,54784,788,32,5,5634},
		{0,29696,40960,1024,55140,0},
		{2,55040,2,254,14840,471},
		{2,54784,788,32,5634,5},
		{2,55040,2,254,691,14840},
		{2,54784,788,32,15,5634},
		{0,512,40960,9984,942478,0},
		{2,55040,2,254,14758,691},
		{2,54784,788,32,5634,15},
		{2,55040,2,254,623,14758},
		{2,54784,788,32,8,5634},
		{0,59392,40960,2048,98740,0},
		{2,55040,2,254,14842,623},
		{2,54784,788,32,5634,8},
		{2,55040,2,254,714,14842},
		{2,54784,788,32,27,5634},
		{0,46080,40960,4096,194032,0},
		{2,55040,2,254,14843,714},
		{2,54784,788,32,5634,27},
		{2,55040,2,254,550,14843},
		{2,54784,788,32,15,5634},
		{0,30720,40960,4096,117590,0},
		{2,55040,2,254,14625,550},
		{2,54784,788,32,5634,15},
		{2,55040,2,254,465,14625},
		{2,54784,788,32,6,5634},
		{0,52480,40960,2304,232506,0},
		{2,55040,2,254,14643,465},
		{2,54784,788,32,5634,6},
		{2,55040,2,254,578,14643},
		{2,54784,788,32,6,5634},
		{0,50176,40960,2304,236626,0},
		{2,55040,2,254,14747,578},
		{2,54784,788,32,5634,6},
		{2,55040,2,254,581,14747},
		{2,54784,788,32,20,5634},
		{0,34816,40448,10752,967892,0},
		{2,235008,57344,6144,747995,201979},
		{2,55040,2,254,14981,581},
		{2,54784,788,32,5634,20},
		{1,34816,40448,8704,838189,0},
		{1,44544,55296,1024,8761,0},
		{1,43520,32768,1024,120942,0},
		{1,19968,35584,2304,225499,0}
};
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
							/*if(reg==13)
							{
								::Sys::Result res;
								::Port::Base::FatFsFile fil;
								fil.open("dump",Sys::CREATE_ALWAYS|::Sys::WRITE,&res);
								fil.write(buffer,bufLen,&res);
								fil.close();
							}*/
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

											//cnts[0][cntcnt]=DWT->CYCCNT;
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

											//cnts[1][cntcnt]=DWT->CYCCNT;
											// Hopefully, data is now available
										//	if(!isCompare)
										//	{
												buffer[temp]=byte;
												subBuff2[subidx]=byte;
												subidx++;
												if(subidx==1024)
													subidx=0;
										//	}
										//	else
										//		byte=(buffer[(*reuBaseAddressReg)]==byte?1:0);
											// Update the reuBaseAddress too.
											// According to https://codebase64.org/doku.php?id=base:reu_registers#introduction
											// after the command is finished, addresses in the registers point to the NEXT
											// address.So first addresses are incremented, then the exit condition is checked.
											//subidx++;
											//if(subidx==200)
											//	subidx=0;
											//cnts[2][cntcnt]=DWT->CYCCNT;


											// Now, the checks
											sum+=byte;
											if((*transferLengthReg)==TF_END) // || (isCompare && !byte))
											{

												(*transferLengthReg)=1;
											/*	if((dump[idx2].type!=0 ||
												dump[idx2].REUAddr!=REUAddrBackup ||
												dump[idx2].c64Addr!=c64AddrBackup ||
												dump[idx2].tlength!=transferSizeBackup ||
												sum != dump[idx2].sum1) && idx2!=273
												)
												{
													__asm__("BKPT");
												}
												idx2++;*/
												CRT_SETDMAASINPUT;
												CRT_SETRWASINPUT;
												/*if(isCompare)
													return byte;*/
												break;
											}

											(*transferLengthReg)--;

											//cntcnt++;
											CRT_WAITFORCLOCKEND;
											//cnts[3][cntcnt]=DWT->CYCCNT;
										}
										//cntcnt=0;
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
