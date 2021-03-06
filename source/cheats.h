#include "../copyright"

#ifndef _CHEATS_H_
#define _CHEATS_H_

#ifdef WANT_CHEATS

#define MAX_SFCCHEAT_NAME 48
#define MAX_CHEATS_T 800

typedef struct
{
    uint32_t  address;
    uint8_t   byte;
    uint8_t   saved_byte;
    bool      enabled;
    bool      saved;
    char      name[MAX_SFCCHEAT_NAME];
} SCheat;

typedef struct
{
    SCheat   c [MAX_CHEATS_T];
    uint32_t num_cheats;
    uint8_t	 CWRAM [0x20000];
    uint8_t	 CSRAM [0x10000];
    uint8_t	 CIRAM [0x2000];
    uint8_t* RAM;
    uint8_t* FillRAM;
    uint8_t* SRAM;
    uint32_t WRAM_BITS [0x20000 >> 3];
    uint32_t SRAM_BITS [0x10000 >> 3];
    uint32_t IRAM_BITS [0x2000 >> 3];
} SCheatData;

typedef enum
{
    S9X_LESS_THAN, S9X_GREATER_THAN, S9X_LESS_THAN_OR_EQUAL,
    S9X_GREATER_THAN_OR_EQUAL, S9X_EQUAL, S9X_NOT_EQUAL
} S9xCheatComparisonType;

typedef enum
{
    S9X_8_BITS, S9X_16_BITS, S9X_24_BITS, S9X_32_BITS
} S9xCheatDataSize;

void S9xInitCheatData();

const char *S9xGameGenieToRaw(const char *code, uint32_t *address, uint8_t *byte);
const char *S9xProActionReplayToRaw(const char *code, uint32_t *address, uint8_t *byte);
const char *S9xGoldFingerToRaw(const char *code, uint32_t *address, bool *sram,	uint8_t *num_bytes, uint8_t bytes[3]);
void S9xApplyCheats();
void S9xApplyCheat(uint32_t which1);
void S9xRemoveCheats();
void S9xRemoveCheat(uint32_t which1);
void S9xEnableCheat(uint32_t which1);
void S9xDisableCheat(uint32_t which1);
void S9xDisableAllCheat();
void S9xAddCheat(bool enable, bool save_current_value, uint32_t address, uint8_t byte);
void S9xDeleteCheats();
void S9xDeleteCheat(uint32_t which1);
bool S9xLoadCheatFile(const char *filename);
bool S9xSaveCheatFile(const char *filename);

void S9xStartCheatSearch(SCheatData *cheats);
void S9xSearchForChange(SCheatData *cheats, S9xCheatComparisonType cmp, S9xCheatDataSize size, bool is_signed, bool update);
void S9xSearchForValue(SCheatData *cheats, S9xCheatComparisonType cmp, S9xCheatDataSize size, uint32_t value, bool is_signed, bool update);
void S9xOutputCheatSearchResults(SCheatData *cheats);

#endif

#endif
