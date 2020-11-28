#include<iostream>
#include<windows.h>
#include<conio.h>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<algorithm>
#include<fstream>
#include<string.h>
#include<vector>
#define BIGSIZE 1
#define MIDSIZE 2
#define SMASIZE 3
//四个方向
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
// RPG
#define WALL 1//墙
#define LOAD 2//路
#define DOOR 3//墙
#define GOTO 4//传送点
#define SHOP 5//商店 
//时间
#define DAY 1
#define HOUR 2
#define MINUTE 3
#define SECOND 4
#define MS 5
//
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;


/*
涵盖了：
12个常数
11个函数
2个类型变量

v1.1.0
增加了四个方向的常数
增加了创建文件夹函数
优化了say()
v1.1.1
增加了RPG地图用常数
v1.2.0
增加了时间类与5个时间常数
增加了
*/
COORD pos;//光标类型，有一个X和Y
HWND window;//窗口类型
bool isInit;
int index;
int MT[624];
int mcount ;
int realrand ( ) {
    mcount ++ ;
    int t = clock ( ) + 1 ; // 使用当前时间 
    for ( int i = 1 ; i < 12121307 ; i ++ ) { // 降速（如果放到具体代码里面使用可以将此参数调低） 
        t += rand ( ) ;
    }
    t += clock ( ) ; // 降速后扩大时间变化 
    t *= -1234 ;
    return t * mcount + rand () ;
}


void generate()
{
    for(int i=0; i<624; i++)
    {
        int y = (MT[i] & 0x80000000) + (MT[(i+1) % 624] & 0x7fffffff);
        MT[i] = MT[(i + 397) % 624] ^ (y >> 1);
        if (y & 1)
            MT[i] ^= 2567483615;
    }
}

void MSsrand(int seed)
{
    index = 0;
    isInit = 1;
    MT[0] = seed;
    for(int i=1; i<624; i++)
    {
        int t = 1812433253 * (MT[i-1] ^ (MT[i-1] >> 30)) + i;
        MT[i] = t & 0xffffffff;   //取最后的32位
    }
}
int MSrand()
{
    if(!isInit) MSsrand(realrand());
    if(index == 0) generate();
    int y = MT[index];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 2636928640);
    y = y ^ ((y << 15) & 4022730752);
    y = y ^ (y >> 18);
    index = (index + 1) % 624;
    return y; 
}

void say(string a,int timeh) {//间隔输出字符 a字符串
	for(int i=0; i<a.size(); i++) {
		cout<<a[i];
		Sleep(timeh);
	}
}

void Color(int num) { //设置颜色
	HANDLE hout;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout,num);
}

void gotoxy(int x, int y) { //函数移动光标
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //获得输出设备的句柄
	SetConsoleCursorPosition(hOut, pos); //参数1：控制台句柄；参数2：COORD结构存放的坐标
} /**/

void hidden(bool k) { //隐藏光标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=k;//赋1为显示，赋0为隐藏
	SetConsoleCursorInfo(hOut,&cci);
}

void GetMouse(int &x,int &y) { //获取鼠标位置
	POINT ptB = { 0, 0 };
	LPPOINT xy = &ptB;	//位置变量

	x = xy -> x;
	y = xy -> y;
}

void Endl(int num) { //换行
	for(int i=0; i<num; i++) printf("\n");
}

void Draw(int num,char ch) { //画字符
	for(int i=0; i<num; i++) printf("%c",ch);
}

void ITOD(int &ot) {
	if(ot==LEFT) ot=RIGHT;
	else if(ot==RIGHT) ot=LEFT;
	else if(ot==UP) ot=DOWN;
	else if(ot==DOWN) ot=UP; 
}

void lt(int &ot) {
	if(ot==LEFT) ot=DOWN;
	else if(ot==RIGHT) ot=UP;
	else if(ot==UP) ot=LEFT;
	else if(ot==DOWN) ot=RIGHT;  
}

void rt(int &ot) {lt(ot);ITOD(ot);}

struct c_picture {
	int n,m;
	int line[100][100];
	void out(int x,int y) {
		for(int i=y; i<y+n; i++) {
			gotoxy(x,i);
			for(int j=1; j<=m; j++) {
			   Color(line[i-y+1][j]);
			   printf("█");
			} 
		} 
	}
};
void SetScreen(const int num) { //设置屏幕大小
	switch(num) {
		case BIGSIZE:
			system("mode con cols=240 lines=60");
		case MIDSIZE:
			system("mode con cols=120 lines=30");
		case SMASIZE:
			system("mode con cols=30 lines=20");
	}
	return ;
}

inline void SetFolder(string l,string name) { //创建文件夹，用法路径+文件名
	l = "md "+l+name;
	system(l.c_str());
}

inline int GetKey() { //获取按键，返回常数
	char ch = getch();
	switch(ch) {
		case 'w':
			return UP;
		case 's':
			return DOWN;
		case 'a':
			return LEFT;
		case 'd':
			return RIGHT;
	}
	return NULL;
}

