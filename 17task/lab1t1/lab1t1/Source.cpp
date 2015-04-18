#include <windows.h>
#include<stdio.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
{
	int a = atoi(lpCmdLine);
	char buff[100];
	sprintf_s(buff, "a=%d", a);
	MessageBox(NULL, buff, "Caption", MB_ABORTRETRYIGNORE);
	return 0;
}