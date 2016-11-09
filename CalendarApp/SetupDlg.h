#pragma once
#define C_PAGES 3 
 
typedef struct tag_dlghdr { 
    HWND hwndTab;       // tab control 
    HWND hwndDisplay;   // current child dialog box 
    RECT rcDisplay;     // display rectangle for the tab control 
    DLGTEMPLATE *apRes[C_PAGES]; 
} DLGHDR; 
//创建并显示"设置对话框"
INT_PTR ShowSetupDlg();
