#include "flash.h"
#include "stdio.h"
u8 read_flash_array_data(uint32_t start_addr,uint16_t *data,uint32_t len)
{
		uint16_t index;
		u16 dat;
		if(start_addr <  FLASH_BASE || (start_addr + len * 2) >= FLASH_BASE + 1024 * MCU_FLASH_SIZE) return 1;
	
		for(index = 0; index < len ; index++)
		{
				
			dat= read_falsh_halfword(start_addr+index * 2);
			*(data+index)  = dat;
		}
				
		return 0;
}

u16 read_falsh_halfword(uint32_t addr)
{
	return *((__IO u16*)(addr));
}

u32 read_flash_word(uint32_t addr)
{
	return *((__IO u32*)(addr));
}

u8 	write_flash_array_data(uint32_t start_addr,uint16_t *data,uint32_t len)
{
	u32 offsetAddr,pageIndex,pageAddr,index;
	
	if(start_addr < FLASH_BASE || (start_addr + len *2) >= (FLASH_BASE + 1024 * MCU_FLASH_SIZE)) return 1;
	
	offsetAddr	= start_addr - FLASH_BASE;
	pageIndex		=	offsetAddr / PAGE_SIZE;
	pageAddr		= pageIndex * PAGE_SIZE + FLASH_BASE;
	
	FLASH_Unlock();
	
	FLASH_ErasePage(pageAddr);
	
	for(index = 0 ; index < len ;index++)
		FLASH_ProgramHalfWord(start_addr + index * 2,*(data+index));
	
	FLASH_Lock();
	
	return 0;
}

u8 	write_flash_short_data(uint32_t start_addr,uint16_t data)
{
		u32 offsetAddr,pageIndex,pageAddr;
	
		if(start_addr < FLASH_BASE) return 1;
	
		offsetAddr = start_addr - FLASH_BASE;
		pageIndex	 = offsetAddr / PAGE_SIZE;
		pageAddr	 = pageIndex * PAGE_SIZE + FLASH_BASE;
	
		FLASH_Unlock();
		FLASH_ErasePage(pageAddr);
		FLASH_ProgramHalfWord(start_addr,data);
		FLASH_Unlock();
	
		return 0;
}

	
