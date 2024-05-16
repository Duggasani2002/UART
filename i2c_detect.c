#include <LPC21xx.H>
#include"header.h"
#define SI ((I2CONSET>>3)&1)

int main()
{
	i2c_init();
	uart0_init(9600);
	u32 i,j;
	u8 temp;
	for(i=0;i<=15;i++)
	{
		for(j=0;j<=15;j+=2)
		{
		temp=0;
		delay_ms(300);
			I2CONSET=(1<<5);
	    I2CONCLR=(1<<3);
	    while(SI==0);
	    I2CONCLR=(1<<5);
			
		  temp|=i<<4;
			temp|=j;
			
			I2DAT=temp;
	    I2CONCLR=(1<<3);
	    while(SI==0);
			
			if(I2STAT==0X18)
			{
				uart0_tx_hex(temp);
				//return 0;
			}				
			
			uart0_tx('\r');
			uart0_tx_hex(temp);
			I2CONSET=(1<<4);
	    I2CONCLR=(1<<3);	
		}
	}
}