struct Timeh {
	long long last_time=0;
	long long now_time=clock();
	void replace() { //更新时间
		last_time = now_time;
	}
	long long conversion(int num,int to) { //转换时间
		switch(to) {
			case DAY:
				return num/1000/60/60/24;
			case HOUR:
				return num/1000/60/60;
			case MINUTE:
				return num/1000/60;
			case SECOND:
				return num/1000;
			case MS:
				return num;
		}
	}
	long long Get_time(int to = MS) { //获取时间间隔
		now_time = clock();
		switch(to) {
			case DAY:
				return now_time/1000/60/60/24 - last_time/1000/60/60/24;
			case HOUR:
				return now_time/1000/60/60 - last_time/1000/60/60;
			case MINUTE:
				return now_time/1000/60 - last_time/1000/60;
			case SECOND:
				return now_time/1000 - last_time/1000;
			case MS:
				return now_time - last_time;
		}
	}
	bool Is_time_enough(int num,int to=MS) { //判断时间间隔是否足够
		now_time = clock();
		switch(to) {
			case DAY:
				if(now_time/1000/60/60/24 - last_time/1000/60/60/24 >= num) return true;
			case HOUR:
				if(now_time/1000/60/60 - last_time/1000/60/60 >= num) return true;
			case MINUTE:
				if(now_time/1000/60 - last_time/1000/60 >= num) return true;
			case SECOND:
				if(now_time/1000 - last_time/1000 >= num) return true;
			case MS:
				if(now_time - last_time >= num) return true;
		}
		return false;
	}
};

struct Int_Csdt {//Can store data types
	vector<int> type;
	vector<string> lei;//类，代表对应下标的数据类型
	string fname;//文件名 如user.txt
	string path;//路径 格式为c:// 或 c://user//
	//==========//
	string wname;//文件夹名 (如果有新创建文件夹则需填写)
	string wpath;//文件夹路径  (如果有新创建文件夹则需填写)
	void output() {
		string l = "md "+wpath+" "+wname;
		system(l.c_str());
		l = path+fname;
		FILE* out=fopen(l.c_str(),"w");
		for(int i=0; i<type.size(); i++) fprintf(out,"%d\n",type[i]);
		fclose(out);
	}
	void input() {
		string l = path+fname;
		FILE* in=fopen(l.c_str(),"r");
		for(int i=0; i<type.size(); i++) fscanf(in,"%d",type[i]);
	}
	int operator [](string a) {
		for(int i=0; i<lei.size(); i++) if(lei[i] == a) return type[i];
		return NULL;
	}
};

inline void D1XX(POINT& pt){pt.x=abs(pt.x),pt.y=abs(pt.y);}
struct Button {
	int x,y;
	string name;
	int len;
	int Color,Gcolor;
	bool ib = false;
	void color(int a) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
	}
	void gto(int x,int y) {
		COORD pos;
		pos.X=y*2;
		pos.Y=x;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}
	void out() {
		gto(x,y),color(Color),printf("%s",name.c_str());
	}
	void GetPos(POINT &pt) { //获得鼠标相对于屏幕的位置
		HWND hwnd=GetForegroundWindow();
		GetCursorPos(&pt);
		ScreenToClient(hwnd,&pt);
		pt.y=pt.y/16,pt.x=pt.x/16;//除以16，想不明白自己把它去掉试试
	}
	bool Preserve() {
		POINT pt;
		GetPos(pt);
		if(pt.y==x&&(pt.x>=y&&pt.x<=y+len/2)) {
			if(!ib) {
				color(Gcolor);
				gto(x,y),printf("%s",name.c_str());
				ib = true;
			}
			if(KEY_DOWN(MOUSE_MOVED)) return 1;//检测到点击按钮
		} else {
			if(ib) {
				color(Color);
				gto(x,y),printf("%s",name.c_str());
				ib = false;
			}
		}
		return 0;//没有检测到
	}
};

void GetPos(POINT &pt) { //获得鼠标相对于屏幕的位置
//POINT是自带类型
	HWND hwnd=GetForegroundWindow();
	GetCursorPos(&pt);
	ScreenToClient(hwnd,&pt);
	pt.y=pt.y/16,pt.x=pt.x/16;//除以16，想不明白自己把它去掉试试
}

void color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void gto(int x,int y) {
	COORD pos;
	pos.X=y*2;
	pos.Y=x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

Button NewButton(int x,int y,int Color,int Gcolor,string name) {
	Button t;
	t.x=x,t.y=y,t.name=name;
	t.len=name.size();
	t.Color = Color;
	t.Gcolor = Gcolor;
	return t;//新建按钮，返回它
}
//===以下为斜线的测试代码 
//inline void D1XX(POINT& pt){pt.x=abs(pt.x),pt.y=abs(pt.y);}
int gcd(int a,int b) {
	if(a<b) {
		int t=a;
		a=b,b=t;
	}
	if(a%b==0) return b;
    return gcd(b,a%b);
}
void out(int x,int y,int a,int b) {
	x*=a,y*=b;
	x+=10,y+=10;
	if(x<0||y<0)  return ; 
	gotoxy(x,y); 
	printf("H");
}
int YCHS(int x,int fm,int fz) {
	fz*=x;
	int count=fz/fm;
	if(fz%fm>=fm/2) count++;
	return count;
}
void line() {
	POINT pt;
	while(1) {
		GetPos(pt);
		pt.x-=10,pt.y-=10;
		int a=1,b=1;
		if(pt.x<0) a=-1;
		if(pt.y<0) b=-1;
		D1XX(pt);
		bool flag=false;
		int x=0,y=0;
		if(pt.x==0) {
			out(x,y,a,b);
			for(int i=1; i<=40; i++) y++,out(x,y,a,b);
			flag=true;
			system("cls");
		}
		if(pt.y==0) {
		    out(x,y,a,b);
			for(int i=1; i<=40; i++) x++,out(x,y,a,b);
			flag=true;
			system("cls");
		}
		if(flag) continue;
		int fz=pt.y,fm=pt.x;
		int ggg=gcd(fm,fz);
		fm/=ggg,fz/=ggg;
		out(x,y,a,b);
		x++;
		bool fff=false;
		for(int i=1; i<=40; i++) {
			int num=YCHS(x,fm,fz);
			if(y>num) y=num;
			out(x,y,a,b);
			if(y==num) x++,y++;
			else y++;
		}
		system("cls");
	}
} 
