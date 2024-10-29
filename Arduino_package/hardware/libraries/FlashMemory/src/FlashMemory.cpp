#include "FlashMemory.h"

flash_t flash_obj;

FlashMemoryClass::FlashMemoryClass()
{
    _flash_base_address = FLASH_MEMORY_APP_BASE;
    buf_size = MAX_FLASH_MEMORY_APP_SIZE;

    buf = (unsigned char *)(malloc(MAX_FLASH_MEMORY_APP_SIZE));
    _pFlash = &flash_obj;
}

FlashMemoryClass::~FlashMemoryClass()
{
    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }
}

void FlashMemoryClass::begin(unsigned int flash_base_address, unsigned int flash_buf_size)
{
    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }

    if ((FLASH_MEMORY_APP_BASE <= flash_base_address) && (flash_base_address <= FLASH_MEMORY_SIZE)) {
        _flash_base_address = flash_base_address;
    } else {
        _flash_base_address = FLASH_MEMORY_APP_BASE;
    }

    if (flash_buf_size > MAX_FLASH_MEMORY_APP_SIZE) {
        buf_size = MAX_FLASH_MEMORY_APP_SIZE;
    } else {
        buf_size = flash_buf_size;
    }
    buf = (unsigned char *)(malloc(buf_size));
}

void FlashMemoryClass::end()
{
    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }
}

void FlashMemoryClass::read(unsigned int offset)
{
    if ((_flash_base_address + offset) < FLASH_MEMORY_APP_BASE) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    } else if ((_flash_base_address + offset + buf_size) > FLASH_MEMORY_SIZE) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    }

    flash_stream_read(_pFlash, (_flash_base_address + offset), buf_size, (uint8_t *)buf);
}

void FlashMemoryClass::write(unsigned int offset)
{
    if ((_flash_base_address + offset) < FLASH_MEMORY_APP_BASE) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    } else if ((_flash_base_address + offset + buf_size) > FLASH_MEMORY_SIZE) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    }

    for (int i = 0; i < (MAX_FLASH_MEMORY_APP_SIZE / FLASH_SECTOR_SIZE); i++) {
        flash_erase_sector(_pFlash, (_flash_base_address + (i * FLASH_SECTOR_SIZE)));
    }

    flash_stream_write(_pFlash, (_flash_base_address + offset), buf_size, (uint8_t *)buf);
}

unsigned int FlashMemoryClass::readWord(unsigned int offset)
{
    if ((_flash_base_address + offset) < FLASH_MEMORY_APP_BASE) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return 0;
    } else if ((_flash_base_address + offset) > (FLASH_MEMORY_SIZE - 4)) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return 0;
    }

    unsigned int value;

    flash_read_word(_pFlash, _flash_base_address + offset, (uint32_t *)&value);

    return value;
}

void FlashMemoryClass::writeWord(unsigned int offset, unsigned int data)
{
    if ((_flash_base_address + offset) < FLASH_MEMORY_APP_BASE) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    } else if ((_flash_base_address + offset) > (FLASH_MEMORY_SIZE - 4)) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    }

    unsigned int check_val;
    unsigned char *tmp_buf;
    unsigned int *tmp_val;
    unsigned int tmp_sector_adr;

    flash_write_word(_pFlash, _flash_base_address + offset, data);
    flash_read_word(_pFlash, _flash_base_address + offset, (uint32_t *)&check_val);

    if (check_val != data) {
        tmp_sector_adr = ((_flash_base_address + offset) / FLASH_SECTOR_SIZE) * FLASH_SECTOR_SIZE;
        tmp_buf = (unsigned char *)(malloc(FLASH_SECTOR_SIZE));
        flash_stream_read(_pFlash, tmp_sector_adr, FLASH_SECTOR_SIZE, tmp_buf);
        flash_erase_sector(_pFlash, tmp_sector_adr);
        tmp_val = (unsigned int *)(tmp_buf + _flash_base_address + offset - tmp_sector_adr);
        *tmp_val = data;
        flash_stream_write(_pFlash, tmp_sector_adr, FLASH_SECTOR_SIZE, tmp_buf);
        free(tmp_buf);
    }
}

void FlashMemoryClass::eraseSector(unsigned int sector_offset)
{
    if ((sector_offset % FLASH_SECTOR_SIZE) != 0) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    }

    flash_erase_sector(_pFlash, (_flash_base_address + sector_offset));
}

void FlashMemoryClass::eraseWord(unsigned int offset)
{
    if ((_flash_base_address + offset) < FLASH_MEMORY_APP_BASE) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    } else if ((_flash_base_address + offset) > (FLASH_MEMORY_SIZE - 4)) {
        printf("\r\n[ERROR] %s. Invalid offset \n", __FUNCTION__);
        return;
    }

    unsigned char *tmp_buf;
    unsigned int *tmp_val;
    unsigned int tmp_sector_adr;

    tmp_sector_adr = ((_flash_base_address + offset) / FLASH_SECTOR_SIZE) * FLASH_SECTOR_SIZE;
    tmp_buf = (unsigned char *)(malloc(FLASH_SECTOR_SIZE));
    flash_stream_read(_pFlash, tmp_sector_adr, FLASH_SECTOR_SIZE, tmp_buf);
    flash_erase_sector(_pFlash, tmp_sector_adr);
    tmp_val = (unsigned int *)(tmp_buf + _flash_base_address + offset - tmp_sector_adr);
    *tmp_val = 0;
    flash_stream_write(_pFlash, tmp_sector_adr, FLASH_SECTOR_SIZE, tmp_buf);
    free(tmp_buf);
}

FlashMemoryClass FlashMemory = FlashMemoryClass();
