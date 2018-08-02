/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                           (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*                                               EXAMPLE #1
*********************************************************************************************************
*/

#include "../source/includes.h"
#include "LCD1602.H" //导入LCD1602的显示库。

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK   xdata     TaskStk[TASK_STK_SIZE];        /* Tasks stacks，放在xdata里。  						  */
OS_STK   xdata     Task1Stk[TASK_STK_SIZE];        /* Tasks stacks，放在xdata里。                           */

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  Task(void *data1) RUNSISI_LARGE_REENTRANT;                       /* Function prototypes of tasks                  */
void  Task1(void *data1) RUNSISI_LARGE_REENTRANT;                       /* Function prototypes of tasks                  */
void InitTimer0();

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

void  main (void)
{
    OSInit();                                              /* Initialize uC/OS-II                      */
	InitTimer0();   //启动定时器0
	OSTaskCreate(Task,0, &TaskStk[0],4);			  //创建任务函数Task的任务，参数依次为函数指针（即函数名），函数的参数，任务栈，优先级。
	OSTaskCreate(Task1,0, &Task1Stk[0],5);			  //创建任务函数Task1的任务，参数依次为函数指针（即函数名），函数的参数，任务栈，优先级。
    OSStart();                                             /* Start multitasking                       */
}


/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/
xdata unsigned short sec=0,min=0,hour=0,day=0;	//分别是记录秒分时天的变量
void  Task(void *data1) RUNSISI_LARGE_REENTRANT
{
while(1)
{
OSTimeDlyHMSM(0,0,1,0); //延时大约1s
P1^=0x1; //P1.0取反，P1.0接的一个LED，因此会闪烁。
sec++;
}

}

void  Task1(void *data1) RUNSISI_LARGE_REENTRANT	 //此任务对LCD1602液晶进行操作
{
Init_LCD1602();
LCD1602_Dis_Str(0,0,"Current Time:");
sec=0;
while(1)
{
sec>=60?(min++,sec=0):sec;
min>=60?(hour++,sec=0):min;
hour>=24?(day++,sec=0):hour;//对时分秒的数值进行修正，使其处于合理范围。

LCD1602_Dis_OneChar(2,1,48+day/100);
LCD1602_Dis_OneChar(3,1,48+day%100/10);
LCD1602_Dis_OneChar(4,1,48+day%10); //显示天数

LCD1602_Dis_OneChar(6,1,48+hour/10);
LCD1602_Dis_OneChar(7,1,48+hour%10); //显示小时数

LCD1602_Dis_OneChar(8,1,':');  //分隔符

LCD1602_Dis_OneChar(9,1,48+min/10);
LCD1602_Dis_OneChar(10,1,48+min%10); //显示分钟数

LCD1602_Dis_OneChar(11,1,':');  //分隔符

LCD1602_Dis_OneChar(12,1,48+sec/10);
LCD1602_Dis_OneChar(13,1,48+sec%10); //显示秒数

OSTimeDly(15);//延时15个时间片
}

}


void InitTimer0() //初始化定时0，操作系统核心中断
{
	TMOD &= 0xf0;
	TMOD |= 0x01;
	TH0 = 0xb1;
	TL0 = 0xe0;
	ET0 = 1;
	TR0 = 1;
	EA=1;
}