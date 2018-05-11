#ifndef _FLASH_H_
#define _FLASH_H_
#include "AppConfig.h"
	
u8 read_flash_array_data(uint32_t start_addr,uint16_t *data,uint32_t len);

u16 read_falsh_halfword(uint32_t addr);

u32 read_flash_word(uint32_t addr);

u8 	write_flash_array_data(uint32_t start_addr,uint16_t *data,uint32_t len);

u8 	write_flash_short_data(uint32_t start_addr,uint16_t data);

#endif
