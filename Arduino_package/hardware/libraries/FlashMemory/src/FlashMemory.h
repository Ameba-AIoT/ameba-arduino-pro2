#ifndef _FLASH_MEMORY_H_
#define _FLASH_MEMORY_H_

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "flash_api.h"

#ifdef __cplusplus
}
#endif

// #define NAND_FLASH_SIZE             0x100000

#define NOR_FLASH_SIZE            0x100000
#define FLASH_MEMORY_APP_BASE     0xFD000
#define FLASH_MEMORY_SIZE         NOR_FLASH_SIZE
#define MAX_FLASH_MEMORY_APP_SIZE (FLASH_MEMORY_SIZE - FLASH_MEMORY_APP_BASE)

#ifndef FLASH_SECTOR_SIZE
#define FLASH_SECTOR_SIZE 0x1000
#endif

// @class FlashMemoryClass FlashMemory.h
// @brief Flash memory api
class FlashMemoryClass {
public:
    // @brief Constructor of FlashMemoryClass
    FlashMemoryClass();

    // @brief Destructor of FlashMemoryClass
    ~FlashMemoryClass();

    // @brief Initialize/Re-initialize the base address and size
    // The base address shall align to size of 0x1000 (4kB). And the size shall be multiple of 0x1000.
    // @param[in] flash_base_address The base address
    // @param[in] flash_buf_size The desired work size
    void begin(unsigned int flash_base_address = FLASH_MEMORY_APP_BASE, unsigned int flash_buf_size = MAX_FLASH_MEMORY_APP_SIZE);

    // @brief free the buf set by begin, deinit flash memory process
    void end();

    // @brief Read the content to buf
    // Read flash memory into the buf. The size would be buf_size.
    // @param[in] offset The offset according to base address
    void read(unsigned int offset = 0);

    // @brief Write buf back to flash memory
    // Write flash memory with the content of buf. The size is buf_size.
    // @param[in] offset The offset according to base address
    void write(unsigned int offset = 0);

    // @brief Read 4 bytes from flash memory
    // Read 4 byte from specific offset based on base address.
    // @param[in] offset The offset according to base address
    // @return the read data with size of 4 bytes
    unsigned int readWord(unsigned int offset);

    // @brief Write 4 bytes into flash memory
    // It will try to write 4 bytes first. If the read data differ from the write data, then buffer the sector of flash memory, erase it, and
    // write correct data back to it.
    // @param[in] offset The offset according to base address
    void writeWord(unsigned int offset, unsigned int data);

    // @brief Erase flash memory by sector
    // Erase flash memory, the size is multiples of sector size.
    // @param[in] offset The offset according to base address
    void eraseSector(unsigned int sector_offset);

    // @brief Erase flash memory by word
    // Erase flash memory, the size is word size.
    // @param[in] offset The offset according to base address
    void eraseWord(unsigned int offset);

    // @brief The buf size regarded as work size
    unsigned int buf_size;

    // @brief The buf to be operated.
    // @note Modify buf won't change the content of buf. It needs update to write back to flash memory.
    unsigned char *buf;

private:
    unsigned int _flash_base_address;
    flash_t *_pFlash;
};

extern FlashMemoryClass FlashMemory;

#endif
