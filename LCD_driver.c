#include <LPC21xx.H>
#include<stdio.h>
#include"header.h"

#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)

void lcd_init(void)
{
	IODIR1|=0x00fe0000;
	PINSEL2|=0;
	IOCLR1=EN;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x28);
	lcd_cmd(0x0e);
	lcd_cmd(0x01);
}

void lcd_data(u8 data)
{
	IOCLR1=0x00fe0000;
	u32 temp;
	temp=(data&0xf0)<<16;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
	
	IOCLR1=0x00fe0000;
	temp=(data&0x0f)<<20;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}

void lcd_cmd(u8 data)
{
	IOCLR1=0x00fe0000;
	u32 temp=0;
	temp=(data&0xf0)<<16;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
	
	IOCLR1=0x00fe0000;
	temp=(data&0x0f)<<20;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}

void delay_ms(u32 ms)
{
	T0PC=0;
	T0PR=15000-1;
	T0TC=0;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}

void lcd_string(u8 *ptr)
{
	while(*ptr!=0)
	{
		lcd_data(*ptr);
		ptr++;
	}
}
void print_two_digit(u32 data)
{
	lcd_data((data/10)+48);
	lcd_data((data%10)+48);
}

/*void lcd_int(u32 data)
{
	u8 buff[12];
	sprintf(buff,"%d",data);
	lcd_string(buff);
}*/

