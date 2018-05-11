#ifndef _IAP_H_
#define _IAP_H_
#include "AppConfig.h"
#include "usart.h"

void listener_USART1_data(void);

void IAP_RESET(void);

void rece_ack(void);

#endif
