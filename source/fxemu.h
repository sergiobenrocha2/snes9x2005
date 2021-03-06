#include "../copyright"

#ifndef _FXEMU_H_
#define _FXEMU_H_ 1

#include "snes9x.h"

/* The FxInfo_s structure, the link between the FxEmulator and the Snes Emulator */
struct FxInit_s
{
   uint32_t  vFlags;
   uint8_t*  pvRegisters; /* 768 bytes located in the memory at address 0x3000 */
   uint32_t  nRamBanks;   /* Number of 64kb-banks in GSU-RAM/BackupRAM (banks 0x70-0x73) */
   uint8_t*  pvRam;       /* Pointer to GSU-RAM */
   uint32_t  nRomBanks;   /* Number of 32kb-banks in Cart-ROM */
   uint8_t*  pvRom;       /* Pointer to Cart-ROM */
};

/* Reset the FxChip */
extern void FxReset(struct FxInit_s* psFxInfo);

/* Execute until the next stop instruction */
extern int32_t FxEmulate(uint32_t nInstructions);

/* Write access to the cache */
extern void FxCacheWriteAccess(uint16_t vAddress);
extern void FxFlushCache();   /* Callled when the G flag in SFR is set to zero */

/* Errors */
extern int32_t FxGetErrorCode();
extern int32_t FxGetIllegalAddress();

/* Access to internal registers */
extern uint32_t FxGetColorRegister();
extern uint32_t FxGetPlotOptionRegister();
extern uint32_t FxGetSourceRegisterIndex();
extern uint32_t FxGetDestinationRegisterIndex();

/* Get the byte currently in the pipe */
extern uint8_t FxPipe();

/* SCBR write seen.  We need to update our cached screen pointers */
extern void fx_dirtySCBR();

/* Update RamBankReg and RAM Bank pointer */
extern void fx_updateRamBank(uint8_t Byte);

/* Option flags */
#define FX_FLAG_ADDRESS_CHECKING 0x01
#define FX_FLAG_ROM_BUFFER    0x02

/* Return codes from FxEmulate(), FxStepInto() or FxStepOver() */
#define FX_BREAKPOINT            -1
#define FX_ERROR_ILLEGAL_ADDRESS -2

/* Return the number of bytes in an opcode */
#define OPCODE_BYTES(op) ((((op) >= 0x05 && (op) <= 0xf) || ((op) >= 0xa0 && (op) <= 0xaf)) ? 2 : (((op) >= 0xf0) ? 3 : 1))

extern void fx_computeScreenPointers();

#endif
