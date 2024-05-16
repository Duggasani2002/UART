#include <LPC21xx.H>
#include "header.h"
CAN1 v1;
int main()
{
	can1_init();
	v1.id=0x123;
	v1.rtr=0;
	v1.dlc=8;
	v1.byteA=0x44332211;
	v1.byteB=0x88776655;
	can1_tx(v1);
}

