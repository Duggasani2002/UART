#include <LPC21xx.H>
#include<stdio.h>
#include"header.h"

#define RDR (U0LSR&1)
#define THRE ((U0LSR>>5)&1)

void uart0_init(int baud)
{
	u32 a[]={15,60,30,0,15},pclk,result;
	pclk=a[VPBDIV]*1000000;
	PINSEL0|=0X5;
	U0LCR=0X83;
	result=pclk/(16*baud);
	U0DLL=result&0xff;
	U0DLM=(result>>8)&0xff;
	U0LCR=0X03;
}

void uart0_tx(u8 data)
{
	U0THR=data;
	while(THRE==0);
}

void uart0_tx_string(u8 *ptr)
{
	while(*ptr!=0)
	{
		uart0_tx(*ptr);
		ptr++;
	}
}

void uart0_tx_int(u32 data)
{
	u8 buff[12];
	sprintf(buff,"%d",data);
	uart0_tx_string(buff);
}

void uart0_tx_float(float data)
{
	u8 buff[12];
	sprintf(buff,"%.1f",data);
	uart0_tx_string(buff);
}

u8 uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

void uart0_rx_string(s8 *ptr,u8 max_bytes)
{
	s32 i;
	for(i=0;i<max_bytes;i++)
	{
		while(RDR==0);
		ptr[i]=U0RBR;
		if(ptr[i]=='\r')
		 break;
	}
	ptr[i]=0;
}

void uart0_tx_hex(u8 temp)
{
	u8 t;
	t=((temp>>4)&0Xf);
	if(t<10)
		uart0_tx(t+48);
	else
		uart0_tx(t-10+65);
	t=(temp&0xf);
	if(t<10)
		uart0_tx(t+48);
	else
		uart0_tx(t-10+65);
}
