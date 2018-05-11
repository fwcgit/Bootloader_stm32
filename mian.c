#include "AppConfig.h"
#include "usart.h"
#include "flash.h"
#include <stdio.h>
#include "IAP.h"

int main(void)
{
	
	USART1_init();
	LOG("bootloader\r\n");
		
	if(read_falsh_halfword(0X08002800) == 0xf080)
	{
			NVIC_SetVectorTable(NVIC_VectTab_FLASH, VectorTable_Offset);
			SystemInit ();
			SCB->VTOR = FLASH_BASE | VectorTable_Offset;
	}
	else
	{
		rece_ack();
	}	
	
	while(1)
	{
		listener_USART1_data();
	}
}
