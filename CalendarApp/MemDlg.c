#include "public.h"
static HBITMAP  m_hBkBmp=NULL;
Memory cur_memory[100];//��ǰ�ļ�����
int memorynum = 0;//��ǰ�ļ�������Ŀ


void UpdateMem(HWND hWnd,HDC hDC)
{
	
	HDC hdcMemory=CreateCompatibleDC(hDC);
	//���ƴ��屳��ͼƬ
	SelectObject(hdcMemory,m_hBkBmp);
	//�������ֱ���Ϊ͸��ģʽ
	SetBkMode(hdcMemory,TRANSPARENT);

	BitBlt(hDC,0,0,400,600,hdcMemory,0,0,SRCCOPY);
	DeleteDC(hdcMemory);

}
INT_PTR CALLBACK MemProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	//RECT rect,rect1;
	//GetWindowRect(g_hInst,&rect);
	//GetWindowRect(hDlg,&rect1);
	SYSTEMTIME Datetime;
	char te1[10],te2[10];
	FILE *file;//���ڳ�ʼ�����ļ�
	int i;
	int index;//ɾ��������
	TCHAR buffer[1000],szResult[1000],szFormer[1000],temp[1000],tempname[1000];
	char addName[100];
	HWND hwnd;
	int len;//��ȡ�ĳ���
	HDC hDC;
	HDC hdcMemory;
	int year,month,day,hour,minute,is_tell,is_sun;
	char _buffer[100];
	hour = 0;
	minute = 0;

	GetLocalTime(&Datetime);
	switch(uMsg)
	{
	case WM_INITDIALOG://��ʼ���Ի���
		//��ʾ����ͼƬ����
		SetWindowLong(hDlg,GWL_EXSTYLE,GetWindowLong(hDlg,GWL_EXSTYLE)|WS_EX_LAYERED);   
		//��ĵط�Ϊ͸��ɫ
		SetLayeredWindowAttributes(hDlg,RGB(255,0,128),0,LWA_COLORKEY);
		m_hBkBmp = (HBITMAP)LoadImage(g_hInst,"../image/1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);		

		//��ʼ��combo box����
		hwnd = GetDlgItem(hDlg,IDC_COMBO_YEAR);//��
		for(i=2012;i<=2020;i++)
		{
			wsprintf(buffer,_T("%d"),i);
			SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM) buffer);
		}
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(0),0);
		hwnd = GetDlgItem(hDlg,IDC_COMBO_MONTH);//��
		for(i=1;i<=12;i++)
		{
			wsprintf(buffer,_T("%2d"),i);
			SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM) buffer);
		}
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(Datetime.wMonth-1),0);
		hwnd = GetDlgItem(hDlg,IDC_COMBO_DAY);//��
		for(i=1;i<=31;i++)
		{
			wsprintf(buffer,_T("%2d"),i);
			SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM) buffer);
		}
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(Datetime.wDay-1),0);
		hwnd = GetDlgItem(hDlg,IDC_COMBO_HOUR);//Сʱ
		
		for(i=1;i<=24;i++)
		{
			wsprintf(buffer,_T("%2d"),i);
			SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM) buffer);
		}
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(Datetime.wHour-1),0);
		EnableWindow(hwnd,FALSE);//ʹСʱʧЧ
		


		hwnd = GetDlgItem(hDlg,IDC_COMBO_MINUTE);//����
		for(i=1;i<60;i++)
		{
			wsprintf(buffer,_T("%2d"),i);
			SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM) buffer);
		}
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(Datetime.wMinute-1),0);
		EnableWindow(hwnd,FALSE);//ʹ����ʧЧ
		hwnd = GetDlgItem(hDlg,IDC_SELECT);
		EnableWindow(hwnd,FALSE);//ʹ��ťʧЧ
		hwnd = GetDlgItem(hDlg,IDC_COM1);
		//wsprintf(buffer,_T("%2d"),i);
		SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM)_T("������"));
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(0),0);
		hwnd = GetDlgItem(hDlg,IDC_COM2);
		SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM)_T("����"));
		SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM)_T("ũ��"));
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(0),0);
		hwnd = GetDlgItem(hDlg,IDC_COM3);
		SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM)_T("���ѿ�"));
		SendMessage (hwnd, CB_ADDSTRING, 0,(LPARAM)_T("���ѹ�"));
		SendMessage(hwnd,CB_SETCURSEL,(WPARAM)(0),0);
		
		hwnd = GetDlgItem(hDlg,IDC_MEM_SHOW);
		//SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE)|~LBS_SORT);

		SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM)_T("���ļ�������:\r\n"));
		//SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM)buffer);
		memorynum = 0;
		if(fopen_s(&file,"../setup/mem.ini","r")!=NULL)
		{
			exit(0);
		}
		while(fgets(_buffer,100,file)!=NULL)
		{
			sscanf(_buffer,"%d %d %d %d %d %d %d %s",&cur_memory[memorynum].year,&cur_memory[memorynum].month,&cur_memory[memorynum].day,&cur_memory[memorynum].hour,&cur_memory[memorynum].minute,&cur_memory[memorynum].is_sun,&cur_memory[memorynum].is_tell,cur_memory[memorynum].name);
			memset(_buffer,0,sizeof(_buffer));
			memorynum++;
			//printf("%d\n",num);
		}
		//hwnd = GetDlgItem(hDlg,IDC_MEM_SHOW);
		fclose(file);
						
		
		for(i=0;i<memorynum;i++)
		{
			strcpy(tempname,cur_memory[i].name);
			if(cur_memory[i].is_sun)
			{
				wsprintf(szResult,"\r\nũ�� %d��%d��%d��",cur_memory[i].year,cur_memory[i].month,cur_memory[i].day);
			}
			else
			{
				wsprintf(szResult,"\r\n���� %d��%d��%d��",cur_memory[i].year,cur_memory[i].month,cur_memory[i].day);
			}
			if(cur_memory[i].is_tell)
			{
				wsprintf(temp,"  ����ʱ��:%dʱ%d��\r\n",cur_memory[i].hour,cur_memory[i].minute);
			}
				else
			{
				wsprintf(temp,"  ������\r\n");
			}
			strcat(szResult,temp);
			strcat(tempname,szResult);
			SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM)tempname);

		}

		return FALSE;
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==IDCANCEL)
					EndDialog(hDlg,0);
				else if(LOWORD(wParam == IDC_ADD))
				{
					//do something
					hour = 0;//��ʼ��ʱ��Ϊ0
					minute = 0;
					hwnd = GetDlgItem(hDlg,IDC_EDIT_MEM);
					len = SendMessage(hwnd,WM_GETTEXT,(WPARAM)1000,(LPARAM)buffer);//�õ���Ϣ
					
					if(len == 0)
					{
						MessageBox(hDlg,"�����������","ERROR",MB_ICONERROR);
					}
					else
					{
					//wsprintf(buffer,_T("%d"),len);
						//cur_memory = (Memory*)malloc(sizeof(Memory)*10);
						strcpy(cur_memory[memorynum].name,buffer);
						hwnd = GetDlgItem(hDlg,IDC_COMBO_YEAR);
						year = SendMessage(hwnd,CB_GETCURSEL,0,0)+2012;
						hwnd = GetDlgItem(hDlg,IDC_COMBO_MONTH);
						month = SendMessage(hwnd,CB_GETCURSEL,0,0)+1;
						hwnd = GetDlgItem(hDlg,IDC_COMBO_DAY);
						day = SendMessage(hwnd,CB_GETCURSEL,0,0)+1;
						
						hwnd = GetDlgItem(hDlg,IDC_COM2);
						is_sun = SendMessage(hwnd,CB_GETCURSEL,0,0);

						hwnd = GetDlgItem(hDlg,IDC_COM3);
						is_tell = SendMessage(hwnd,CB_GETCURSEL,0,0);
						if(is_tell == 1)
						{
							hwnd = GetDlgItem(hDlg,IDC_COMBO_HOUR);
							hour = SendMessage(hwnd,CB_GETCURSEL,0,0)+1;
							hwnd = GetDlgItem(hDlg,IDC_COMBO_MINUTE);
							minute = SendMessage(hwnd,CB_GETCURSEL,0,0)+1;
						}

						hwnd = GetDlgItem(hDlg,IDC_MEM_SHOW);
						memset(szResult,0,sizeof(szResult));
						memset(temp,0,sizeof(temp));
						//SendMessage(hwnd,WM_GETTEXT,(WPARAM)1000,(LPARAM)szFormer);
						if(is_sun)
						{
							wsprintf(szResult,"\r\ũ�� %d��%d��%d��",year,month,day);
						}
						else
						{
							wsprintf(szResult,"\r\n���� %d��%d��%d��",year,month,day);
						}
						if(is_tell)
						{
							wsprintf(temp,"  ����ʱ��:%dʱ%d��\r\n",hour,minute);
						}
						else
						{
							wsprintf(temp,"  ������\r\n");
						}
						strcat(szResult,temp);
						strcat(buffer,szResult);

						hwnd = GetDlgItem(hDlg,IDC_MEM_SHOW);

						SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM)buffer);
						//if(is_tell == 1)
						//{
							cur_memory[memorynum].year = year;
							cur_memory[memorynum].month = month;
							cur_memory[memorynum].day =day;
							cur_memory[memorynum].hour = hour;
							cur_memory[memorynum].minute = minute;
							cur_memory[memorynum].is_sun = is_sun;
							cur_memory[memorynum].is_tell = is_tell;
							memorynum ++;
							if(fopen_s(&file,"../setup/mem.ini","a+")!=NULL)
							{
								exit(0);
							}
							memset(_buffer,0,sizeof(_buffer));
							sprintf(_buffer,"%d %d %d %d %d %d %d %s\n",year,month,day,hour,minute,is_sun,is_tell,cur_memory[memorynum-1].name);
							fputs(_buffer,file);
							fclose(file);
						//}
						//else
						//{
							
						//}
						//sprintf(te1,"%d",memorynum);
						//MessageBox(hDlg,te1,"22",0);
						
						MessageBox(hDlg,_T("��ӳɹ�"),_T("����"),0);
						//EndDialog(hDlg,0);
					}
				}
				else if(LOWORD(wParam)==IDC_MEM_DELETE)
				{
					hwnd = GetDlgItem(hDlg,IDC_MEM_SHOW);
					index = SendMessage(hwnd,LB_GETCURSEL,0,0);
					if(index >0)
					SendMessage(hwnd,LB_DELETESTRING,(WPARAM)index,0);
				if(fopen_s(&file,"../setup/mem.ini","w+")!=NULL)
				{
					exit(0);
				}
				//MessageBox(hDlg,te1,"s",0);
				for(i=1;i<=memorynum;i++)
				{
					if(i<index)
					{
					memset(_buffer,0,sizeof(_buffer));
					sprintf(_buffer,"%d %d %d %d %d %d %d %s\n",cur_memory[i-1].year,cur_memory[i-1].month,cur_memory[i-1].day,cur_memory[i-1].hour,cur_memory[i-1].minute,cur_memory[i-1].is_sun,cur_memory[i-1].is_tell,cur_memory[i-1].name);
					//MessageBox(hDlg,_buffer,"s",0);
					fputs(_buffer,file);
					}
					if(i==index)
					{
						continue;
					}
					if(i>index)
					{
						memset(_buffer,0,sizeof(_buffer));
						sprintf(_buffer,"%d %d %d %d %d %d %d %s\n",cur_memory[i-1].year,cur_memory[i-1].month,cur_memory[i-1].day,cur_memory[i-1].hour,cur_memory[i-1].minute,cur_memory[i-1].is_sun,cur_memory[i-1].is_tell,cur_memory[i-1].name);
						fputs(_buffer,file);
						cur_memory[i-2].year = cur_memory[i-1].year;
						cur_memory[i-2].month = cur_memory[i-1].month;
						cur_memory[i-2].day = cur_memory[i-1].day;
						cur_memory[i-2].hour = cur_memory[i-1].hour;
						cur_memory[i-2].minute = cur_memory[i-1].minute;
						cur_memory[i-2].is_sun = cur_memory[i-1].is_sun;
						cur_memory[i-2].is_tell = cur_memory[i-1].is_tell;
						strcpy(cur_memory[i-2].name,cur_memory[i-1].name);
						//MessageBox(hDlg,_buffer,"s",0);
					}
					
				}
				memorynum--;	
				fclose(file);
				}
				else if(LOWORD(wParam)==IDC_MEM_CHANGE)
				{
					//ShowChangeDlg();
				}
			}
			else if(HIWORD(wParam)==CBN_SELCHANGE)//�жϰ�ť��״̬
			{
				if(LOWORD(wParam) == IDC_COM3)
				{
					if(SendMessage((HWND)lParam,CB_GETCURSEL,0,0) == 1)
					{
						hwnd = GetDlgItem(hDlg,IDC_COMBO_HOUR);
						EnableWindow(hwnd,TRUE);
						hwnd = GetDlgItem(hDlg,IDC_COMBO_MINUTE);
						EnableWindow(hwnd,TRUE);
						hwnd = GetDlgItem(hDlg,IDC_SELECT);
						EnableWindow(hwnd,TRUE);

					}
					else
					{
						hwnd = GetDlgItem(hDlg,IDC_COMBO_HOUR);
						EnableWindow(hwnd,FALSE);
						hwnd = GetDlgItem(hDlg,IDC_COMBO_MINUTE);
						EnableWindow(hwnd,FALSE);
						hwnd = GetDlgItem(hDlg,IDC_SELECT);
						EnableWindow(hwnd,FALSE);
					}
				}

				
				
			}
			else if(HIWORD(wParam) == LBN_DBLCLK)//˫��ɾ��
			{
				hwnd = GetDlgItem(hDlg,IDC_MEM_SHOW);
				index = SendMessage(hwnd,LB_GETCURSEL,0,0);
				if(index >0)
				SendMessage(hwnd,LB_DELETESTRING,(WPARAM)index,0);
				

				if(fopen_s(&file,"../setup/mem.ini","w+")!=NULL)
				{
					exit(0);
				}
				sprintf(te1,"%d",memorynum);
				sprintf(te2,"%d",index);
				strcpy(te1,te2);
				//MessageBox(hDlg,te1,"s",0);
				for(i=1;i<=memorynum;i++)
				{
					if(i<index)
					{
					memset(_buffer,0,sizeof(_buffer));
					sprintf(_buffer,"%d %d %d %d %d %d %d %s\n",cur_memory[i-1].year,cur_memory[i-1].month,cur_memory[i-1].day,cur_memory[i-1].hour,cur_memory[i-1].minute,cur_memory[i-1].is_sun,cur_memory[i-1].is_tell,cur_memory[i-1].name);
					//MessageBox(hDlg,_buffer,"s",0);
					fputs(_buffer,file);
					}
					if(i==index)
					{
						continue;
					}
					if(i>index)
					{
						memset(_buffer,0,sizeof(_buffer));
						sprintf(_buffer,"%d %d %d %d %d %d %d %s\n",cur_memory[i-1].year,cur_memory[i-1].month,cur_memory[i-1].day,cur_memory[i-1].hour,cur_memory[i-1].minute,cur_memory[i-1].is_sun,cur_memory[i-1].is_tell,cur_memory[i-1].name);
						fputs(_buffer,file);
						cur_memory[i-2].year = cur_memory[i-1].year;
						cur_memory[i-2].month = cur_memory[i-1].month;
						cur_memory[i-2].day = cur_memory[i-1].day;
						cur_memory[i-2].hour = cur_memory[i-1].hour;
						cur_memory[i-2].minute = cur_memory[i-1].minute;
						cur_memory[i-2].is_sun = cur_memory[i-1].is_sun;
						cur_memory[i-2].is_tell = cur_memory[i-1].is_tell;
						strcpy(cur_memory[i-2].name,cur_memory[i-1].name);
						//MessageBox(hDlg,_buffer,"s",0);
					}
					
				}
					memorynum--;
					fclose(file);


			}
		}
		return FALSE;//����WM_COMMAND��Ϣ��Ӧ������0
	case WM_LBUTTONDOWN:
		PostMessage(hDlg,WM_NCLBUTTONDOWN,HTCAPTION,lParam); 
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg,&ps);
			UpdateMem(hDlg,hdc);
			EndPaint(hDlg,&ps);
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;

}


INT_PTR ShowMemDlg()
{
	return DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DLG_MEM),0,MemProc);
}
