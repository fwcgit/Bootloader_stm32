#ifndef _USART_H_
#define _USART_H_
#include "AppConfig.h"

void USART1_init(void);
void LOG(char *log);
void LOG_u16(u16 *log,u16 len);
void send_data(u8 *dat,u16 len);
u8* get_USART1_RECE_BUFF(void);
u8  *get_USART1_rece_complete(void);
u16 get_data_len(void);
u8  *get_file_download_complete(void);

#endif
