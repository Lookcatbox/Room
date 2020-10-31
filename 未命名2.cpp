#include<bits/stdc++.h>
#include<c++play.h> 
using namespace std;

int main()
{
	Timeh a;
	getch();
	while(1) {
		if(a.Is_time_enough(60000)) break;
		cout<<a.now_time;
		gotoxy(0,0);
		cout<<"       ";
	}
	cout<<"OK";
	return 0;
}

