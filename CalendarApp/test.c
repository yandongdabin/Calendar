#include<windows.h>
#include<string.h>
#pragma comment(lib, "winmm.lib")

void PlayOnFull(int hour)
{
	char buffer[100];
	sprintf(buffer,"open \"../image/sound/sunyanzi/%02d.mp3\" alias file",hour);
	//wsprintf(buffer,"../image/sound/sunyanzi/%02d.mp3",hour);
	printf(buffer);
	mciSendString(buffer,NULL,0,NULL);
	mciSendString("play file",NULL,0,NULL);

}
int main()
{
	PlayOnFull(9);
	//mciSendString("open \"../image/sound/sunyanzi/08.mp3\" alias file",NULL,0,NULL);
	//mciSendString("play file",NULL,0,NULL);
	getch();
	return 0;
}