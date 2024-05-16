#include <LPC21xx.H>
#include"header.h"

#define DONE ((ADDR>>31)&1)

void adc_init(void)
{
	PINSEL1|=0x1540000;
	ADCR=0x00200400;
}

u32 adc_read(u8 ch_num)
{
	u32 result;
	ADCR|=1<<ch_num;
	ADCR|=1<<24;
	while(DONE==0);
	ADCR^=1<<ch_num;
	ADCR^=1<<24;
	result=(ADDR>>6)&0x3ff;
	return result;
}
