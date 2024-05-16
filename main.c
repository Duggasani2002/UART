#include <LPC21xx.H>
#include "header.h"

#define sw1 ((IOPIN0>>14)&1)
#define sw2 ((IOPIN0>>15)&1)
#define sw3 ((IOPIN0>>16)&1)

void display_RTC(void);
void enter_hour(void);
void enter_12_24(void);
void enter_min_sec(u32 );
void enter_day_week(void);
void enter_date(void);
void enter_month(void);
void enter_year(void);


u8 h,m,s,dw,dd,mm,yy,flag,flag1;
int main()
{
	i2c_init();
	lcd_init();
/*i2c_byte_write_frame(0xd0,0x0,0x56);
	i2c_byte_write_frame(0xd0,0x1,0x59);
	i2c_byte_write_frame(0xd0,0x2,0x72);
	i2c_byte_write_frame(0xd0,0x3,0x1);
	i2c_byte_write_frame(0xd0,0x4,0x28);
	i2c_byte_write_frame(0xd0,0x5,0x4);
	i2c_byte_write_frame(0xd0,0x6,0x78);
	*/
	
	while(1)
	{
		if(sw3==0)
		{
			while(sw3==0);
			enter_hour();
			enter_12_24();
			enter_min_sec(1);
			enter_min_sec(2);
			enter_date();
			enter_month();
			enter_year();
			enter_day_week();
			if(sw3==0)
			{
				while(sw3==0);
				break;
			}
		}
		display_RTC();
	}
}

void enter_year(void)
{
	u32 i=1;
	lcd_cmd(0x01);
	u32 temp=0;
	lcd_string("enter month");
	while(1)
	{
		lcd_cmd(0xc0);
		if(sw2==0)
		{
			while(sw2==0);
			i++;
			if(i==99)
				i=1;
		}
		print_two_digit(i);
		temp|=(i/10);
	  temp|=(i%10)<<4;
		i2c_byte_write_frame(0xd0,0x6,temp);
		if(sw1==0)
			break;
	}
	while(sw1==0);
	return;
}

void enter_month(void)
{
	u32 i=1;
	lcd_cmd(0x01);
	u32 temp=0;
	lcd_string("enter month");
	while(1)
	{
		lcd_cmd(0xc0);
		if(sw2==0)
		{
			while(sw2==0);
			i++;
			if(i==32)
				i=1;
		}
		print_two_digit(i);
		temp|=(i/10);
	  temp|=(i%10)<<4;
		i2c_byte_write_frame(0xd0,0x5,temp);
		if(sw1==0)
			break;
	}
	while(sw1==0);
	return;
}


void enter_date(void)
{
	u32 i=1;
	lcd_cmd(0x01);
	u32 temp=0;
	lcd_string("enter date");
	while(1)
	{
		lcd_cmd(0xc0);
		if(sw2==0)
		{
			while(sw2==0);
			i++;
			if(i==31)
				i=1;
		}
		print_two_digit(i);
		temp|=(i/10);
	  temp|=(i%10)<<4;
		i2c_byte_write_frame(0xd0,0x4,temp);
		if(sw1==0)
			break;
	}
	while(sw1==0);
	return;
}



void enter_day_week(void)
{
	u32 i=1;
	lcd_cmd(0x01);
	lcd_string("enter DOW");
	while(1)
	{
		lcd_cmd(0xc0);
		if(sw2==0)
		{
			while(sw2==0);
			i++;
			if(i==8)
				i=1;
		}
		switch(i)
		{
			case 1:lcd_string("sun");
			        break;
			case 2:lcd_string("mon");
			        break;
			case 3:lcd_string("tue");
			        break;
			case 4:lcd_string("wed");
			        break;
			case 5:lcd_string("thu");
			        break;
			case 6:lcd_string("fri");
			        break;
			case 7:lcd_string("sat");
			        break;
		}
		if(sw1==0)
			break;
	}
	while(sw1==0);
	dw=i;
	i2c_byte_write_frame(0xd0,0x3,dw);
	return;
}

