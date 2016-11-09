/************************************************************************/
/*文件名：public.h                                                      */
/*作  用：全局公共头文件                                                */
/************************************************************************/
#pragma once
#pragma comment(lib, "winmm.lib")

#define _WIN32_WINNT 0x0500

#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include "CalendarDlg.h"
#include "ClockDlg.h"
#include "SetupDlg.h"
#include "MemDlg.h"
#include "AlarmDlg.h"
#include "SpecialDlg.h"


 typedef struct _stDateTime
{
	int nYear;
	int nMonth;
	int nDay;
}stDateTime;
//声名'用于保存应用程序实例的句柄'的变量
extern HINSTANCE g_hInst;
//声名‘保存主窗口句柄’的变量
extern HWND      g_hMainWnd;

	
char *GetGanZhiMonth(int ,int);
char* GetGanZhi(int nYear);
void CalendarSelChange();//当选项变化的时候
typedef struct _curDay
{
	int year;
	int month;
	int day;
}curDay;
typedef struct _alarm
{
	int hour;
	int minute;
	int style;
	int sound;
}Alarm;
typedef struct _memory
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int is_sun;
	int is_tell;
	TCHAR name[10];
}Memory;
extern Memory cur_memory[100];//暂存100个纪念日
extern curDay cur_datetime;//日历修改数据
extern int remindfull;//整点报时
extern int alarmnum;//闹铃数目
extern int memorynum;//纪念日数目
extern int remindmem[100];
extern int cur_remindmem;
extern int skin;//皮肤
extern Alarm cur_alarm[10];//闹铃
void PlayOnFull(int hour);//整点提醒
void PlayAlarm(HWND hDlg,int i);//闹铃
void read_alarm();//读取闹钟
void PlayMemory(HWND hDlg);
