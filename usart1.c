#include "usart.h"
#include <stdio.h>
#include "IAP.h"

u8 rece_buff[USART_RX_SIZE];
u16 rx_index = 0;
u8  is_rece_stop = 0;
u8  is_rece_head = 0 ;
u16 data_len = 0;
u8  file_download_complete = 0;

void USART1_init(void)
{
	GPIO_InitTypeDef 	GPIO_Init_Type_Struct;
	USART_InitTypeDef USART_Init_Type_Struct;
	NVIC_InitTypeDef	NVIC_Init_Type_Struct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	GPIO_Init_Type_Struct.GPIO_Pin 		= GPIO_Pin_9;
	GPIO_Init_Type_Struct.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_Init_Type_Struct.GPIO_Speed	= GPIO_Speed_50MHz;

	GPIO_Init(GPIOA,&GPIO_Init_Type_Struct);

	GPIO_Init_Type_Struct.GPIO_Pin 		= GPIO_Pin_10;
	GPIO_Init_Type_Struct.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init_Type_Struct.GPIO_Speed	= GPIO_Speed_50MHz;

	GPIO_Init(GPIOA,&GPIO_Init_Type_Struct);
	
	
	USART_Init_Type_Struct.USART_BaudRate 							= 115200;
	USART_Init_Type_Struct.USART_WordLength 						= USART_WordLength_8b;
	USART_Init_Type_Struct.USART_StopBits 							= USART_StopBits_1;
	USART_Init_Type_Struct.USART_Parity 								= USART_Parity_No;
	USART_Init_Type_Struct.USART_HardwareFlowControl 		= USART_HardwareFlowControl_None;
	USART_Init_Type_Struct.USART_Mode 									= USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1,&USART_Init_Type_Struct);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_Init_Type_Struct.NVIC_IRQChannel 									= USART1_IRQn;
	NVIC_Init_Type_Struct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init_Type_Struct.NVIC_IRQChannelSubPriority 				= 1;
	NVIC_Init_Type_Struct.NVIC_IRQChannelCmd								= ENABLE;
	
	NVIC_Init(&NVIC_Init_Type_Struct);
	
	USART_Cmd(USART1,ENABLE);

}

void LOG(char *log)
{
	
	USART1->SR;
	while(*log != '\0')
	{
		USART_SendData(USART1,*log++);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	}

}

void LOG_SHORT(u16 log)
{
		USART1->SR;
		
		USART_SendData(USART1,log);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	
		USART_SendData(USART1,log>>8);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
}

void LOG_u16(u16 *log,u16 len)
{
	u16 i;
	USART1->SR;
	for(i = 0 ;i < len ;i++)
	{
		USART_SendData(USART1,*log++);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	}
}

void send_data(u8 *dat,u16 len)
{
	u16 i;
	USART1->SR;
	for(i = 0 ;i < len ;i++)
	{
		USART_SendData(USART1,*(dat+i));
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	}
}


int fputc(int ch,FILE *file)
{
	
	USART_SendData(USART1,(unsigned char)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	return ch;
	
}

void USART1_IRQHandler(void)
{
	
	u8 r_buff;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		
		if(rx_index >= USART_RX_SIZE)
		{
			data_len = 0;
			is_rece_head = 0;
			rx_index = 0;
			is_rece_stop = 0;
			file_download_complete = 0;
		}
		
		r_buff = USART_ReceiveData(USART1);
		
		if(is_rece_head)
		{
			rece_buff[rx_index] = r_buff;
		}
		
		if(r_buff == 0xa0 && is_rece_head == 0) //包头
		{
			rx_index = 0;
			data_len = 0;
			is_rece_head = 1;
			file_download_complete = 0;
			rece_buff[rx_index] = r_buff;

		}else if(is_rece_head && rx_index == 3)//数据长度
		{
				
				data_len = rece_buff[3];
				data_len = data_len << 8 | rece_buff[2];
				
			
		}
		
		if(is_rece_head && rx_index >= 3 && data_len == rx_index -3)
		{
			
			rx_index = 0;
			is_rece_head = 0;
			data_len = 0;
				
			if(rece_buff[1] == 0xa1)
			{
				rx_index = 0;
				is_rece_head = 0;
				IAP_RESET();
			}
			else if(rece_buff[1] == 0x1a)//数据传输完成
			{
				rx_index = 0;
				is_rece_head = 0;
				file_download_complete = 1;
			}
			else
			{
				is_rece_stop = 1;
			}
			
		}
		
		rx_index++;
	
		USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
	}
}

u8* get_USART1_RECE_BUFF(void)
{
	return (u8 *)rece_buff;
}
u8  *get_USART1_rece_complete(void)
{
	return &is_rece_stop;
}

u16 get_data_len(void)
{
	return data_len;
}

u8  *get_file_download_complete(void)
{
	return &file_download_complete;
}

