#include "public.h"




HINSTANCE g_hInst;
unsigned int nCurrentYear=0;
unsigned int nCurrentMonth=0;
unsigned int nCurrentDay=0;
curDay cur_datetime;
stDateTime _psunDay;
int remindfull;
TCHAR lunarmonth[12][6]={TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("ʮ��"),TEXT("ʮһ��"),TEXT("����")};
TCHAR lunarday[30][6]={TEXT("��һ"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("����"),TEXT("��ʮ"),TEXT("ʮһ"),
TEXT("ʮ��"),TEXT("ʮ��"),TEXT("ʮ��"),TEXT("ʮ��"),TEXT("ʮ��"),TEXT("ʮ��"),TEXT("ʮ��"),TEXT("ʮ��"),TEXT("��ʮ"),TEXT("إһ"),TEXT("إ��"),TEXT("إ��"),TEXT("إ��"),TEXT("إ��"),
TEXT("إ��"),TEXT("إ��"),TEXT("إ��"),TEXT("إ��"),TEXT("��ʮ")};
//�����񣬴洢1901��-2099���ũ����Ϣ��ÿ��Ĵ�С�¡�������Ϣ���������ڵĹ�������
unsigned int LunarCalendarTable[199] = 
{
	0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/
	0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/
	0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/
	0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/   
	0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/
	0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/
	0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/
	0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/
	0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB,/*1981-1990*/
	0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/
	0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/
	0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/
	0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/
	0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/
	0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/
	0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/
	0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/
	0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/
	0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/
	0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/
};

char* TianGanDizhi[60]=
{
	"����", "�ҳ�","����","��î","�쳽","����","����","��δ","����","����",
	"����","�Һ�","����","����","����","��î","����","����","����","��δ",
	"����","����","����","����","����","�ѳ�","����","��î","�ɳ�","����",
	"����","��δ","����","����","����","�Ѻ�","����","����","����","��î",
	"�׳�","����","����","��δ","����","����","����","����","����","���",
	"����","��î","����","����","����","��δ","����","����","����","�ﺥ "
};
char* TianGanMonth[10]={"����","����","����","����","����","����","����","����","����","����"};
TCHAR weekday[7][6]={TEXT("������"),TEXT("����һ"),TEXT("���ڶ�"),TEXT("������"),TEXT("������"),TEXT("������"),TEXT("������")};

//�����񣬴洢ÿ��1����Ԫ�������������������꣩
unsigned int MonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

//�����û�Ҫ��ʾ���ꡢ�¡���

const int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
//�ж�ĳ���Ƿ�Ϊ��������

int IsLeapYear(WORD iYear)
{
	if(iYear%4==0 &&iYear%100!=0)
		return 1;
	if(iYear%400==0)
		return 1;
	return 0;
}
 
//��������תũ�����ڵĺ���
void SunToLunar(const stDateTime* pSunDay,stDateTime* pLunarDay)
{
	int i=0;
	int SunDiff=0;
	int SpringDiff=0;

	int nSpringYear=pSunDay->nYear;
	int nSpringMonth=1;
	int nSpringDay=0;
	int a=0;
	int flag = 1;
	//���㵱ǰ�������뵱��Ԫ��������
	SunDiff = MonthAdd[pSunDay->nMonth-1] + pSunDay->nDay - 1;
	if(IsLeapYear(pSunDay->nYear) && (pSunDay->nMonth > 2) )//���������Ҵ����£������ټ�
		SunDiff++;

	//���㴺�����ڹ�������Ԫ����������ͨ��������㵱��Ĵ������ڵĹ������ڣ�
	if(((LunarCalendarTable[pSunDay->nYear - 1901] & 0x60)>>5)==1)//�������ڹ�����
		SpringDiff= (LunarCalendarTable[pSunDay->nYear-1901]&0x1F)-1;
	else//�������ڹ�����
		SpringDiff= (LunarCalendarTable[pSunDay->nYear-1901]&0x1F)-1+31;

	//SunDiff��SpringDiff�Ĳ���ǵ�ǰ�������봺�ڵ�����

	if(SunDiff>=SpringDiff)//�������ڴ��ں�
	{
		int x = SunDiff - SpringDiff;
		int bLunar = (LunarCalendarTable[nSpringYear - 1901] & 0xF00000)>>20;//�����·�

		i=0;
		nSpringMonth=1;

		for(;;)
		{
			a = (LunarCalendarTable[pSunDay->nYear-1901] & (0x80000>>i));//�����С��
			if(a==0)
				a=29;
			else
				a=30;
			if(x<a)
				break;
			x =x - a;
			i++;
			nSpringMonth++;
		}
		nSpringDay =x+1;
		//���������
		if(nSpringMonth>bLunar && bLunar>0)
			nSpringMonth--;
	}
	else//�������ڴ���ǰ
	{

		int x = SpringDiff-SunDiff;
		int nShift=0;

		int bLunar = (LunarCalendarTable[nSpringYear - 1901-1] & 0xF00000)>>20;//�����·�

		i=0;
		nSpringYear--;//��Ҫ��һ���ũ����Ϣ
		nSpringMonth=12;//�����һ���¿�ʼ����

		if (bLunar == 0)//���û������
			nShift = 0x100;
		else
			nShift = 0x80;

		for(;;)
		{
			a = (LunarCalendarTable[nSpringYear-1901] & (nShift<<i));//�����С��
			if(a==0)
				a=29;
			else
				a=30;

			if(x<=a)
			{
				x = a-x;
				break;
			}
			x =x - a;
			i++;
			nSpringMonth--;
		}
		nSpringDay =x+1;

		if(nSpringMonth<bLunar && bLunar>0)
			nSpringMonth++;
	}
	pLunarDay->nYear = nSpringYear;
	pLunarDay->nMonth= nSpringMonth;
	pLunarDay->nDay  = nSpringDay;
}

int GetCountDay(const stDateTime *pLunarDay)
{
	int year,month,day,leapMonth;
	int total;
	year = pLunarDay->nYear;
	month = pLunarDay->nMonth;
	day = pLunarDay->nDay;
	leapMonth = (LunarCalendarTable[year-1901] & 0xF00000) >>20;
	if(leapMonth == 0 || month <=leapMonth)
	{
		total = LunarCalendarTable[year-1901] & (0x080000 >>(month-1));
	}
	else
	{
		total = LunarCalendarTable[year-1901] &(0x080000>>(month));
	}
	if(total ==0)return 29;
	else return 30;

}
//���ݹ������ڻ������
int GetDayOfWeek(const stDateTime* pSunDay)
{
	//����̩�չ�ʽ
	//nWeek = [nYear1��4] - 2*nYear1 + nYear2 + [nYear2��4] + [26(nMonth+1)��10] + nDay - 1
	int nWeek=0;
	int nYear1=pSunDay->nYear/100;//���ǰ��λ����
	int nYear2=pSunDay->nYear%100;//��ĺ���λ����
	int nDay=pSunDay->nDay;  //������

	int nMonth=pSunDay->nMonth;//����������������·������1�»�2�£�
	                           //��Ӧ��Ϊ��һ���13�»�14�£�
	                           //Ҳ���ǹ�ʽ��nMonth��ȡֵ��Χ�Ǵ�3��14�����Ǵ�1��12

	if(nMonth==1 || nMonth==2)
	{
		nMonth=12+nMonth;
		nYear1=(pSunDay->nYear-1)/100;//���ǰ��λ����
		nYear2=(pSunDay->nYear-1)%100;//��ĺ���λ����
	}
	
	nWeek = nYear1/4 - 2*nYear1 + nYear2 + nYear2/4 + (26*(nMonth+1))/10 + nDay - 1;
	nWeek = nWeek%7;
	return nWeek < 0 ? (nWeek+7):nWeek;
}
//���ݹ�����õ�ũ����֧��
char* GetGanZhi(int nYear)
{
	int temp;
	temp=nYear%60-3;
	if(temp<=0)temp+=60;
	return TianGanDizhi[temp-1];
}

char *GetGanZhiMonth(int nYear,int nMonth)//��Ԫ����·�
{	
	int i=0,j=nMonth-1;
	char *January;
	i=(nYear%5-2)*2-1;
	if(i<0){i+=10;}
	January=TianGanMonth[i-1];
	while(i++<60)//���µ������
	{
		if(TianGanDizhi[i]==January){
			break;
		}
	}
	while(j--){//���������㵽����
		i++;
	}
	if(i>60)i-=60;
	return TianGanDizhi[i-1];
}

//Windows������ں���
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	g_hInst = hInstance;
    ShowClockDlg();
}



