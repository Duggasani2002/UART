#include <LPC21xx.H>
#include"header.h"
void i2c_init(void)
{
	PINSEL0|=0X50;
	I2SCLH=I2SCLL=75;
	I2CONSET=(1<<6);
}

#define SI ((I2CONSET>>3)&1)
void i2c_byte_write_frame(u8 sa,u8 mr,u8 data)
{
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=(1<<5);
	
	I2DAT=sa;
	I2CONCLR=(1<<3);
	while(SI==0);
	
	I2DAT=mr;
	I2CONCLR=(1<<3);
	while(SI==0);
	
	I2DAT=data;
	I2CONCLR=(1<<3);
	while(SI==0);
	
	I2CONSET=(1<<4);
	I2CONCLR=(1<<3);
}

u8 i2c_byte_read_frame(u8 sa,u8 mr)
{
	u8 temp;
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=(1<<5);
	
	I2DAT=sa;
	I2CONCLR=(1<<3);
	while(SI==0);
	
	I2DAT=mr;
	I2CONCLR=(1<<3);
	while(SI==0);
	
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=(1<<5);
	
	I2DAT=sa|1;
	I2CONCLR=(1<<3);
	while(SI==0);
	
	I2CONCLR=(1<<3);
	while(SI==0);
	temp=I2DAT;
	
	I2CONSET=(1<<4);
	I2CONCLR=(1<<3);
	return temp;
}
