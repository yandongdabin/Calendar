#include "public.h"
Alarm cur_alarm[10];
int alarmnum = 0;

INT_PTR CALLBACK AlarmProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HWND hwnd;
	FILE *file;
	char _buffer[100];
	TCHAR szBuffer[10],szResult[100];
	char temp[100],tempbuffer[100];
	int hour,minute,style,sound;
	int len;
	int i;
	int index;//删除的索引
	switch(uMsg)
	{
	case WM_INITDIALOG:
		hwnd = GetDlgItem(hDlg,IDC_ALARM_HOUR);
		for(i=1;i<=24;i++)
		{
			wsprintf(szBuffer,_T("%2d"),i);
			SendMessage(hwnd,CB_ADDSTRING,0,(LPARAM)szBuffer);
		}
		hwnd = GetDlgItem(hDlg,IDC_ALARM_MINUTE);
		for(i=0;i<=59;i++)
		{
			wsprintf(szBuffer,_T("%2d"),i);
			SendMessage(hwnd,CB_ADDSTRING,0,(LPARAM)szBuffer);
		}
		hwnd = GetDlgItem(hDlg,IDC_ALARM_SOUND);
		for(i=1;i<=5;i++)
		{
			wsprintf(szBuffer,_T("%2d.mp3"),i);
			SendMessage(hwnd,CB_ADDSTRING,0,(LPARAM)szBuffer);
		}
		
		hwnd = GetDlgItem(hDlg,IDC_RADIO1);
		SendMessage(hwnd,BM_SETCHECK,(WPARAM)BST_CHECKED,0);

		hwnd = GetDlgItem(hDlg,IDC_ALARM_SHOW);

		SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM)_T("您的闹钟（双击删除）:\r\n"));
		alarmnum = 0;
		if(fopen_s(&file,"../setup/alarm.ini","r")!=NULL)
		{
			exit(0);
		}
		while(fgets(_buffer,100,file)!=NULL)
		{
			sscanf(_buffer,"%d %d %d %d",&cur_alarm[alarmnum].hour,&cur_alarm[alarmnum].minute,&cur_alarm[alarmnum].style,&cur_alarm[alarmnum].sound);
			memset(_buffer,0,sizeof(_buffer));
			alarmnum++;
			//printf("%d\n",num);
		}
		//hwnd = GetDlgItem(hDlg,IDC_MEM_SHOW);
		fclose(file);

		for(i=0;i<alarmnum;i++)
		{
			if(cur_alarm[i].style == 1)
			{
				strcpy(temp,"24小时内");
			}
			else
			{
				strcpy(temp,"每天重复");
			}
			memset(tempbuffer,0,sizeof(tempbuffer));
			sprintf(tempbuffer,"%02d:%02d 铃声:%d.mp3  ",cur_alarm[i].hour,cur_alarm[i].minute,cur_alarm[i].sound);
			
			strcat(tempbuffer,temp);
			SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM)tempbuffer);

		}

		break;
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==BN_CLICKED)
			{
				if(LOWORD(wParam)==IDCANCEL)
					EndDialog(hDlg,0);
				else if(LOWORD(wParam == IDC_ALARM_ADD))
				{
					hwnd =GetDlgItem(hDlg,IDC_ALARM_HOUR);
					hour = SendMessage(hwnd,CB_GETCURSEL,0,0)+1;
					
					hwnd =GetDlgItem(hDlg,IDC_ALARM_MINUTE);
					minute = SendMessage(hwnd,CB_GETCURSEL,0,0);
					hwnd =GetDlgItem(hDlg,IDC_RADIO1);
					if(SendMessage(hwnd,BM_GETCHECK,0,0)==BST_CHECKED)
						style = 1;//24小时内
					else style = 2;
					hwnd =GetDlgItem(hDlg,IDC_ALARM_SOUND);
					sound = SendMessage(hwnd,CB_GETCURSEL,0,0)+1;

					if(hour == 0 || sound == 0)
					{
						MessageBox(hDlg,"请选择时间","提示",0);
					}
					else
					{
					//wsprintf(szResult,"hour = %d minute = %d style = %d sound =%d",hour,minute,style,sound);
					cur_alarm[alarmnum].hour = hour;
					cur_alarm[alarmnum].minute = minute;
					cur_alarm[alarmnum].style = style;
					cur_alarm[alarmnum].sound = sound;
					
					
					if(style == 1)
					{
						strcpy(temp,"24小时内");
					}
					else
					{
						strcpy(temp,"每天重复");
					}
					memset(tempbuffer,0,sizeof(tempbuffer));
					sprintf(tempbuffer,"%02d:%02d 铃声:%d.mp3  ",hour,minute,sound);
					
					strcat(tempbuffer,temp);
					
					//SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM));
					//MessageBox(hDlg,"添加成功","闹铃提醒",0);
					hwnd =GetDlgItem(hDlg,IDC_ALARM_SHOW);
					if(LB_ERR ==SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM)tempbuffer))
					{
						MessageBox(hDlg,"error","s",0);
					}
					if(fopen_s(&file,"../setup/alarm.ini","a+")!=NULL)
					{
						exit(0);
					}
					memset(_buffer,0,sizeof(_buffer));
					sprintf(_buffer,"%d %d %d %d\n",hour,minute,style,sound);
					fputs(_buffer,file);
					alarmnum ++;
					fclose(file);
					}
				}
			}
			else if(HIWORD(wParam) == LBN_DBLCLK)//双击删除
			{
				hwnd = GetDlgItem(hDlg,IDC_ALARM_SHOW);
				index = SendMessage(hwnd,LB_GETCURSEL,0,0);
				if(index >0)
				SendMessage(hwnd,LB_DELETESTRING,(WPARAM)index,0);
				if(fopen_s(&file,"../setup/alarm.ini","w+")!=NULL)
				{
					exit(0);
				}
				//sprintf(te1,"%d",memorynum);
				//sprintf(te2,"%d",index);
				//strcpy(te1,te2);
				//MessageBox(hDlg,te1,"s",0);
				for(i=1;i<=alarmnum;i++)
				{
					if(i<index)
					{
					memset(_buffer,0,sizeof(_buffer));
					sprintf(_buffer,"%d %d %d %d\n",cur_alarm[i-1].hour,cur_alarm[i-1].minute,cur_alarm[i-1].style,cur_alarm[i-1].sound);
					fputs(_buffer,file);
					}
					if(i==index)
					{
						continue;
					}
					if(i>index)
					{
						memset(_buffer,0,sizeof(_buffer));
						sprintf(_buffer,"%d %d %d %d\n",cur_alarm[i-1].hour,cur_alarm[i-1].minute,cur_alarm[i-1].style,cur_alarm[i-1].sound);
						fputs(_buffer,file);
						cur_alarm[i-2].hour = cur_alarm[i-1].hour;
						cur_alarm[i-2].minute = cur_alarm[i-1].minute;
						cur_alarm[i-2].style = cur_alarm[i-1].style;
						cur_alarm[i-2].sound = cur_alarm[i-1].sound;
						//MessageBox(hDlg,_buffer,"s",0);
					}
					
				}
					alarmnum--;
					fclose(file);
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
INT_PTR ShowAlarmDlg()
{
	return DialogBox(g_hInst,MAKEINTRESOURCE(DLG_ALARM),0,AlarmProc);
}