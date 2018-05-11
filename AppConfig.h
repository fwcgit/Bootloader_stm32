#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_
#include <stm32f10x.h>

#define MCU_FLASH_SIZE 256

#if MCU_FLASH_SIZE < 256
	#define PAGE_SIZE 1024
	#define USART_RX_SIZE 1024 + 1 + 2
#else
	#define PAGE_SIZE 2048
	#define USART_RX_SIZE 2048 + 1 + 2
#endif	

#define ApplitionAddr 0x8004000
#define VectorTable_Offset  0x4000

#endif
