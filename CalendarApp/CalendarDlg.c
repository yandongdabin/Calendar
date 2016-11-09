#include "public.h"
static HBITMAP  m_hBkBmp=NULL;

void UpdateCalendar(HWND hWnd,HDC hDC)
{
	RECT rc;
	HDC hdcMemory;
	HBITMAP hBmp ;
	HBRUSH  hBrush,hBrush1,hBrush2;
	GetClientRect(hWnd,&rc);
	hdcMemory=CreateCompatibleDC(hDC);
	hBmp = CreateCompatibleBitmap(hDC,rc.right,rc.bottom);
	SelectObject(hdcMemory,hBmp);

	//绘制窗体背景
	hBrush=CreateSolidBrush(RGB(0,255,0));
	SelectObject(hdcMemory,hBrush);
	Rectangle(hdcMemory,0,0,rc.right,rc.bottom);
	//DeleteObject(hBrush);
	hBrush=CreateSolidBrush(RGB(255,255,255));
	SelectObject(hdcMemory,hBrush);
	Rectangle(hdcMemory,358,50,509,346);
	hBrush=CreateSolidBrush(RGB(192,100,255));
	SelectObject(hdcMemory,hBrush);
	SelectObject(hdcMemory,m_hBkBmp);
	//设置文字背景为透明模式
	SetBkMode(hdcMemory,TRANSPARENT);
/*
	//测试文字输出
	SetTextColor(hdcMemory,RGB(0,0,255));//文字颜色
	TextOut(hdcMemory,50,50,"2010",4);//文字输出
	*/
	DrawCalendar(hdcMemory,rc.right,rc.bottom);

	BitBlt(hDC,0,0,rc.right,rc.bottom,hdcMemory,0,0,SRCCOPY);
	
	DeleteObject(hBrush);
	DeleteObject(hBmp);
	DeleteDC(hdcMemory);
}
INT_PTR CALLBACK CalendarDlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static HWND hwnd_y,hwnd_m;
	TCHAR buffer[20];
	TCHAR buffer1[20];
	char changebuffer[30];
	int len;
	int i;
	int curyear,curmonth;
	int temp;
	int to_judge;
	char back[100];
	switch(uMsg)
	{
	case WM_INITDIALOG:
		//SetWindowPos(hDlg, HWND_TOPMOST,600,200,128,128,SWP_SHOWWINDOW);  
		//SetWindowText(hDlg,"万年历时钟");
		
		hwnd_y =GetDlgItem(hDlg,IDC_YEAR);
		hwnd_m =GetDlgItem(hDlg,IDC_MONTH);
		SetWindowLong(hwnd_y,GWL_EXSTYLE,GetWindowLong(hDlg,GWL_EXSTYLE)|CBS_SORT|CBS_DROPDOWN);
		SetWindowLong(hwnd_m,GWL_EXSTYLE,GetWindowLong(hDlg,GWL_EXSTYLE)&~CBS_SORT);
		//Combobox_SetMinVisible(hwnd_y,10);

		//SendMessage(hwnd_y,CB_SHOWDROPDOWN,(WPARAM)TRUE,0);
		//SendMessage(hwnd_y,CB_SETITEMHEIGHT,-1,(LPARAM)100);
		SetTextColor(hDlg,RGB(255,0,0));
		for(i=1901;i<=2099;i++)
		{
			wsprintf(buffer,_T("%d"),i);
			SendMessage (hwnd_y, CB_ADDSTRING, 0,(LPARAM) buffer);
		}
		for(i=1;i<=12;i++)
		{
			wsprintf(buffer,_T("%2d"),i);
			SendMessage (hwnd_m, CB_ADDSTRING, 0,(LPARAM) buffer);
		}
		//SendMessage(hwnd_y,CB_SETCURSEL,(WPARAM)(cur_datetime.year-1901),0);
		//SendMessage(hwnd_m,CB_SETCURSEL,(WPARAM)(cur_datetime.month-1),0);
		SetWindowLong(hDlg,GWL_EXSTYLE,GetWindowLong(hDlg,GWL_EXSTYLE)|WS_EX_LAYERED);   
		//红的地方为透明色
		SetLayeredWindowAttributes(hDlg,RGB(255,0,128),0,LWA_COLORKEY);
		sprintf(back,"../image/season/%02d.bmp",cur_datetime.month);
		m_hBkBmp = (HBITMAP)LoadImage(g_hInst,back,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		break;
	case WM_TIMER:
		{
			HDC hdc= GetDC(hDlg);
			UpdateCalendar(hDlg,hdc);
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg,&ps);
			UpdateCalendar(hDlg,hdc);
			EndPath(hdc);
			

			SendMessage(hwnd_y,CB_SETCURSEL,(WPARAM)(cur_datetime.year-1901),0);
			SendMessage(hwnd_m,CB_SETCURSEL,(WPARAM)(cur_datetime.month-1),0);
		}
		break;
	case WM_LBUTTONDOWN:
		PostMessage(hDlg,WM_NCLBUTTONDOWN,HTCAPTION,lParam); 
		break;
	case WM_COMMAND:
		{			
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==IDCANCEL)
					EndDialog(hDlg,0);
				else
				{
					HDC hdc = GetDC(hDlg);
					CalendarButtonEvent(LOWORD(wParam));
					sprintf(back,"../image/season/%02d.bmp",cur_datetime.month);
					//MessageBox(hDlg,back,"s",0);
					DeleteObject(m_hBkBmp);
					m_hBkBmp = (HBITMAP)LoadImage(g_hInst,back,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
				
					UpdateCalendar(hDlg,hdc);
					//hwnd_y = GetDlgItem(hDlg,IDC_YEAR);
					//hwnd_m = GetDlgItem(hDlg,IDC_MONTH);
					CalendarSelChange();
					InvalidateRect(hDlg,NULL,FALSE);//更新显示
					SendMessage(hwnd_y,CB_SETCURSEL,(WPARAM)(cur_datetime.year-1901),0);
					SendMessage(hwnd_m,CB_SETCURSEL,(WPARAM)(cur_datetime.month-1),0);
				}
			}
			//处理组合框的消息
			else if(HIWORD(wParam)==CBN_SELCHANGE)
			{
				HDC hdc= GetDC(hDlg);
				cur_datetime.year = SendMessage(hwnd_y,CB_GETCURSEL,0,0);
				cur_datetime.month = SendMessage(hwnd_m,CB_GETCURSEL,0,0);
				sprintf(back,"../image/season/%02d.bmp",cur_datetime.month);
				//MessageBox(hDlg,back,"s",0);
				DeleteObject(m_hBkBmp);
				m_hBkBmp = (HBITMAP)LoadImage(g_hInst,back,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
				
				UpdateCalendar(hDlg,hdc);
				CalendarSelChange();
				InvalidateRect(hDlg,NULL,FALSE);
				
			}
			//处理组合框的文本
			else if(HIWORD(wParam) == CBN_EDITUPDATE)
			{
				
				hwnd_y =GetDlgItem(hDlg,IDC_YEAR);
				hwnd_m =GetDlgItem(hDlg,IDC_MONTH);
				ZeroMemory(changebuffer,20);
				//curyear=SendMessage(hwnd_y,CB_GETCURSEL,0,0);
				//curmonth=SendMessage(hwnd_m,CB_GETCURSEL,0,0);
				if(LOWORD(wParam)==IDC_YEAR)
				{
					//MessageBox(hDlg,"Invalid data","ERROR",0);
					temp=SendMessage(hwnd_y,WM_GETTEXT,(WPARAM)20,(LPARAM)buffer);
					if(temp==4)
					{
						//ComboBox_GetCueBannerText(hwnd_y,buffer,10);
						//MessageBox(hDlg,buffer,"we",0);
						to_judge = atoi(buffer);
						if(to_judge>=1901 && to_judge<=2099)
						{
						cur_datetime.year = to_judge;
						CalendarSelChange();
						InvalidateRect(hDlg,NULL,TRUE);
						}
						else
						{
							MessageBox(hDlg,"It must be 1901-2099","ERROR",MB_ICONERROR);
						}
					}
					else if(temp>4)
					{
						MessageBox(hDlg,"It must be 1901-2099","ERROR",MB_ICONERROR);
					}

				}
				else if(LOWORD(wParam)==IDC_MONTH)
				{
					//MessageBox(hDlg,"Invalid data","ERROR",0);
					
					temp=SendMessage(hwnd_m,WM_GETTEXT,(WPARAM)20,(LPARAM)buffer);
					if(temp==2)
					{
						//ComboBox_GetCueBannerText(hwnd_y,buffer,10);
						//MessageBox(hDlg,buffer,"we",0);
						//WideCharToMultiByte(CP_ACP,0,buffer,-1,changebuffer,20,NULL,NULL);//将UNICODE转成ANSI
						to_judge = atoi(buffer);
						if(to_judge>=1 && to_judge<=12)
						{
							HDC hdc = GetDC(hDlg);
							cur_datetime.month = to_judge;
							sprintf(back,"../image/season/%02d.bmp",cur_datetime.month);
							//MessageBox(hDlg,back,"s",0);
							DeleteObject(m_hBkBmp);
							m_hBkBmp = (HBITMAP)LoadImage(g_hInst,back,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
				
							UpdateCalendar(hDlg,hdc);
							CalendarSelChange();
							InvalidateRect(hDlg,NULL,TRUE);
						}
						else
						{
							MessageBox(hDlg,"It must be 1-12","ERROR",MB_ICONERROR);
						}
					}
					else if(temp>2)
					{
						MessageBox(hDlg,"It must be 1-12","ERROR",MB_ICONERROR);
					}

				}
				
			}
			
		}
		return FALSE;//处理WM_COMMAND消息后，应当返回0
	
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR ShowCalendarDlg()
{

	SYSTEMTIME DateTime;
	GetLocalTime(&DateTime);
	cur_datetime.year = DateTime.wYear;
	cur_datetime.month = DateTime.wMonth;
	cur_datetime.day = DateTime.wDay; 
	return DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DLG_CALENDAR),g_hMainWnd,CalendarDlgProc);
}