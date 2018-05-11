#include "IAP.h"
#include "flash.h"
#include <string.h>

u16 pageIndex = 0;

void rece_ack(void)
{
		u8 dat[2] = {0xa0,0x80};
		
		send_data(dat,2);
}

void wirte_flash(void)
{
	u16 i;
	u8 data_len = get_data_len();
	u8 dst_data[data_len];
	uint16_t file_data[data_len/2 +1];
	u8 *src_data = get_USART1_RECE_BUFF();
	memcpy(src_data+3,dst_data,data_len);
	
	for(i = 0 ; i < data_len/2;i+=2)
	{
		
			file_data[i] = dst_data[i+1];
			
			file_data[i] = (file_data[i] << 8) | dst_data[i];
	}
	
	if(data_len % 2 != 0)
	{
		file_data[data_len/2+1] = dst_data[data_len-1];
	}
	
	write_flash_array_data(ApplitionAddr+pageIndex*PAGE_SIZE,file_data,PAGE_SIZE);
	
	pageIndex++;
	
	rece_ack();
}

void start_app(void)
{
	
	write_flash_short_data(0X08002800,0Xf080);
	
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, VectorTable_Offset);
	SystemInit ();
	SCB->VTOR = FLASH_BASE | VectorTable_Offset;
	
}

void listener_USART1_data(void)
{
	 u8 *rece, *download;
	rece = get_USART1_rece_complete();
	download = get_file_download_complete();
	
	if(*rece)
	{
			*rece = 0;
			wirte_flash();
	}
	
	if(*download)
	{
		*download = 0;
		start_app();
	}
	
}

void IAP_RESET(void)
{
	pageIndex = 0;
	rece_ack();
}
