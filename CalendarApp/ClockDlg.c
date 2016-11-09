#include "public.h"

static HBITMAP  m_hBkBmp=NULL;
HWND      g_hMainWnd=NULL;
static int skin;
FILE *file;
TCHAR buffer[20];
stDateTime sunDay,lunarDay;
char full[10];
HWND hwnd;
HDC hdc;
void UpdateClock(HWND hWnd,HDC hDC)
{
	
	HDC hdcMemory=CreateCompatibleDC(hDC);
	//���ƴ��屳��ͼƬ
	SelectObject(hdcMemory,m_hBkBmp);
	//�������ֱ���Ϊ͸��ģʽ
	SetBkMode(hdcMemory,TRANSPARENT);

	DrawClockText(hdcMemory);
	BitBlt(hDC,0,0,128,128,hdcMemory,0,0,SRCCOPY);
	DeleteDC(hdcMemory);

}
HBITMAP ChangeColor()
{
	TCHAR buffer[30];
	HDC hdc;
	
	wsprintf(buffer,"../image/skin/a%d.bmp",skin);
	//MessageBox(g_hMainWnd,buffer,"d",0);
	hdc= GetDC(g_hMainWnd);
	UpdateClock(g_hMainWnd,hdc);
	
	return (HBITMAP)LoadImage(g_hInst,buffer,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//UpdateClock(g_hMainWnd,hdc);

}
INT_PTR CALLBACK ClockDlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int i;
	switch(uMsg)
	{
	case WM_INITDIALOG:
		
		g_hMainWnd=hDlg;
		SetWindowPos(hDlg, HWND_TOPMOST,0,0,128,128,SWP_NOMOVE);  //Z-index topmost
		SetWindowText(hDlg,"������ʱ��");//title
		SendMessage(hDlg,WM_SETICON,ICON_SMALL,(LPARAM)(LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1))));
		SendMessage(hDlg,WM_SETICON,ICON_BIG,(LPARAM)(LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1))));
		//��Ӳ���
		SetWindowLong(hDlg,GWL_EXSTYLE,GetWindowLong(hDlg,GWL_EXSTYLE)|WS_EX_LAYERED);   
		//��ĵط�Ϊ͸��ɫ
		if(skin == 1)
		SetLayeredWindowAttributes(hDlg,RGB(255,0,128),0,LWA_COLORKEY);
		else
		SetLayeredWindowAttributes(hDlg,RGB(0,0,0),0,LWA_COLORKEY);
		if(fopen_s(&file,"../setup/setup.ini","r+")!=0)
		{
			MessageBox(hDlg,"��ʼ��ʧ��","ERROR",MB_ICONERROR);
			exit(0);
		}
		fscanf_s(file,"%d",&skin,1);
		fclose(file);
		wsprintf(buffer,"../image/skin/a%d.bmp",skin);
		//MessageBox(hDlg,buffer,"sd",0);
		DeleteObject(m_hBkBmp);
		m_hBkBmp = (HBITMAP)LoadImage(g_hInst,buffer,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);	
		if(fopen_s(&file,"../setup/full.ini","r+")!=0)
		{
			MessageBox(hDlg,"��ʼ��ʧ��","ERROR",MB_ICONERROR);
			exit(0);
		}
		fgets(full,10,file);
		remindfull = atoi(full);
		fclose(file);
		SetTimer(hDlg,1,500,NULL);
		break;
	case WM_TIMER:
		{
			SYSTEMTIME datetime;
			HDC hdc;
			
			hdc= GetDC(hDlg);
			GetLocalTime(&datetime);
			sunDay.nYear = datetime.wYear;
			sunDay.nMonth = datetime.wMonth;
			sunDay.nDay = datetime.wDay;
			SunToLunar(&sunDay,&lunarDay);
			
			if(datetime.wMinute == 0 && remindfull == 1) //���㱨ʱ
			{
				PlayOnFull(datetime.wHour);
			}
			//�ж�����
			if(datetime.wSecond == 0)
			{
				for(i = 0;i<alarmnum;i++)
				{
					if(datetime.wHour ==cur_alarm[i].hour && datetime.wMinute ==cur_alarm[i].minute &&datetime.wSecond ==0 && datetime.wMilliseconds <=499)//����
					{
	
					PlayAlarm(hDlg,i);
					
					}
				}
				//�жϼ�����
				
			}
			
			
			for(i=0;i<memorynum;i++)
			{
				if(cur_memory[i].is_tell == 1)
				{
					if(cur_memory[i].is_sun == 1)
					{
						if(lunarDay.nMonth ==cur_memory[i].month && lunarDay.nDay == cur_memory[i].day && datetime.wHour == cur_memory[i].hour && datetime.wMinute == cur_memory[i].minute &&datetime.wSecond == 0&&datetime.wMilliseconds<=499)
							PlayMemory(hDlg,i);
					}
					else
					{
						if(datetime.wMonth ==cur_memory[i].month && datetime.wDay == cur_memory[i].day && datetime.wHour == cur_memory[i].hour && datetime.wMinute == cur_memory[i].minute &&datetime.wSecond == 0&&datetime.wMilliseconds<=499)
						{
							PlayMemory(hDlg,i);
						}
					}
				}
			}
			
			if(skin == 1)
			SetLayeredWindowAttributes(hDlg,RGB(255,0,128),0,LWA_COLORKEY);
			else
			SetLayeredWindowAttributes(hDlg,RGB(0,0,0),0,LWA_COLORKEY);
			InvalidateRect(hDlg,NULL,FALSE);
			DeleteObject(m_hBkBmp);
			m_hBkBmp = ChangeColor();
			UpdateClock(hDlg,hdc);
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg,&ps);
			UpdateClock(hDlg,hdc);
			EndPaint(hDlg,&ps);
		}
		break;
	case WM_LBUTTONDOWN:
		PostMessage(hDlg,WM_NCLBUTTONDOWN,HTCAPTION,lParam); 
		break;
	case WM_RBUTTONUP:
		{
			HMENU hParentMenu,hSubMenu;

			POINT pt={LOWORD(lParam),HIWORD(lParam)};
			ClientToScreen(hDlg,&pt);

			hParentMenu = LoadMenu(g_hInst,MAKEINTRESOURCE(IDR_MENU));
			hSubMenu=GetSubMenu(hParentMenu,0);
			TrackPopupMenu(hSubMenu,TPM_LEFTALIGN,pt.x,pt.y,0,hDlg,NULL);
		}
		break;
	case WM_COMMAND:
		{
			
			if(LOWORD(wParam)==ID_EXIT)
			{
				if(HIWORD(wParam)==BN_CLICKED)
					EndDialog(hDlg,0);
			}
			else if(LOWORD(wParam)==ID_CALENDAR)
			{
				if(HIWORD(wParam)==BN_CLICKED)
					ShowCalendarDlg();
			}
			else if(LOWORD(wParam)==ID_SETUP)//����
			{
				if(HIWORD(wParam)==BN_CLICKED)
					ShowSetupDlg();
			}
			else if(LOWORD(wParam)==ID_MEM) //������
			{
				if(HIWORD(wParam)==BN_CLICKED)
					ShowMemDlg();
			}
			else if(LOWORD(wParam)==ID_ALARM)//����
			{
				if(HIWORD(wParam)==BN_CLICKED)
					ShowAlarmDlg();
			}
			else if(LOWORD(wParam)==ID_SPECIAL)//���Ի�
			{
				if(HIWORD(wParam)==BN_CLICKED)
					ShowSpecialDlg();
			}
			else if(LOWORD(wParam)==ID_ABOUT)//����
			{
				if(HIWORD(wParam)==BN_CLICKED)
					ShowAboutDlg();
			}
			else if(LOWORD(wParam)==ID_RED && fopen_s(&file,"../setup/setup.ini","w+")==0)//��ɫ
			{
				if(HIWORD(wParam)==BN_CLICKED)
				{
					skin = 4;
					fprintf_s(file,"%d",skin);
					
					fclose(file);
				}
			}
			else if(LOWORD(wParam)==ID_BLUE && fopen_s(&file,"../setup/setup.ini","w+")==0 )//��ɫ
			{
				if(HIWORD(wParam)==BN_CLICKED)
				{
					skin = 1;
					fprintf_s(file,"%d",skin);
					
					fclose(file);
				}
			}
			else if(LOWORD(wParam)==ID_GREEN && fopen_s(&file,"../setup/setup.ini","w+")==0)//��ɫ
			{
				if(HIWORD(wParam)==BN_CLICKED)
				{
					skin = 3;
					fprintf_s(file,"%d",skin);
					
					fclose(file);
				}
			}
			else if(LOWORD(wParam)==ID_YELLOW && fopen_s(&file,"../setup/setup.ini","w+")==0)//��ɫ
			{
				if(HIWORD(wParam)==BN_CLICKED)
				{
					skin = 2;
					fprintf_s(file,"%d",skin);
					
					fclose(file);
				}
			}
				//m_hBkBmp = ChangeColor();	
			
		}
		return FALSE;//����WM_COMMAND��Ϣ��Ӧ������0
	case WM_CLOSE:
		{
			KillTimer(hDlg,1);
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK AboutProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		
		hwnd = GetDlgItem(hDlg,IDC_ABOUT_STATIC);
		SetWindowText(hwnd,_T("���������Գ���\n�����ණ"));
		//hdc = GetDC(hwnd);
		//SetTextColor(hdc,RGB(100,100,100));
		//TextOut(hdc,100,100,_T("���������Գ���"),_tcslen(_T("���������Գ���")));
		//ReleaseDC(hDlg,hdc);
		break;
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==IDOK)
					EndDialog(hDlg,0);
			}
		}
		return FALSE;//����WM_COMMAND��Ϣ��Ӧ������0
	case WM_PAINT:
		
	
		break;
	case WM_LBUTTONDOWN:
		PostMessage(hDlg,WM_NCLBUTTONDOWN,HTCAPTION,lParam); 
		break;
	default:
		return FALSE;
	}
	return TRUE;

}

INT_PTR ShowClockDlg()
{
	return DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DLG_CLOCK),0,ClockDlgProc);
}
INT_PTR ShowAboutDlg()
{
	return DialogBox(g_hInst,MAKEINTRESOURCE(DLG_ABOUT),0,AboutProc);
}
