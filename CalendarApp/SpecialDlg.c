#include "public.h"
FILE *file;
char buffer[10];
INT_PTR CALLBACK SpecialProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HWND hwnd;
	switch(uMsg)
	{
	case WM_INITDIALOG:
		//DoPropertySheet(hDlg);
		hwnd = GetDlgItem(hDlg,IDC_FULL);
		SendMessage(hwnd,CB_ADDSTRING,0,(LPARAM)_T("开"));
		SendMessage(hwnd,CB_ADDSTRING,0,(LPARAM)_T("关"));
		if(remindfull == 0)
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(0),0);
		else
		{
			SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(1),0);
		}
		break;
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==IDCANCEL)
					EndDialog(hDlg,0);
				if(LOWORD(wParam == IDOK))
				{
					hwnd = GetDlgItem(hDlg,IDC_FULL);
					if(SendMessage(hwnd,CB_GETCURSEL,0,0)==1)
					{
						remindfull = 1;
						
					}
					else
					{
						remindfull = 0;
					}
					fopen_s(&file,"../setup/full.ini","w+");
					sprintf(buffer,"%d",remindfull);
					fputs(buffer,file);
					fclose(file);
					
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
INT_PTR ShowSpecialDlg()
{
	return DialogBox(g_hInst,MAKEINTRESOURCE(DLG_SPECIAL),0,SpecialProc);
}

