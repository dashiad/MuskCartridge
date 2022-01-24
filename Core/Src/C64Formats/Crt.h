/*
 * Crt.h
 *
 *  Created on: 1 gen 2022
 *      Author: Jose
 */

#ifndef SRC_C64FORMATS_CRT_H_
#define SRC_C64FORMATS_CRT_H_

#include "BaseFormat.h"

using Sys_Result = Sys::Result;

namespace C64Formats {


// From https://vice-emu.sourceforge.io/vice_17.html
typedef enum {
    CRT_NORMAL_CARTRIDGE = 0x00,
    CRT_ACTION_REPLAY,
    CRT_KCS_POWER_CARTRIDGE,
    CRT_FINAL_CARTRIDGE_III,
    CRT_SIMONS_BASIC,
    CRT_OCEAN_TYPE_1,
    CRT_EXPERT_CARTRIDGE,
    CRT_FUN_PLAY_POWER_PLAY,
    CRT_SUPER_GAMES,
    CRT_ATOMIC_POWER,
    CRT_EPYX_FASTLOAD,
    CRT_WESTERMANN_LEARNING,
    CRT_REX_UTILITY,
    CRT_FINAL_CARTRIDGE_I,
    CRT_MAGIC_FORMEL,
    CRT_C64_GAME_SYSTEM_SYSTEM_3,
    CRT_WARP_SPEED,
    CRT_DINAMIC,
    CRT_ZAXXON_SUPER_ZAXXON,
    CRT_MAGIC_DESK_DOMARK_HES_AUSTRALIA,
    CRT_SUPER_SNAPSHOT_V5,
    CRT_COMAL_80,
    CRT_STRUCTURED_BASIC,
    CRT_ROSS,
    CRT_DELA_EP64,
    CRT_DELA_EP7X8,
    CRT_DELA_EP256,
    CRT_REX_EP256,
    CRT_MIKRO_ASSEMBLER,
    CRT_FINAL_CARTRIDGE_PLUS,
    CRT_ACTION_REPLAY_4,
    CRT_STARDOS,
    CRT_EASYFLASH,
    CRT_EASYFLASH_XBANK,
    CRT_CAPTURE,
    CRT_ACTION_REPLAY_3,
    CRT_RETRO_REPLAY,
    CRT_MMC64,
    CRT_MMC_REPLAY,
    CRT_IDE64,
    CRT_SUPER_SNAPSHOT_V4,
    CRT_IEEE_488,
    CRT_GAME_KILLER,
    CRT_PROPHET64,
    CRT_EXOS,
    CRT_FREEZE_FRAME,
    CRT_FREEZE_MACHINE,
    CRT_SNAPSHOT64,
    CRT_SUPER_EXPLODE_V5_0,
    CRT_MAGIC_VOICE,
    CRT_ACTION_REPLAY_2,
    CRT_MACH_5,
    CRT_DIASHOW_MAKER,
    CRT_PAGEFOX,
    CRT_KINGSOFT,
    CRT_SILVERROCK_128K_CARTRIDGE,
    CRT_FORMEL_64,
    CRT_RGCD,
    CRT_RR_NET_MK3,
    CRT_EASYCALC,
    CRT_GMOD2,
    CRT_MAX_BASIC,
    CRT_GMOD3,
    CRT_ZIPP_CODE_48,
    CRT_BLACKBOX_V8,
    CRT_BLACKBOX_V3,
    CRT_BLACKBOX_V4,
    CRT_REX_RAM_FLOPPY,
    CRT_BIS_PLUS,
    CRT_SD_BOX,
    CRT_MULTIMAX,
    CRT_BLACKBOX_V9,
    CRT_LT_KERNAL_HOST_ADAPTOR,
    CRT_RAMLINK,
    CRT_DREAN,
    // KFF specific extensions
    CRT_C128_NORMAL_CARTRIDGE = 0xFF00
} CRT_TYPE;

typedef enum {
    CRT_CHIP_ROM = 0x00,
    CRT_CHIP_RAM,
    CRT_CHIP_FLASH
} CRT_CHIP_TYPE;

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint8_t signature[16];
    uint32_t header_length;
    uint16_t version;
    CRT_TYPE cartridge_type;
    uint8_t exrom;
    uint8_t game;
    uint8_t hardware_revision;
    uint8_t reserved[5];
    uint8_t cartridge_name[32];
} CRT_HEADER;

typedef struct
{
    uint8_t signature[4];
    uint32_t packet_length;
    uint16_t chip_type;
    uint16_t bank;
    uint16_t start_address;
    uint16_t image_size;
} CRT_CHIP_HEADER;
typedef struct
{
	CRT_CHIP_HEADER header;
	uint8_t *loBuffer;
	uint8_t *hiBuffer;

}CRT_BANK;

#define MAX_BANK 128

class Crt: public BaseFormat {
public:
	static const char *RES_INVALID_SIGNATURE;
	static const char *RES_INVALID_HEADER;
	static const char *RES_INVALID_CRT_VERSION;
	static const char *RES_INVALID_CHIP_SIGNATURE;
	static const char *RES_CHIP_HEADER_ERROR;
	static const char *RES_UNKNOWN_CHIP_TYPE;
	static const char *RES_TOO_MANY_BANKS;
	static const char *RES_INVALID_BANK;

	static const char *CRT_SIGNATURE; //"C64 CARTRIDGE   "
	static const char *CRT_CHIP_SIGNATURE; //"CHIP"
	static const uint16_t CRT_VERSION_1_0; //0x100
	static const uint16_t CRT_VERSION_1_1; //0x101


	Crt(uint8_t *_mainBuffer,uint32_t _buflen);
	inline CRT_TYPE getType(){return header.cartridge_type;}
	inline uint8_t getHwRevision(){return header.hardware_revision;}
	inline uint8_t getExrom(){return header.exrom;}
	inline uint8_t getGame(){return header.game;}
	inline uint8_t getNBanks(){return nBanks;}
	inline CRT_BANK *getBankPointer(int bankNumber){return &banks[bankNumber];}
	inline virtual const char *getModuleName(){return "Crt";}
	bool parse(Sys_Result *res);
	virtual ~Crt();
protected:

private:
	int parseChip(::Sys::Result *res, uint8_t *buf);

	int nBanks=0;
	CRT_HEADER header;
	CRT_BANK banks[MAX_BANK];

};
}
#endif /* SRC_C64FORMATS_CRT_H_ */
