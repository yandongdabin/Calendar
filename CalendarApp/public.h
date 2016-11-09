/************************************************************************/
/*�ļ�����public.h                                                      */
/*��  �ã�ȫ�ֹ���ͷ�ļ�                                                */
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
//����'���ڱ���Ӧ�ó���ʵ���ľ��'�ı���
extern HINSTANCE g_hInst;
//���������������ھ�����ı���
extern HWND      g_hMainWnd;

	
char *GetGanZhiMonth(int ,int);
char* GetGanZhi(int nYear);
void CalendarSelChange();//��ѡ��仯��ʱ��
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
extern Memory cur_memory[100];//�ݴ�100��������
extern curDay cur_datetime;//�����޸�����
extern int remindfull;//���㱨ʱ
extern int alarmnum;//������Ŀ
extern int memorynum;//��������Ŀ
extern int remindmem[100];
extern int cur_remindmem;
extern int skin;//Ƥ��
extern Alarm cur_alarm[10];//����
void PlayOnFull(int hour);//��������
void PlayAlarm(HWND hDlg,int i);//����
void read_alarm();//��ȡ����
void PlayMemory(HWND hDlg);
