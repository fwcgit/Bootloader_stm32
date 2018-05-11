#include "utils.h"
u8 calc_code_sum(u8 *dat,u16 len)
{
	u16 i;
	u32 sum = 0;
	
	for(i = 0 ; i < len-1 ; i++)
	{
		sum = sum+*(dat+i);
	}
	
	return (u8)sum;
}

u8 code_check(u8 *dat,u16 len)
{
	if(calc_code_sum(dat,len) == *(dat+(len-1)))
	{
		return 1;
	}
	
	return 0;
}
