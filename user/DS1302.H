#ifndef __DS1302__
#define __DS1302__
#include<reg51.h>
#include<intrins.h>
sbit sclk = P1^0; //对应DS1302的 TSCLK
sbit dio = P1^1;  //对应DS1302的 TIO
sbit ce = P1^2;	  //对应DS1302的 TRST/CE
void write_1302(unsigned char add,dat)
{
	unsigned char i,temp;
	temp=add;
	ce=0;
	_nop_();
	sclk=0;
	_nop_();
	ce=1;
	_nop_();
	for(i=0;i<8;i++)
	{
		sclk=0;
		_nop_();
		if((temp&0x01)==0x01)
			dio=1;
			else
			dio=0;
		temp>>=1;
		sclk=1;
		_nop_();
	}
	temp=dat;
	for(i=0;i<8;i++)
	{
		sclk=0;
		_nop_();
		if((temp&0x01)==0x01)
			dio=1;
			else
			dio=0;
		temp>>=1;
		sclk=1;
		_nop_();
	}
	ce=0;
	sclk=0;
}
unsigned char read_1302(unsigned char add)
{
	unsigned char dat,dat1,i,temp;
	temp=add;
	ce=0;
	_nop_();
	sclk=0;
	_nop_();
	ce=1;
	for(i=0;i<8;i++)
	{
		sclk=0;
		_nop_();
		if((temp&0x01)==0x01)
			dio=1;
			else
			dio=0;
		temp>>=1;
		sclk=1;
		_nop_();
	}
	for(i=0;i<8;i++)
	{
		sclk=0;
		_nop_();
		if(dio)
		    dat|=0x80;
		if(i<7)
			dat>>=1;
		sclk=1;
	}
	dat1=dat/16;
	dat=dat%16;
	dat=dat1*10+dat;  
	ce=0;
	sclk=0;
	return dat;
}

#endif