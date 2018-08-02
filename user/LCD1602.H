#include "reg51.h"
#ifndef __LCD1602__
#define __LCD1602__
 /*=================================================
*自定义数据类型
=================================================*/
typedef unsigned char uchar;
typedef unsigned int uint;

#define LCD1602_DB P0	//LCD1602数据总线

sbit LCD1602_RS = P3^5;	 //RS端
sbit LCD1602_RW = P3^6;	 //RW端
sbit LCD1602_EN = P3^4;	 //EN端


void Read_Busy();
void LCD1602_Write_Cmd(uchar cmd);
void LCD1602_Write_Dat(uchar dat);
void LCD1602_Dis_OneChar(uchar x, uchar y,uchar dat);
void LCD1602_Dis_Str(uchar x, uchar y, uchar *str);
void Init_LCD1602();
#endif