void enter_min_sec(u32 data)
{
	u32 i=1;
	lcd_cmd(0x01);
	u32 temp=0;
	if(data==1)
	 lcd_string("Enter mins");
	if(data==2)
	 lcd_string("Enter secs");
	while(1)
	{
		lcd_cmd(0xc0);
		if(sw2==0)
		{
			while(sw2==0);
			i++;
			if(i==59)
				i=0;
		}
		temp|=(i/10);
	  temp|=(i%10)<<4;
		if(data==1)
		i2c_byte_write_frame(0xd0,0x1,temp);
		if(data==2)
		i2c_byte_write_frame(0xd0,0x0,temp);
		if(sw1==0)
		{
			while(sw1==0);
			return;
		}
		print_two_digit(i);
	}
}
	
void enter_12_24(void)
{
	u32 i;
	flag1=0;
	i=i2c_byte_read_frame(0xd0,0x2);
	i|=1<<6;
	h|=(i/10);
	h|=(i%10)<<4;
	i2c_byte_write_frame(0xd0,0x2,h);
	lcd_string("AM / PM");
	while(1)
	{
		if(sw1==0)
			break;
		if(flag1)
		{
			i|=1<<5;
	    h|=(i/10);
	    h|=(i%10)<<4;
			lcd_string("PM");
		}
		else
		{
			i&=~(1<<5);
	    h|=(i/10);
	    h|=(i%10)<<4;
			lcd_string("AM");
		}
		while(sw2==1);
		while(sw2==0);
		 flag1^=1;
	}
	i2c_byte_write_frame(0xd0,0x2,h);
	while(sw1==0);
	return;
}


void enter_hour(void)
{
	u32 i=1;
	lcd_cmd(0x01);
	h=0;
	lcd_string("Enter hour");
	while(1)
	{
		lcd_cmd(0xc0);
		if(sw2==0)
		{
			while(sw2==0);
			i++;
			if(i==12)
				i=1;
		}
		h|=(i/10);
	  h|=(i%10)<<4;
		i2c_byte_write_frame(0xd0,0x2,h);
		if(sw1==0)
		{
			while(sw1==0);
			return;
		}
		print_two_digit(i);
	}
}
void display_RTC(void)
{
	  s=i2c_byte_read_frame(0xd0,0x0);
		m=i2c_byte_read_frame(0xd0,0x1);
		h=i2c_byte_read_frame(0xd0,0x2);
		dw=i2c_byte_read_frame(0xd0,0x3);
    dd=i2c_byte_read_frame(0xd0,0x4);
		mm=i2c_byte_read_frame(0xd0,0x5);
		yy=i2c_byte_read_frame(0xd0,0x6);
		
		flag=((h>>6)&1);
		if(flag)
		{
			flag1=((h>>5)&1);
			h=h&0x1f;
		}
		
		lcd_cmd(0x80);
		lcd_data((h/0x10)+48);
		lcd_data((h%0x10)+48);
		lcd_data(':');
		
		lcd_data((m/0x10)+48);
		lcd_data((m%0x10)+48);
		lcd_data(':');
		
		lcd_data((s/0x10)+48);
		lcd_data((s%0x10)+48);
		
		lcd_data(' ');
		if(flag)
		{
			if(flag1)
				lcd_string("PM");
			else
				lcd_string("AM");
		}
		
		lcd_cmd(0xc0);
		lcd_data((dd/0x10)+48);
		lcd_data((dd%0x10)+48);
    lcd_data('/');
		
		lcd_data((mm/0x10)+48);
		lcd_data((mm%0x10)+48);
    lcd_data('/');
		
		lcd_string("20");
		lcd_data((yy/0x10)+48);
		lcd_data((yy%0x10)+48);
		
		lcd_string("  ");
		switch(dw)
		{
			case 1:lcd_string("sun");
			        break;
			case 2:lcd_string("mon");
			        break;
			case 3:lcd_string("tue");
			        break;
			case 4:lcd_string("wed");
			        break;
			case 5:lcd_string("thur");
			        break;
			case 6:lcd_string("fri");
			        break;
			case 7:lcd_string("sat");
			        break;
		}
}
