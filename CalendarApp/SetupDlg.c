#include "public.h"
SYSTEMTIME Datetime;
HWND hwnd;
TCHAR buffer[100];
int temp;
int len;
INT_PTR CALLBACK SetupDlgProc(HWND hDlg,
								 UINT uMsg,
								 WPARAM wParam,
								 LPARAM lParam
								 )
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==IDCANCEL)
					EndDialog(hDlg,0);
				if(LOWORD(wParam)==IDOK_APPLY)
				{
					
					GetLocalTime(&Datetime);
					hwnd = GetDlgItem(hDlg,IDC_EDIT_YEAR);
					len = SendMessage(hwnd,WM_GETTEXT,(WPARAM)100,(LPARAM)buffer);
					temp = atoi(buffer);
					if(temp >=1901 && temp <=2099)
					Datetime.wYear = temp;

					hwnd = GetDlgItem(hDlg,IDC_EDIT_MONTH);
					len = SendMessage(hwnd,WM_GETTEXT,(WPARAM)100,(LPARAM)buffer);
					temp = atoi(buffer);
					if(temp >=1 && temp <=12)
					Datetime.wMonth = temp;

					hwnd = GetDlgItem(hDlg,IDC_EDIT_DAY);
					len = SendMessage(hwnd,WM_GETTEXT,(WPARAM)100,(LPARAM)buffer);
					temp = atoi(buffer);
					if(temp >=1 && temp <=31)
					Datetime.wDay = temp;

					hwnd = GetDlgItem(hDlg,IDC_EDIT_HOUR);
					len = SendMessage(hwnd,WM_GETTEXT,(WPARAM)100,(LPARAM)buffer);
					temp = atoi(buffer);
					if(temp >=1 && temp <=24)
					Datetime.wHour = temp;

					hwnd = GetDlgItem(hDlg,IDC_EDIT_MINUTE);
					len = SendMessage(hwnd,WM_GETTEXT,(WPARAM)100,(LPARAM)buffer);
					temp = atoi(buffer);
					if(temp >=1 && temp <=59)
					Datetime.wMinute= temp;
					
					SetLocalTime(&Datetime);
					EndDialog(hDlg,0);
				}
			}
		}
		return FALSE;//处理WM_COMMAND消息后，应当返回0
	case WM_LBUTTONDOWN:
		PostMessage(hDlg,WM_NCLBUTTONDOWN,HTCAPTION,lParam); 
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR ShowSetupDlg()
{
	return DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DLG_SETUP),
		g_hMainWnd,SetupDlgProc);
}

