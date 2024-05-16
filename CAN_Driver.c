#include <LPC21xx.H>
#include "header.h"
void can1_init(void)
{
	PINSEL1|=0x00040000;
	VPBDIV=1;
	C1MOD=1;
	AFMR=0x2;
	C1BTR=0x001c001d;
	C1MOD=0;
}

#define TCS ((C1GSR>>3)&1)
void can1_tx(CAN1 v)
{
	C1TID1=v.id;
	C1TFI1=(v.dlc<<16);
	if(v.rtr==0)
	{
		C1TDA1=v.byteA;
		C1TDB1=v.byteB;
	}
	else
		C1TFI1|=(1<<30);
	C1CMR=1|(1<<5);
	while(TCS==0);
}

#define RBS (C1GSR&1)
void can1_rx(CAN1 *ptr)
{
	while(RBS==0);
	ptr->id=C1RID;
	ptr->dlc=(C1RFS>>16)&0X0F;
	ptr->rtr=(C1RFS>>30)&0X1;
	if(ptr->rtr==0)
	{
		ptr->byteA=C1RDA;
		ptr->byteB=C1RDB;
	}
	C1CMR=(1<<2);
}