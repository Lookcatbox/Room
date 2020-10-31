#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

int main()
{
//	system("cmd");
	system("start music1.mp3");
	Sleep(1000); 
	HWND hwnd=GetForegroundWindow();	
	if(hwnd)
	{
		ShowWindow(hwnd,SW_HIDE);
	} 
	Sleep(5000);
	system("start music2.mp3");
	return 0;
}

