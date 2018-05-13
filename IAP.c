#include "IAP.h"
#include "flash.h"
#include <string.h>

u32 start_addr = FLASH_ApplitionAddr;

typedef void (*IAPFun)(void);
IAPFun Jump_To_Application;

void rece_ack(void)
{
		u8 dat[4] = {0xa0,0x80,0x00,0x00};
		send_data(dat,4);
}

void wirte_flash(void)
{
	u16 i,j,temp;
	u32 offsetAddr,pageAddr,pageIndex;
	
	
	u16 data_len;
	u8 *src_data = get_USART1_RECE_BUFF();
	
	data_len = src_data[3];
	data_len = data_len << 8 | src_data[2];
	
	LOG_SHORT(data_len);
	
	data_len = data_len + 4;
	
	offsetAddr = start_addr - FLASH_BASE;
	pageIndex	 = offsetAddr / PAGE_SIZE;
	pageAddr	 = pageIndex * PAGE_SIZE + FLASH_BASE;
	
	FLASH_Unlock();
	FLASH_ErasePage(pageAddr);
		
	for(i = 4 ,j = 0 ; i < data_len;i+=2,j++)
	{
			
			if(i+1 < data_len)
			{
				temp = src_data[i+1] & 0x00ff;
				temp = (temp << 8)&0xff00;
				temp = temp | (src_data[i]&0x00ff);
			}
			else
			{
				temp = src_data[i];
			}
			
			FLASH_ProgramHalfWord(start_addr+j*2,temp);
			
	}
	
	start_addr = start_addr+j*2;
	
	FLASH_Lock();
	
	rece_ack();
}

void start_app(void)
{
	
		vu32 JumpAddress;
		write_flash_short_data(0X08032800,0Xf080);
		
		__disable_irq();
	
		JumpAddress = *(__IO uint32_t*) (ApplitionAddr + 4);  
		Jump_To_Application = (IAPFun) (JumpAddress);  

		__set_MSP(*(__IO uint32_t*) ApplitionAddr);  
		Jump_To_Application();
	
		__enable_irq();
}

void start_IAP(void)
{
		vu32 JumpAddress;
		write_flash_short_data(0X08032800,0Xff80);
		
		__disable_irq();
	
		JumpAddress = *(__IO uint32_t*) (IAP_ApplitionAddr + 4);  
		Jump_To_Application = (IAPFun) (JumpAddress);  

		__set_MSP(*(__IO uint32_t*) IAP_ApplitionAddr);  
		Jump_To_Application();
	
		__enable_irq();
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
	write_flash_short_data(0X08032800,0Xff80);
	start_addr = FLASH_ApplitionAddr;
	rece_ack();
}
