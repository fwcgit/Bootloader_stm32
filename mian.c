#include "AppConfig.h"
#include "usart.h"
#include "flash.h"
#include <stdio.h>
#include "IAP.h"




/**__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0             //set Main Stack value
    BX r14
}**/

int main(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH,0);
	__enable_irq();
	
	USART1_init();
	LOG("bootloader\r\n");
	
	#if 1
	if(read_falsh_halfword(0X08032800) == 0xf080)
	{
		 
		start_app();
                                                                  //???A              
	}
	else
	{
		rece_ack();
			while(1)
		{
			listener_USART1_data();
		}
	}
	#endif
	
	#if 0
		rece_ack();
		while(1)
		{
			listener_USART1_data();
		}
	#endif

}