void DrawCalendar(HDC hDC,int nWidth,int nHeight)
{
	stDateTime SunDay,LunarDay;
	HFONT oldFont,newFont,newFont1;
	const int xOrg=10;
	const int yOrg=50;
	const int xRight  = nWidth - 150;
	const int yBottom = nHeight- 20;
	int line,week,len;
	TCHAR szTemp[20];
	const int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	const TCHAR *sText[]={_T("��"),_T("һ"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��")};
	int i=0;
	int nVer=0;
	int ver1 = (yBottom-yOrg-25)/6;
	int ver2 = (xRight-xOrg)/7;
	int lunarMonth,lunarDay;
	int CountDay;
	COLORREF oldColor;
	int add;
	SYSTEMTIME DateTime;
	char tianganyear[10],tianganmonth[10];
	//���������ľ��α���
    Rectangle(hDC,xOrg,yOrg,xRight,yBottom);
    
	//���ơ����ڡ������
	MoveToEx(hDC,xOrg,yOrg+25,NULL);
	LineTo(hDC,xRight,yOrg+25);

	//ʣ���ܸ߶�
	nVer = yBottom-yOrg-25;
	nVer = nVer/6;

	//���ơ�ÿ�ա��ĸ߶���
	for(i=0;i<5;i++)
	{
		MoveToEx(hDC,xOrg,yOrg+25+nVer*(i+1),NULL);
		LineTo(hDC,xRight,yOrg+25+nVer*(i+1));
	}
	
	//ʣ���ܿ��
	nVer = xRight-xOrg;
	nVer = nVer/7;
	//���ơ�ÿ�ա��Ŀ����
	for(i=0;i<6;i++)
	{
		MoveToEx(hDC,xOrg+nVer*(i+1),yOrg,NULL);
		LineTo(hDC,xOrg+nVer*(i+1),yBottom);
	}

	//���ơ����ڡ�������ڵ�����

	SetTextColor(hDC,RGB(255,0,0));
	TextOut(hDC,xOrg+20,yOrg+6,sText[0],_tcslen(sText[0]));

	SetTextColor(hDC,RGB(0,0,0));
	for(i=1;i<=5;i++)
	{
		TextOut(hDC,xOrg+20+nVer*i,yOrg+6,sText[i],_tcslen(sText[i]));
	}

	SetTextColor(hDC,RGB(255,0,0));
	TextOut(hDC,xOrg+20+nVer*6,yOrg+6,sText[6],_tcslen(sText[6]));

	//���´����ǹ�����ũ�����㲢��ʾ
	if(nCurrentYear==0)
	{
		
		GetLocalTime(&DateTime);
		nCurrentYear = DateTime.wYear;
		nCurrentMonth= DateTime.wMonth;
		nCurrentDay =DateTime.wDay;
		cur_datetime.year = DateTime.wYear;
		cur_datetime.month = DateTime.wMonth;
		cur_datetime.day = DateTime.wDay;
	}
	GetLocalTime(&DateTime);
	SunDay.nYear  =  nCurrentYear;
	SunDay.nMonth =  nCurrentMonth;//nCurrentMonth;
	SunDay.nDay   =  nCurrentDay;//nCurrentDay;
	
	line = 1;
	SunDay.nDay = 1;
	week = GetDayOfWeek(&SunDay);
	//week = _sun(nCurrentYear,nCurrentMonth)+1;
	
	

	//���ݹ������ڻ��ũ������
	SunToLunar(&SunDay,&LunarDay);
	lunarMonth = LunarDay.nMonth;
	lunarDay = LunarDay.nDay;
	CountDay = GetCountDay(&LunarDay);
	//len = wsprintf(szTemp,TEXT("%d-%d-%d"),SunDay.nYear,SunDay.nMonth,SunDay.nDay,LunarDay.nDay);
	//TextOut(hDC,xOrg+10+nVer*7,yOrg+6,szTemp,len);
	add = 0;
	newFont=CreateFont(30,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	newFont1=CreateFont(10,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	
	oldFont = SelectObject(hDC,newFont);
	for(i=1;i<=month[SunDay.nMonth];i++)
	{
		
		SelectObject(hDC,newFont);
		if(week%7 ==0 || week%7 ==6)
		{
			SetTextColor(hDC,RGB(200,0,0));
		}
		else
		{
			SetTextColor(hDC,RGB(0,0,0));
		}
		
		len = wsprintf(szTemp,TEXT("%d"),i);
		TextOut(hDC,xOrg+(week%7)*ver2+20,line*ver1+yOrg-20,szTemp,len);
		SelectObject(hDC,newFont1);
		//���Ƶ�ǰ���ڴ�����Բ
		if(i==DateTime.wDay)
		{
			//Ellipse(hDC,
		}
		if(lunarDay == 1)
		{
			oldColor = SetTextColor(hDC,RGB(0,0,255));
			TextOut(hDC,xOrg+(week%7)*ver2+20,line*ver1+yOrg+12,lunarmonth[lunarMonth+add],4);
			if(add==0)add=1;
			SetTextColor(hDC,oldColor);
			
		}
		else
		{
			TextOut(hDC,xOrg+(week%7)*ver2+20+5,line*ver1+yOrg+12,lunarday[lunarDay-1],4);
		}
		
		lunarDay = lunarDay + 1;
		if(lunarDay > CountDay)lunarDay = 1;
		week++;
		if(week%7==0)
		line++;
	}
	DeleteObject(newFont);
	DeleteObject(newFont);
	newFont=CreateFont(15,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	
	oldFont = SelectObject(hDC,newFont);
	SetTextColor(hDC,RGB(255,0,51));
	
	

	//�����Ҳ���Ϣ�� ������������Ĺ̶����ڲ��ɱ� ת��Ϊϵͳ����
	SunDay.nYear  =  DateTime.wYear;
	SunDay.nMonth =  DateTime.wMonth;//nCurrentMonth;
	SunDay.nDay   =  DateTime.wDay;//nCurrentDay;
	len = wsprintf(szTemp,TEXT("%d-%d-%d"),DateTime.wYear,DateTime.wMonth,DateTime.wDay);
	SunDay.nDay   =  nCurrentDay;//nCurrentDay;
	week = GetDayOfWeek(&SunDay);
	
	SetTextColor(hDC,0x33FF33);
	TextOut(hDC,xOrg+8+nVer*7,yOrg+6,szTemp,len); //�����������
	SetTextColor(hDC,0x33FF66);
	TextOut(hDC,xOrg+90+nVer*7,yOrg+6,weekday[week],6);//����ܼ���Ϣ
	DeleteObject(newFont);
	newFont=CreateFont(200,40,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	//DeleteObject(newFont);
	SelectObject(hDC,newFont);
	SetTextColor(hDC,RGB(255,51,0));
	len = wsprintf(szTemp,TEXT("%02d"),DateTime.wDay);
	TextOut(hDC,xOrg+60+nVer*7-20,yOrg+20,szTemp,len);//�����д������
	DeleteObject(newFont);
	SelectObject(hDC,oldFont);
	newFont=CreateFont(15,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	SelectObject(hDC,newFont);
	SetTextColor(hDC,0x6600FF);
	SunToLunar(&SunDay,&LunarDay);
	TextOut(hDC,xOrg+30+nVer*7+5,yOrg+200,_T("ũ��: "),4);
	TextOut(hDC,xOrg+60+nVer*7+5,yOrg+200,lunarmonth[LunarDay.nMonth],4);
	TextOut(hDC,xOrg+90+nVer*7+5,yOrg+200,lunarday[LunarDay.nDay],4);
	
	//�����ɵ�֧
	strcpy(tianganyear,GetGanZhi(LunarDay.nYear));
	strcpy(tianganmonth,GetGanZhiMonth(SunDay.nYear,SunDay.nMonth));


	DeleteObject(newFont);
	newFont=CreateFont(15,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	SelectObject(hDC,newFont);
	SetTextColor(hDC,0x633FF);
	TextOut(hDC,xOrg+60+nVer*7,280,tianganyear,strlen(tianganyear));
	TextOut(hDC,xOrg+60+nVer*7+30,280,_T("��"),2);
	TextOut(hDC,xOrg+60+nVer*7,300,tianganmonth,strlen(tianganmonth));
	TextOut(hDC,xOrg+60+nVer*7+30,300,_T("��"),2);
	SelectObject(hDC,oldFont);
	
	DeleteObject(newFont);
	
}


void CalendarButtonEvent(UINT nID)
{
	SYSTEMTIME DateTime;
	if(nID==IDC_BTN_YEARUP)//�����"���"��ť	
	{
        nCurrentYear ++;
		cur_datetime.year ++;
	}
	else if(nID==IDC_BTN_YEARDOWN)
	{
		nCurrentYear --;
		cur_datetime.year --;
	}
	else if(nID == IDC_BTN_MONTHUP)
	{
		nCurrentMonth = nCurrentMonth+1;
		if(nCurrentMonth>12)
		{
			nCurrentMonth=1;
			nCurrentYear +=1;
		}
		cur_datetime.year = nCurrentYear;
		cur_datetime.month = nCurrentMonth;
	}
	else if(nID == IDC_BTN_MONTHDOWN)
	{
		nCurrentMonth = nCurrentMonth-1;
		if(nCurrentMonth<=0)
		{ 
			nCurrentMonth=12;
			nCurrentYear -=1;
		}
		cur_datetime.year = nCurrentYear;
		cur_datetime.month = nCurrentMonth;

	}
	else if(nID == IDC_BTN_TODAY)
	{
		GetLocalTime(&DateTime);
		nCurrentYear = DateTime.wYear;
		nCurrentMonth=DateTime.wMonth;
		cur_datetime.year = nCurrentYear;
		cur_datetime.month = nCurrentMonth;

	}
	//...
}
void CalendarSelChange()
{
	nCurrentYear = cur_datetime.year;
	nCurrentMonth = cur_datetime.month;
}

void DrawClockText(HDC hDC)
{
	//��õ�ǰϵͳ�ı���ʱ��
	SYSTEMTIME DateTime;
	HBITMAP hBitmapImag,hBitmapImag1 ;//��ʾλͼ������λͼ
	BITMAP bitmap;//��ȡλͼ����Ϣ
	HDC hdcMemImag;//compatibleDC������ʾ��Ф
	LONG cxBitmap,cyBitmap;
	stDateTime pSunDay,pLunarDay;
	int curHour,curMinute,curSec;
	int curYear,curMonth,curDay;
	int len;
	int curWeek;
	int ID;
	HPEN oldFont,newFont;
	TCHAR szBuffer[50];
	LOGFONT lf ;
	char tianganyear[10];
	char tianganmonth[10];
	GetLocalTime(&DateTime);
	curHour=DateTime.wHour;
	curMinute=DateTime.wMinute;
	curSec=DateTime.wSecond;
	curYear=DateTime.wYear;
	curMonth=DateTime.wMonth;
	curDay=DateTime.wDay;
	pSunDay.nYear=DateTime.wYear;
	pSunDay.nMonth=DateTime.wMonth;
	pSunDay.nDay=DateTime.wDay;
	curWeek = GetDayOfWeek(&pSunDay);//��õ�ǰ������
	SetTextColor(hDC,RGB(192,255,0));//������ɫ
	
	len = wsprintf(szBuffer,TEXT("%02d"),curHour);
	TextOut(hDC,35,50,szBuffer,len);//�������
	
	TextOut(hDC,50,50,TEXT(":"),1);//�������

	len = wsprintf(szBuffer,TEXT("%02d"),curMinute);
	TextOut(hDC,55,50,szBuffer,len);//�������
	
	TextOut(hDC,70,50,TEXT(":"),1);
	len = wsprintf(szBuffer,TEXT("%02d"),curSec);
	TextOut(hDC,75,50,szBuffer,len);//�������
	
	SetTextColor(hDC,RGB(0,255,0));
	TextOut(hDC,40,70,weekday[curWeek],6);//�������

	
	//������б����
	SetTextColor(hDC,RGB(100,0,200));
	newFont=CreateFont(15,8,300,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	oldFont=SelectObject(hDC,newFont);
	len = wsprintf(szBuffer,TEXT("%d"),curYear);
	TextOut(hDC,18,28,szBuffer,len);
	DeleteObject(newFont);
	newFont=CreateFont(15,8,3500,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	SelectObject(hDC,newFont);
	len = wsprintf(szBuffer,TEXT("%d"),curMonth);
	TextOut(hDC,65,9,szBuffer,len);
	DeleteObject(newFont);
	newFont=CreateFont(15,8,3150,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	SelectObject(hDC,newFont);
	len = wsprintf(szBuffer,TEXT("%d"),curDay);
	TextOut(hDC,97,17,szBuffer,len);
	DeleteObject(newFont);
	newFont=CreateFont(20,5,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����"); 
	SelectObject(hDC,newFont);
	
	//���ũ��
	SetTextColor(hDC,RGB(0,100,255));
	SunToLunar(&pSunDay,&pLunarDay);
	TextOut(hDC,42,30,lunarmonth[pLunarDay.nMonth-1],4);
	TextOut(hDC,62,30,lunarday[pLunarDay.nDay-1],6);
	//�����ɵ�֧

	strcpy(tianganyear,GetGanZhi(pLunarDay.nYear));
	strcpy(tianganmonth,GetGanZhiMonth(pSunDay.nYear,pSunDay.nMonth));
	DeleteObject(newFont);
	SetTextColor(hDC,0x0066FF);
	newFont = CreateFont(15,7,3000,0,0,0,0,0,0,0,0,0,0,"@����"); 
	SelectObject(hDC,newFont);
	TextOut(hDC,24,68,tianganyear,strlen(tianganyear));
	DeleteObject(newFont);
	newFont = CreateFont(15,7,3100,0,0,0,0,0,0,0,0,0,0,"@����"); 
	SelectObject(hDC,newFont);
	TextOut(hDC,38,90,TEXT("��"),2);
	DeleteObject(newFont);
	newFont = CreateFont(15,7,2500,0,0,0,0,0,0,0,0,0,0,"@����"); 
	SelectObject(hDC,newFont);
	TextOut(hDC,120,70,tianganmonth,strlen(tianganmonth));
	DeleteObject(newFont);
	newFont = CreateFont(15,7,2350,0,0,0,0,0,0,0,0,0,0,"@����"); 
	SelectObject(hDC,newFont);
	TextOut(hDC,105,98,TEXT("��"),2);
	DeleteObject(newFont);
	SelectObject(hDC,oldFont);
	//SunToLunar(
	ID=(pLunarDay.nYear-1900)%12;//��ȡ��Ф��Ӧ��id
    wsprintf(szBuffer,"../image/shengxiao1/%d.bmp",ID);
	hBitmapImag = LoadImage (g_hInst, szBuffer,IMAGE_BITMAP,32,28,LR_LOADFROMFILE);//������Фλͼ
	wsprintf(szBuffer,"../image/shengxiao/%d.bmp",ID);
	hBitmapImag1 = LoadImage (g_hInst, szBuffer,IMAGE_BITMAP,32,28,LR_LOADFROMFILE);//������Фλͼ
	if(NULL == hBitmapImag || NULL == hBitmapImag1)
	{
		MessageBox(g_hInst,_T("����λͼʧ��"),"ERORR",0);
	}
        
    GetObject (hBitmapImag, sizeof (BITMAP),&bitmap) ;
	        
	cxBitmap = bitmap.bmWidth ;
	        
	cyBitmap = bitmap.bmHeight ;
	
	hdcMemImag  = CreateCompatibleDC (NULL) ;
	        
	SelectObject (hdcMemImag, hBitmapImag) ;
	BitBlt (hDC, 48, 90, cxBitmap, cyBitmap,hdcMemImag, 0, 0, SRCPAINT) ;
	SelectObject (hdcMemImag, hBitmapImag1) ;
	BitBlt (hDC, 48, 90, cxBitmap, cyBitmap,hdcMemImag, 0, 0, SRCAND) ;
	        
									
	DeleteDC (hdcMemImag);
	DeleteObject(hBitmapImag);
	DeleteObject(hBitmapImag1);
	        
                         

}
void PlayOnFull(int hour)
{
	char buffer[100];
	sprintf(buffer,"open \"../image/sound/sunyanzi/%02d.mp3\" alias ffile",hour);
	printf(buffer);
	mciSendString(buffer,NULL,0,NULL);
	mciSendString("play ffile",NULL,0,NULL);

}
void PlayAlarm(HWND hDlg,int index)
{
	char buffer[100];
	int i;
	char _buffer[100];
	FILE *file;
	HWND hwnd;
	HWND message_box;
	index +=1;
	if(cur_alarm[index-1].style == 1)
	{
		if(fopen_s(&file,"../setup/alarm.ini","w+")!=NULL)
		{
			exit(0);
		}
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
				hwnd = GetDlgItem(hDlg,IDC_ALARM_SHOW);
				SendMessage(hwnd,LB_DELETESTRING,(WPARAM)index,0);

	}
	
	sprintf(buffer,"open \"../image/sound/alarm/%d.mp3\" alias file",cur_alarm[index-1].sound);
	//printf(buffer);
	mciSendString(buffer,NULL,0,NULL);
	mciSendString("play file",NULL,0,NULL);
	
	MessageBox(hDlg,"���ֹͣ","��������",0);
	//message_box = FindWindow(NULL,"��������");
	mciSendString("close file",NULL,0,NULL);


}
void PlayMemory(HWND hDlg,int i)
{
	char buffer[100];
	TCHAR buffer1[100];
	//printf(buffer);
	sprintf(buffer,"open \"../image/sound/alarm/1.mp3\" alias file");
	mciSendString(buffer,NULL,0,NULL);
	mciSendString("play file",NULL,0,NULL);
	
	wsprintf(buffer1,"���ļ����� \"%s\" ����  ��������һ��\r\n���ֵ��ֹͣ",cur_memory[i].name);
	MessageBox(hDlg,buffer1,cur_memory[i].name,0);
	mciSendString("close file",NULL,0,NULL);
	memorynum --;
}