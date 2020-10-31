#include<bits/stdc++.h>
#include<c++play.h>
#include<windows.h>
#include<conio.h>

using namespace std;
/*更新记录
  未完整版：
  v0.0.1 自豪的拥有了多账号的登录系统
  v0.0.2 制作了主界面
  v0.0.3
*/
//===================登录部分=========================
string tmp1,tmp2,us[110]/*用户名*/,pw[110]/*密码*/;//|
int unum/*用户个数*/,mousefan=UP,chess[15][15],map1[15][15],mapnum=12,roofff=1,jejeje;/*地图上的物体		`	*/
bool shi[15][15]/*是否是实体*/,kkl=false,lintoto=false;
void make_map();         //|
//===================================================|
struct xy {
	int x,y;
};
struct U {                                          //|
	string name;                                   //|
	string word;
	int x,y,blood=100,kill=5,speed=100,up_blood=100,hui;
	int fan;                      //|
	int money;
};
bool SHIXUE;
int dx[4]= {0,0,1,-1};
int dy[4]= {1,-1,0,0};
U User;
struct bionode {
	int x,y,len,fan;
	void DY(bionode tmp) {
		x=tmp.x,y=tmp.y,fan=tmp.fan,len=tmp.len;
	}
};
bool fan_ok(int juruo,int zhex,int zhey) {
	if(juruo==LEFT&&(zhey<=0||shi[zhex][zhey-1])) return false;
	if(juruo==RIGHT&&(zhey>=14||shi[zhex][zhey+1])) return false;
	if(juruo==UP&&(zhex<=0||shi[zhex-1][zhey])) return false;
	if(juruo==DOWN&&(zhex>=14||shi[zhex+1][zhey])) return false;
	return true;
}
struct bullet {
	string ch;
	int lengh=0,fan,maxn,x,y,di,kill;
	Timeh t;
	void clear() {
		ch="\0";
		lengh=0;
		fan=0;
		maxn=0;
		x=0;
		y=0;
		di=0;
		t.last_time=0;
		t.now_time=0;
	}
};
bullet d[400];
int zbnum,ghnum;
void GET_bullet(int lei,int num);
void disfly();
void Get_New_Bio(int lei,int x,int y);
struct bio {
	int x,y,speed,nextf,color,kill,blood,lei,nextb,number,bspeed,make_zombie;//位置，速度,下一个方向·
	string ot,bot;
	Timeh th,bt,jt;
	bool hit=false,gop=false;
	void clean() {
		x=y=speed=0;
		ot='\0';
		th.last_time=0;
		th.now_time=0;
		color=0;
		gop=false;
	}
	void find_road() {
		int setnum=0,ans=1000;
		queue<bionode> q;
		bionode my_set[1000];
		bionode st1,st2,st3,st4;
		st1.fan=UP,st2.fan=DOWN,st3.fan=LEFT,st4.fan=RIGHT;
		st1.len=st2.len=st3.len=st4.len=1;
		st1.x=x-1,st1.y=y;
		st2.x=x+1,st2.y=y;
		st3.x=x,st3.y=y-1;
		st4.x=x,st4.y=y+1;
		if(st1.x>=0&&st1.x<15&&!shi[st1.x][st1.y]) q.push(st1),setnum++,my_set[setnum].DY(st1);
		if(st2.x>=0&&st2.x<15&&!shi[st2.x][st2.y]) q.push(st2),setnum++,my_set[setnum].DY(st2);
		if(st3.y>=0&&st3.y<15&&!shi[st3.x][st3.y]) q.push(st3),setnum++,my_set[setnum].DY(st3);
		if(st4.y>=0&&st4.y<15&&!shi[st4.x][st4.y]) q.push(st4),setnum++,my_set[setnum].DY(st4);
		while(!q.empty()) {
			bionode fu=q.front();
			if(fu.x==User.x&&fu.y==User.y/2) {
				if(fu.len<ans) ans=fu.len,nextf=fu.fan;
				q.pop();
				continue;
			}
			for(int i=0; i<4; i++) {
				bionode next;
				bool fula=false;
				next.DY(fu);
				next.x+=dx[i],next.y+=dy[i],next.len++;
				if(shi[next.x][next.y]) continue;
				if(next.x<0||next.x>14||next.y<0||next.y>14) continue;
				for(int j=1; j<=setnum; j++)
					if(my_set[j].x==next.x&&my_set[j].y==next.y) {
						if(next.len<my_set[j].len) my_set[j].DY(next);
						fula=1;
						break;
					}
				if(fula==1) continue;
				setnum++,my_set[setnum].DY(next);
				q.push(next);
			}
			q.pop();
		}
	}
	void find_road_far() {
		int gotof=-1;
		for(int i=1; i<110; i++) if(d[i].x==x||d[i].y==y*2) {
				gotof=d[i].fan;
				break;
			}
		if(gotof==UP) {
			if(fan_ok(LEFT,x,y)) nextf=LEFT;
			else if(fan_ok(RIGHT,x,y)) nextf=RIGHT;
			else if(fan_ok(UP,x,y)) nextf=UP;
			else nextf=DOWN;
		} else if(gotof==DOWN) {
			if(fan_ok(LEFT,x,y)) nextf=LEFT;
			else if(fan_ok(RIGHT,x,y)) nextf=RIGHT;
			else if(fan_ok(DOWN,x,y)) nextf=DOWN;
			else nextf=UP;
		} else if(gotof==LEFT) {
			if(fan_ok(UP,x,y)) nextf=UP;
			else if(fan_ok(DOWN,x,y)) nextf=DOWN;
			else if(fan_ok(LEFT,x,y)) nextf=LEFT;
			else nextf=RIGHT;
		} else if(gotof==RIGHT) {
			if(fan_ok(UP,x,y)) nextf=UP;
			else if(fan_ok(DOWN,x,y)) nextf=DOWN;
			else if(fan_ok(RIGHT,x,y)) nextf=RIGHT;
			else nextf=LEFT;
		} else {
			if(User.x==x||User.y==y*2) {
				gotof=User.fan;
				if(gotof==UP) {
					if(fan_ok(LEFT,x,y)) nextf=LEFT;
					else if(fan_ok(RIGHT,x,y)) nextf=RIGHT;
					else if(fan_ok(UP,x,y)) nextf=UP;
					else nextf=DOWN;
				} else if(gotof==DOWN) {
					if(fan_ok(LEFT,x,y)) nextf=LEFT;
					else if(fan_ok(RIGHT,x,y)) nextf=RIGHT;
					else if(fan_ok(DOWN,x,y)) nextf=DOWN;
					else nextf=UP;
				} else if(gotof==LEFT) {
					if(fan_ok(UP,x,y)) nextf=UP;
					else if(fan_ok(DOWN,x,y)) nextf=DOWN;
					else if(fan_ok(LEFT,x,y)) nextf=LEFT;
					else nextf=RIGHT;
				} else if(gotof==RIGHT) {
					if(fan_ok(UP,x,y)) nextf=UP;
					else if(fan_ok(DOWN,x,y)) nextf=DOWN;
					else if(fan_ok(RIGHT,x,y)) nextf=RIGHT;
					else nextf=LEFT;
				}
			} else {
				find_road();
				if(nextf==UP) nextf=DOWN;
				else if(nextf==DOWN) nextf=UP;
				else if(nextf==LEFT) nextf=RIGHT;
				else if(nextf==RIGHT) nextf=LEFT;
				while(!fan_ok(nextf,x,y)) {
					if(nextf==UP) nextf=LEFT;
					else if(nextf==DOWN) nextf=RIGHT;
					else if(nextf==LEFT) nextf=DOWN;
					else if(nextf==RIGHT) nextf=UP;
				}
			}
		}
	}
	void Boss_mode(int bosslei) {
		if(bosslei==1) {
			nextb=UP;
			GET_bullet(2,number);
			nextb=DOWN;
			GET_bullet(2,number);
			nextb=LEFT;
			GET_bullet(2,number);
			nextb=RIGHT;
			GET_bullet(2,number);
		}
		disfly();
	}
	void move() {
		if(lei==4) {
			if(zbnum>=20||ghnum>=20) return ;
			shi[x][y]=true;
			Color(color);
			gotoxy(y*2,x);
			cout<<ot;
			if(fan_ok(UP,x,y)) {
				Get_New_Bio(make_zombie,x-1,y);
				return ;
			}
			if(fan_ok(DOWN,x,y)) {
				Get_New_Bio(make_zombie,x+1,y);
				return ;
			}
			if(fan_ok(LEFT,x,y)) {
				Get_New_Bio(make_zombie,x,y-1);
				return ;
			}
			if(fan_ok(RIGHT,x,y)) {
				Get_New_Bio(make_zombie,x,y+1);
				return ;
			}
			return ;
		}
		if(gop==false) {
			gop=true;
			jt.last_time=clock();
		}
		shi[x][y]=false;
		map1[x][y]=0;
		gotoxy(y*2,x);
		cout<<"  ";
		if(lei==2||lei==3) {
			find_road_far();
			if(User.x==x&&User.y>=y*2) nextb=RIGHT;
			else if(User.x==x&&User.y<y*2) nextb=LEFT;
			else if(User.x>=x&&User.y==y*2) nextb=DOWN;
			else if(User.x<x&&User.y==y*2) nextb=UP;
			if(bt.Get_time()>=bspeed) GET_bullet(2,number),bt.replace();
		}
		if(lei==1) find_road();
		Color(color);
		if(!fan_ok(nextf,x,y)) return ;
		if(nextf==UP) x--;
		if(nextf==DOWN) x++;
		if(nextf==LEFT) y--;
		if(nextf==RIGHT) y++;
		if(lei==1&&x==User.x&&y==User.y/2) User.blood-=kill;
		gotoxy(y*2,x);
		cout<<ot;
		shi[x][y]=true;
		map1[x][y]=2;
		nextf=-1;
	}
	bool boos_jn() {
		if(lei==3)
			if(jt.Get_time()>=10000) return true;
		return false;
	}
};
struct weapon {
	int kill,up_bullet,now_bullet,speed,bspeed;
	string ot1,ot2,name,bullet_out;

	void out() {
		gotoxy(14,17);
		cout<<"            ";
		gotoxy(14,17);
		cout<<ot1;
		gotoxy(14,18);
		cout<<"            ";
		gotoxy(14,18);
		cout<<ot2;
	}
} now_weapon;
Timeh weapont;                     //|
//====================================================

struct pos {
	int x,y;
};

void jz() {
	Color(3);
	system("mode con cols=120 lines=30");
	cout<<"    ■■■     ■■■    ■■■   ■■     ■■"<<endl;
	cout<<"    ■    ■  ■    ■  ■    ■  ■ ■   ■ ■"<<endl;
	cout<<"    ■    ■  ■    ■  ■    ■  ■  ■ ■  ■"<<endl;
	cout<<"    ■■■    ■    ■  ■    ■  ■  ■ ■  ■"<<endl;
	cout<<"    ■   ■   ■    ■  ■    ■  ■  ■ ■  ■"<<endl;
	cout<<"    ■    ■  ■    ■  ■    ■  ■  ■ ■  ■"<<endl;
	cout<<"    ■    ■   ■■■    ■■■   ■   ■    ■"<<endl;
	gotoxy(0,7);
	int i,xxxx,j;
	string jz[9]= {"","▏","▎","▍","▌","▋","▊","▉"};
	Color(7);
	gotoxy(5,12);
	Color(15);
	printf("Loading ···\n");
	printf("----------------------------------\n\n");
	printf("----------------------------------\n");
	Color(6);
	printf("Copyright (C)2018 Cat_Box workteam.\nAll right reserved.");
	for(i=1; i<=135; i++) {
		xxxx=i%8;
		int tmmmp=(i/8)*2;
		COORD pos = {tmmmp, 14};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		Color(10);
		cout<<jz[xxxx+1];
	}
	SetScreen(SMASIZE);
}
void how_to_ply();
void menu();
bio zombie[21],ghost[21];
bool zbdie[21],ghdie[21];
void Get_New_Bio(int lei,int x,int y) {
	if(lei==1) {
		zbnum++;
		zombie[zbnum].ot="♀",zombie[zbnum].color=8,zombie[zbnum].speed=500,zombie[zbnum].x=x,zombie[zbnum].y=y;
		zombie[zbnum].kill=20;
		zombie[zbnum].th.last_time=clock();
		zombie[zbnum].blood=80;
		zombie[zbnum].lei=1;
		gotoxy(y*2,x);
		cout<<zombie[zbnum].ot;
	}
	if(lei==2) {
		ghnum++;
		ghost[ghnum].ot="& ",ghost[ghnum].color=5,ghost[ghnum].speed=200,ghost[ghnum].x=x,ghost[ghnum].y=y;
		ghost[ghnum].kill=5;
		ghost[ghnum].th.last_time=clock();
		ghost[ghnum].blood=5;
		ghost[ghnum].lei=1;
	}
	if(lei==3) {
		zbnum++;
		zombie[zbnum].ot="◎";
		zombie[zbnum].color=3;
		zombie[zbnum].speed=700;
		zombie[zbnum].kill=50;
		zombie[zbnum].blood=300;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=1;
		zombie[zbnum].th.last_time=clock();
	}
	if(lei==4) {
		zbnum++;
		zombie[zbnum].ot="¤";
		zombie[zbnum].color=4;
		zombie[zbnum].speed=300;
		zombie[zbnum].kill=20;
		zombie[zbnum].blood=15;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=1;
		zombie[zbnum].th.last_time=clock();
	}
	if(lei==5) {
		zbnum++;
		zombie[zbnum].ot="%";
		zombie[zbnum].color=4;
		zombie[zbnum].speed=500;
		zombie[zbnum].kill=60;
		zombie[zbnum].blood=50;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=1;
		zombie[zbnum].th.last_time=clock();
	}
	if(lei==6) {
		zbnum++;
		zombie[zbnum].ot="★";
		zombie[zbnum].color=4;
		zombie[zbnum].speed=300;
		zombie[zbnum].kill=80;
		zombie[zbnum].blood=1000;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=1;
		zombie[zbnum].th.last_time=clock();
	}
	if(lei==7) {
		zbnum++;
		zombie[zbnum].ot="§";
		zombie[zbnum].bot="。";
		zombie[zbnum].color=4;
		zombie[zbnum].speed=400;
		zombie[zbnum].kill=20;
		zombie[zbnum].blood=150;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=2;
		zombie[zbnum].number=zbnum;
		zombie[zbnum].bspeed=1000;
		zombie[zbnum].th.last_time=clock();
	}
	if(lei==8) {
		zbnum++;
		zombie[zbnum].ot="{}";
		zombie[zbnum].bot="+";
		zombie[zbnum].color=4;
		zombie[zbnum].speed=500;
		zombie[zbnum].kill=20;
		zombie[zbnum].blood=350;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=2;
		zombie[zbnum].number=zbnum;
		zombie[zbnum].bspeed=3000;
		zombie[zbnum].th.last_time=clock();
	}
	if(lei==9) {
		zbnum++;
		zombie[zbnum].ot="￥";
		zombie[zbnum].bot="*";
		zombie[zbnum].color=4;
		zombie[zbnum].speed=400;
		zombie[zbnum].kill=15;
		zombie[zbnum].blood=800;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=3;
		zombie[zbnum].number=zbnum;
		zombie[zbnum].bspeed=1000;
		zombie[zbnum].th.last_time=clock();
	}
	if(lei==10) {
		zbnum++;
		zombie[zbnum].ot="Oo";
		zombie[zbnum].color=8;
		zombie[zbnum].speed=5000;
		zombie[zbnum].blood=450;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=4;
		zombie[zbnum].make_zombie=1;
		zombie[zbnum].th.last_time=clock();
		shi[x][y]=true;
		Color(zombie[zbnum].color);
		gotoxy(y*2,x);
		cout<<zombie[zbnum].ot;
	}
	if(lei==11) {
		zbnum++;
		zombie[zbnum].ot="Oo";
		zombie[zbnum].color=9;
		zombie[zbnum].speed=3500;
		zombie[zbnum].blood=450;
		zombie[zbnum].x=x;
		zombie[zbnum].y=y;
		zombie[zbnum].lei=4;
		zombie[zbnum].make_zombie=4;
		zombie[zbnum].th.last_time=clock();
		shi[x][y]=true;
		Color(zombie[zbnum].color);
		gotoxy(y*2,x);
		cout<<zombie[zbnum].ot;
	}
}
void about_us() {
	system("cls");
	Color(15);
	system("cls");
	printf("●◎◎◎◎◎◎◎◎◎◎◎◎◎●\n");
	printf("◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n●◎◎◎◎◎◎◎◎◎◎◎◎◎●");
	for(int i=1; i<=18; i++) {
		gotoxy(28,i);
		printf("◎");
	}
	Button A1 = NewButton(16,8,3,4,"[Exit]");
	A1.out();
	gotoxy(2,1);
	printf("游戏制作：");
	gotoxy(2,3);
	printf("登录模块：Look_cat_box");
	gotoxy(2,4);
	printf("主界面模块：Look_cat_box");
	gotoxy(2,6);
	printf("地图模块：Look_cat_box");
	gotoxy(2,7);
	printf("子弹模块：Look_cat_box");
	gotoxy(2,9);
	printf("生物模块：Look_cat_box");
	gotoxy(2,10);
	printf("寻路AI：Look_cat_box");
	gotoxy(2,12);
	printf("宣传：Look_cat_box");
	gotoxy(2,13);
	printf("欢迎加入团队猫箱工作室：");
	gotoxy(2,14);
	printf("");
	while(1) if(A1.Preserve()) {
			menu() ;
			return;
		}
}
bool hp50=false;
bool mp5=false;
void shop() {
	Button A1 = NewButton(16,8,3,4,"[Exit]");
	Button A2 = NewButton(5,3,3,4,"[HP+=50] $150");
	Button A3 = NewButton(7,3,3,4,"[-MP5-] $450");
	Color(15);
	system("cls");
	A1.out();
	A2.out();
	A3.out();
	gotoxy(0,0);
	printf("●◎◎◎◎◎◎◎◎◎◎◎◎◎●\n");
	printf("◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n●◎◎◎◎◎◎◎◎◎◎◎◎◎●");
	for(int i=1; i<=18; i++) {
		gotoxy(28,i);
		printf("◎");
	}
	gotoxy(10,10);
	cout<<"money:"<<User.money;
	Timeh buy;
	bool f=true;
	while(1) {
		if(A1.Preserve()) menu();
		if(A2.Preserve()&&User.money>=150&&f) hp50=true,User.money-=150,buy.last_time=clock(),f=false;
		if(A3.Preserve()&&User.money>=450&&f) mp5=true,User.money-=450,buy.last_time=clock(),f=false;
		if(!f&&buy.Get_time()>=500) f=true;
	}
	string l = "c:\\Roomfrc\\us\\"+User.name+"\\archive.txt";
	FILE *oppo=fopen(l.c_str(),"w");
	fprintf(oppo,"%d",User.money);
}
void BFCD() {
	Button A1 = NewButton(16,8,3,4,"[Exit]");
	A1.out();
	int aaan;
	char bbc1[11],bbc2[11];
	string bbbname[110],bbbword[110];
	Color(15);
	system("cls");
	printf("●◎◎◎◎◎◎◎◎◎◎◎◎◎●\n");
	printf("◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n●◎◎◎◎◎◎◎◎◎◎◎◎◎●");
	for(int i=1; i<=18; i++) {
		gotoxy(28,i);
		printf("◎");
	}
	gotoxy(5,5);
	cout<<"请输入文件路径：";
	gotoxy(5,6);
	cout<<"例：c:\\SE_fail\\(请输入两个斜杆)";
	gotoxy(5,7);
	string the_road;
	cin>>the_road;
	string made_road="md "+the_road+"Roomfrc";
	system(made_road.c_str());
	made_road="md "+the_road+"Roomfrc\\us";
	system(made_road.c_str());
	made_road="md "+the_road+"Roomfrc\\map";
	system(made_road.c_str());
	made_road=the_road+"Roomfrc\\user.txt";
	FILE* mdfk = fopen(made_road.c_str(),"w");
	FILE* read_old = fopen("c:\\Roomfrc\\user.txt","r");
	fscanf(read_old,"%d",&aaan);
	for(int i=1; i<=aaan; i++) {
		fscanf(read_old,"%s%s",&bbc1,&bbc2);
		bbbname[i]=bbc1,bbbword[i]=bbc2;
	}
	fprintf(mdfk,"%d\n",aaan);
	for(int i=1; i<=aaan; i++) fprintf(mdfk,"%s %s\n",bbbname[i].c_str(),bbbword[i].c_str());
	made_road=the_road+"Roomfrc\\更新日志.txt";
	FILE* dfg = fopen(made_road.c_str(),"w");
	fprintf(dfg,"版本v1.0(先行版) 拥有最基础的打怪系统，且安装了寻路AI\n制作：Look_cat_box\n宣传：Look_cat_box");
	menu();
	return ;
}
bool start=false;
void menu() {
	SetScreen(SMASIZE);
	system("cls");
	Color(15);
	printf("●◎◎◎◎◎◎◎◎◎◎◎◎◎●\n");
	printf("◎          ");
	Color(3);
	printf("ROOM");
	Color(15);
	printf("            ◎\n");
	printf("◎                          ◎");
	gotoxy(0,3);
	printf("◎User:");
	gotoxy(7,3);
	printf("%s",User.name.c_str());
	for(int i=0; i<21-User.name.size(); i++) putchar(' ');
	printf("◎");
	printf("◎                          ◎\n");
	gotoxy(0,4);
	printf("◎                           \n");
	gotoxy(28,4);
	printf("◎");
	Button A1 = NewButton(5,3,3,4,"[Start the game]");
	Button A2 = NewButton(7,3,3,4,"[Go shopping]");
	Button A3 = NewButton(9,3,3,4,"[How to play]");
	Button A4 = NewButton(11,3,3,4,"[About us]");
	Button A5 = NewButton(13,3,3,4,"[备份存档]");
	Button A6 = NewButton(15,3,3,4,"[countinue]");
	gotoxy(0,5);
	printf("◎              ");
	gotoxy(28,5);
	printf("◎\n");
	printf("◎                           \n");
	gotoxy(28,6);
	printf("◎\n");
	gotoxy(0,7);
	printf("◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n●◎◎◎◎◎◎◎◎◎◎◎◎◎●");
	for(int i=1; i<=18; i++) {
		gotoxy(28,i);
		printf("◎");
	}

	start=true;
	A1.out();
	A2.out();
	A3.out();
	A4.out();
	A5.out();
	A6.out();
	while(1) {
		if(A1.Preserve()) {
			SHIXUE=false;
			User.blood=100;
			now_weapon.name="AT-R103";
			now_weapon.up_bullet=150;
			now_weapon.now_bullet=150;
			now_weapon.bullet_out="::";
			now_weapon.ot1=" ._._.";
			now_weapon.ot2="[/[! ]======";
			now_weapon.kill=5;
			now_weapon.speed=100;
			now_weapon.bspeed=1000;
			if(hp50) {
				User.up_blood+=50;
				User.blood+=50;
				hp50=false;
			}
			if(mp5) {
				now_weapon.name="MP5";
				now_weapon.up_bullet=10;
				now_weapon.now_bullet=10;
				now_weapon.bullet_out="+";
				now_weapon.ot1="    #==#";
				now_weapon.ot2="▄【┳═┵一";
				now_weapon.kill=60;
				now_weapon.speed=600;
				now_weapon.bspeed=3000;
				mp5=false;
			}
			jejeje=0;
			make_map();
			return ;
		}
		if(A2.Preserve()) shop();
		if(A3.Preserve()) {
			how_to_ply() ;
			return ;
		}
		if(A4.Preserve()) {
			about_us();
			return ;
		}
		if(A5.Preserve()) {
			BFCD();
			return ;
		}
		if(A6.Preserve()) {
			string laoshi = "c:\\Roomfrc\\us\\"+User.name+"\\continue.txt";
			FILE *nishishui=fopen(laoshi.c_str(),"r");
			int cf;
			char cinde[110];
			fscanf(nishishui,"%d",&cf);
			if(cf!=1) {
				system("cls");
				gotoxy(5,5);
				cout<<"You can`t countinue!";
				Sleep(3000);
				menu();
				return ;
			}
			fscanf(nishishui,"%d%d",&roofff,&jejeje);
			fscanf(nishishui,"%d%d%d%d%d",&User.blood,&User.up_blood,&User.speed,&User.hui,&now_weapon.now_bullet);
			fscanf(nishishui,"%d%s",&now_weapon.bspeed,&cinde);
			now_weapon.bullet_out=cinde;
			fscanf(nishishui,"%d%s",&now_weapon.kill,&cinde);
			now_weapon.name=cinde;
			fscanf(nishishui,"%s",&cinde);
			now_weapon.ot1=cinde;
			fscanf(nishishui,"%s%d%d",&cinde,&now_weapon.speed,&now_weapon.up_bullet);
			now_weapon.ot2=cinde;
			make_map();
			return ;
		}
	}
}

void how_to_ply() {
	Color(15);
	system("cls");
	printf("●◎◎◎◎◎◎◎◎◎◎◎◎◎●\n");
	printf("◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n◎\n●◎◎◎◎◎◎◎◎◎◎◎◎◎●");
	for(int i=1; i<=18; i++) {
		gotoxy(28,i);
		printf("◎");
	}
	Button A1 = NewButton(16,8,3,4,"[Exit]");
	A1.out();
	gotoxy(2,1);
	printf("操作方法：");
	gotoxy(2,3);
	printf("wasd移动 方向键射击 空格技能");
	gotoxy(2,4);
	printf("数字键切换武器 r换弹");
	gotoxy(2,6);
	printf("通关后进入传送门来进入下一关");
	gotoxy(2,7);
	printf("前往lookcatbox.blog.luogu");
	gotoxy(2,8);
	printf(".org获取最新版本");
	gotoxy(2,9);
	printf("BUG反馈请在luogu.org @lcb9021");
	gotoxy(2,12);
	printf("常见BUG及解答");
	gotoxy(2,13);
	printf("无法移动:请调整输入法");
	gotoxy(2,14);
	printf("程序崩溃:可能是你改了数据");

	while(1) if(A1.Preserve()) {
			menu() ;
			return;
		}
}

void make_num(int num) {
	string jz[8]= {"▏","▎","▍","▌","▋","▊","▉"};
	for(int i=0; i<num/8; i++) printf("█");
	if(num%8!=0) printf("%s",jz[num%8-1].c_str());
}

void walk() {
	hidden(0);
	int d[2]= {0,0};
	bool biil=false;
	if(GetKeyState('W')<0&&kkl==0) User.x-=1,d[0]=1,kkl=1,User.fan=UP,biil=true;
	else if(GetKeyState('S')<0&&kkl==0) User.x+=1,d[0]=-1,kkl=1,User.fan=DOWN,biil=true;
	else if(GetKeyState('A')<0&&kkl==0) User.y-=2,d[1]=2,kkl=1,User.fan=LEFT,biil=true;
	else if(GetKeyState('D')<0&&kkl==0) User.y+=2,d[1]=-2,kkl=1,User.fan=RIGHT,biil=true;
	else kkl=0;
	if(shi[User.x][User.y/2]) {
		User.x+=d[0],User.y+=d[1];
		return ;
	}
	if(User.y<0||User.y>29) {
		User.y+=d[1];
		return ;
	}
	if(User.x<0||User.x>14) {
		User.x+=d[0];
		return;
	}
	if(biil) {
		gotoxy(User.y+d[1],User.x+d[0]);
		printf("  ");
		gotoxy(User.y,User.x);
		Color(3);
		printf("♀");
	}
}
bool vis[400];
Timeh iii;
void disfly() {

	for(int i=0; i<110; i++) if(vis[i]==true) {
			if(d[i].t.Get_time()>=50) {
				d[i].t.replace();
				if(d[i].fan==UP||d[i].fan==DOWN) {
					gotoxy(d[i].y,d[i].x);
					printf("  ");
					for(int j=1; j<=zbnum; j++) if(zombie[j].x==d[i].x&&zombie[j].y==d[i].y/2) {
							zombie[j].blood-=d[i].kill;
							gotoxy(zombie[j].y*2,zombie[j].x);
							Color(zombie[j].color+1);
							cout<<zombie[j].ot;
							break;
						}
					for(int j=1; j<=ghnum; j++) if(ghost[j].x==d[i].x&&ghost[j].y==d[i].y/2) {
							ghost[j].blood-=d[i].kill;
							gotoxy(ghost[j].y*2,ghost[j].x);
							Color(ghost[j].color+1);
							cout<<ghost[j].ot;
							break;
						}
					d[i].x+=d[i].di;
					for(int j=1; j<=zbnum; j++) if(zombie[j].x==d[i].x&&zombie[j].y==d[i].y/2) {
							zombie[j].blood-=d[i].kill;
							gotoxy(zombie[j].y*2,zombie[j].x);
							Color(zombie[j].color+1);
							cout<<zombie[j].ot;
							break;
						}
					for(int j=1; j<=ghnum; j++) if(ghost[j].x==d[i].x&&ghost[j].y==d[i].y/2) {
							ghost[j].blood-=d[i].kill;
							gotoxy(ghost[j].y*2,ghost[j].x);
							Color(ghost[j].color+1);
							cout<<ghost[j].ot;
							break;
						}
					if(d[i].x<0||d[i].x>14||shi[d[i].x][d[i].y/2]==true) {
						vis[i]=false;
						d[i].clear();
						break;
					}
					gotoxy(d[i].y,d[i].x);
					printf("%s",d[i].ch.c_str());
				}
				if(d[i].fan==LEFT||d[i].fan==RIGHT) {
					gotoxy(d[i].y,d[i].x);
					printf("  ");
					for(int j=1; j<=zbnum; j++) if(zombie[j].x==d[i].x&&zombie[j].y==d[i].y/2) {
							zombie[j].blood-=d[i].kill;
							gotoxy(zombie[j].y*2,zombie[j].x);
							Color(zombie[j].color+1);
							cout<<zombie[j].ot;
							break;
						}
					for(int j=1; j<=ghnum; j++) if(ghost[j].x==d[i].x&&ghost[j].y==d[i].y/2) {
							ghost[j].blood-=d[i].kill;
							gotoxy(ghost[j].y*2,ghost[j].x);
							Color(ghost[j].color+1);
							cout<<ghost[j].ot;
							break;
						}
					d[i].y+=d[i].di;
					for(int j=1; j<=zbnum; j++) if(zombie[j].x==d[i].x&&zombie[j].y==d[i].y/2) {
							zombie[j].blood-=d[i].kill;
							gotoxy(zombie[j].y*2,zombie[j].x);
							Color(zombie[j].color+1);
							cout<<zombie[j].ot;
							break;
						}
					for(int j=1; j<=ghnum; j++) if(ghost[j].x==d[i].x&&ghost[j].y==d[i].y/2) {
							ghost[j].blood-=d[i].kill;
							gotoxy(ghost[j].y*2,ghost[j].x);
							Color(ghost[j].color+1);
							cout<<ghost[j].ot;
							break;
						}
					if(d[i].y<0||d[i].y>29||shi[d[i].x][d[i].y/2]==true) {
						vis[i]=false;
						d[i].clear();
						break;
					}
					gotoxy(d[i].y,d[i].x);
					printf("%s",d[i].ch.c_str());
				}
			}
		}
	for(int i=110; i<400; i++) if(vis[i]==true) {
			if(d[i].t.Get_time()>=50) {
				Color(14);
				d[i].t.replace();
				if(d[i].fan==UP||d[i].fan==DOWN) {
					gotoxy(d[i].y,d[i].x);
					printf("  ");
					d[i].x+=d[i].di;
					if(User.x==d[i].x&&User.y==d[i].y) {
						User.blood-=d[i].kill;
						vis[i]=false;
						d[i].clear();
						break;
					}
					if(d[i].x<0||d[i].x>14||shi[d[i].x][d[i].y/2]==true) {
						vis[i]=false;
						d[i].clear();
						break;
					}
					Color(14);
					gotoxy(d[i].y,d[i].x);
					printf("%s",d[i].ch.c_str());
				}
				if(d[i].fan==LEFT||d[i].fan==RIGHT) {
					gotoxy(d[i].y,d[i].x);
					printf("  ");
					d[i].y+=d[i].di;
					for(int j=1; j<=zbnum; j++) if(zombie[j].x==d[i].x&&zombie[j].y==d[i].y/2) {
							zombie[j].blood-=d[i].kill;
							gotoxy(zombie[j].y*2,zombie[j].x);
							Color(zombie[j].color+1);
							cout<<zombie[j].ot;
							break;
						}
					for(int j=1; j<=ghnum; j++) if(ghost[j].x==d[i].x&&ghost[j].y==d[i].y/2) {
							ghost[j].blood-=d[i].kill;
							gotoxy(ghost[j].y*2,ghost[j].x);
							Color(ghost[j].color+1);
							cout<<ghost[j].ot;
							break;
						}
					if(User.x==d[i].x&&User.y==d[i].y) {
						User.blood-=d[i].kill;
						vis[i]=false;
						d[i].clear();
						break;
					}
					if(d[i].y<0||d[i].y>29||shi[d[i].x][d[i].y/2]==true) {
						vis[i]=false;
						d[i].clear();
						break;
					}
					Color(14);
					gotoxy(d[i].y,d[i].x);
					printf("%s",d[i].ch.c_str());
				}
			}
		}
}
void MouseFan() { //获得鼠标相对于屏幕的位置
        POINT pt;
		HWND hwnd=GetForegroundWindow();
		GetCursorPos(&pt);
		ScreenToClient(hwnd,&pt);
		pt.y=pt.y/16,pt.x=pt.x/8;//除以16，想不明白自己把它去掉试试
		bool mouss=false;
		if(mousefan==RIGHT&&pt.x>User.y) mouss=true;
		if(mousefan==LEFT&&pt.x<User.y) mouss=true;
		if(mousefan==UP&&pt.y<User.x) mouss=true;
		if(mousefan==DOWN&&pt.y>User.x) mouss=true;
		if(mouss) return ;
		if(pt.y<User.x) mousefan=UP;
		else if(pt.x<User.y) mousefan=LEFT;
		else if(pt.y>User.x) mousefan=DOWN;
		else mousefan=RIGHT;
}
void GET_bullet(int lei,int num) {
	int fanxiang;
	if(lei==1) {
		if(weapont.Get_time()>=now_weapon.speed) weapont.replace();
		else return ;
		bool flags=false;
		if(GetKeyState(VK_UP)<0) {
			flags=true;
			fanxiang=UP;
		} else if(GetKeyState(VK_DOWN)<0) {
			flags=true;
			fanxiang=DOWN;
		} else if(GetKeyState(VK_LEFT)<0) {
			flags=true;
			fanxiang=LEFT;
		} else if(GetKeyState(VK_RIGHT)<0) {
			flags=true;
			fanxiang=RIGHT;
		} else if(KEY_DOWN(MOUSE_MOVED)) {
			flags=true;
			fanxiang=mousefan;
		}
		if(flags&&now_weapon.now_bullet) {
			for(int i=0; i<110; i++) if(!vis[i]) {
					vis[i]=true;
					Color(14);
					now_weapon.now_bullet--;
					d[i].kill=now_weapon.kill;
					if(SHIXUE) d[i].kill=d[i].kill+d[i].kill*(User.up_blood-User.blood)*100/User.up_blood/100;
					d[i].t.last_time=clock();
					if(fanxiang==UP) {
						d[i].x=User.x-1;
						d[i].y=User.y;
						d[i].di=-1;
					}
					if(fanxiang==DOWN) {
						d[i].x=User.x+1;
						d[i].y=User.y;
						d[i].di=1;
					}
					if(fanxiang==LEFT) {
						d[i].x=User.x;
						d[i].y=User.y-2;
						d[i].di=-2;
					}
					if(fanxiang==RIGHT) {
						d[i].x=User.x;
						d[i].y=User.y+2;
						d[i].di=2;
					}
					for(int j=1; j<=zbnum; j++)
						if(zombie[j].x==d[i].x&&zombie[j].y==d[i].y/2) {
							zombie[j].blood-=d[i].kill;
							gotoxy(zombie[j].y*2,zombie[j].x);
							Color(zombie[j].color+1);
							cout<<zombie[j].ot;
							break;
						}
					for(int j=1; j<=ghnum; j++)
						if(ghost[j].x==d[i].x&&ghost[j].y==d[i].y/2) {
							ghost[j].blood-=d[i].kill;
							gotoxy(ghost[j].y*2,ghost[j].x);
							Color(ghost[j].color+1);
							cout<<ghost[j].ot;
							break;
						}
					if(d[i].x<0||d[i].x>14||d[i].y<0||d[i].y>29||shi[d[i].x][d[i].y/2]) {
						d[i].clear();
						vis[i]=false;
						break;
					}
					d[i].fan=fanxiang;
					d[i].ch=now_weapon.bullet_out;
					gotoxy(d[i].y,d[i].x);
					printf("%s",d[i].ch.c_str());
					break;
				}
		}
	}
	if(lei==2) {
		fanxiang=zombie[num].nextb;
		for(int i=110; i<400; i++) if(!vis[i]) {
				vis[i]=true;
				d[i].kill=zombie[num].kill;
				d[i].t.last_time=clock();
				if(fanxiang==UP) {
					d[i].x=zombie[num].x-1;
					d[i].y=zombie[num].y;
					d[i].di=-1;
				}
				if(fanxiang==DOWN) {
					d[i].x=zombie[num].x+1;
					d[i].y=zombie[num].y;
					d[i].di=1;
				}
				if(fanxiang==LEFT) {
					d[i].x=zombie[num].x;
					d[i].y=zombie[num].y-1;
					d[i].di=-2;
				}
				if(fanxiang==RIGHT) {
					d[i].x=zombie[num].x;
					d[i].y=zombie[num].y+1;
					d[i].di=2;
				}
				d[i].y*=2;
				if(User.x==d[i].x&&User.y==d[i].y) {
					User.blood-=d[i].kill;
					d[i].clear();
					vis[i]=false;
					break;
				}

				if(d[i].x<0||d[i].x>14||d[i].y<0||d[i].y>29||shi[d[i].x][d[i].y/2]) {
					d[i].clear();
					vis[i]=false;
					break;
				}
				d[i].fan=fanxiang;
				d[i].ch=zombie[num].bot;
				gotoxy(d[i].y,d[i].x);
				printf("%s",d[i].ch.c_str());
				break;
			}
	}
}
void monster_move() {
	for(int i=1; i<=zbnum; i++)
		if(zombie[i].th.Is_time_enough(zombie[i].speed,MS)&&!zbdie[i]) {
			zombie[i].move();
			zombie[i].th.replace();
		}
	for(int i=1; i<=ghnum; i++) if(ghost[i].th.Is_time_enough(ghost[i].speed,MS)&&!ghdie[i]) {
			ghost[i].move();
			ghost[i].th.replace();
		}
}
void ifUserdie() {
	if(User.blood<=0) {
		SetScreen(SMASIZE);
		int new_money=roofff*jejeje;
		system("cls");
		gotoxy(5,5);
		cout<<"You Die!!!";
		gotoxy(5,10);
		cout<<"money + "<<new_money;
		Sleep(3000);
		User.money+=new_money;
		string l = "c:\\Roomfrc\\us\\"+User.name+"\\archive.txt";
		FILE *oppo=fopen(l.c_str(),"w");
		fprintf(oppo,"%d",User.money);
		string r = "c:\\Roomfrc\\us\\"+User.name+"\\continue.txt";
		FILE *opp=fopen(r.c_str(),"w");
		fprintf(opp,"%d",-1);
		User.up_blood=100;
		menu();
		return ;
	}
}
int last_blood,last_bullet;
void show_blood() {
	Color(12);
	if(User.blood!=last_blood) {
		gotoxy(0,16);
		cout<<"          ";
		gotoxy(0,16);
		cout<<"HP:"<<User.blood<<"/"<<User.up_blood;
		last_blood=User.blood;
	}
	if(now_weapon.now_bullet!=last_bullet) {
		gotoxy(0,18);
		cout<<"              ";
		gotoxy(0,18);
		cout<<"bullet:"<<now_weapon.now_bullet<<"/"<<now_weapon.up_bullet;
		last_bullet=now_weapon.now_bullet;
	}
	if(SHIXUE) {
		gotoxy(32,4);
		cout<<"                       ";
		gotoxy(32,4);
		cout<<"当前伤害加成："<<(User.up_blood-User.blood)*100/User.up_blood;
	}
}
void ifzbdie() {
	for(int i=1; i<=zbnum; i++) if(!zbdie[i]&&zombie[i].blood<=0) {
			zbdie[i]=true;
			gotoxy(zombie[i].y*2,zombie[i].x);
			cout<<"  ";
			shi[zombie[i].x][zombie[i].y]=false;
			map1[zombie[i].x][zombie[i].y]=0;
			zombie[i].clean();
			jejeje++;
		}
	for(int i=1; i<=ghnum; i++) if(!ghdie[i]&&ghost[i].blood<=0) {
			ghdie[i]=true;
			gotoxy(ghost[i].y*2,ghost[i].x);
			cout<<"  ";
			shi[ghost[i].x][ghost[i].y]=false;
			map1[ghost[i].x][ghost[i].y]=0;
			ghost[i].clean();
			jejeje++;
		}
}
bool all_die() {
	for(int i=1; i<=zbnum; i++) if(!zbdie[i]) return false;
	for(int i=1; i<=ghnum; i++) if(!ghdie[i]) return false;
	return true;
}
void next_room();
void make_map() {
	srand(time(0));
	system("mode con cols=60 lines=20");
	bool isboss=false;
	int bossid;
	string l = "c:\\Roomfrc\\us\\"+User.name+"\\continue.txt";
	FILE *oppo=fopen(l.c_str(),"w");
	fprintf(oppo,"%d\n",1);
	fprintf(oppo,"%d %d\n",roofff,jejeje);
	fprintf(oppo,"%d %d %d %d %d\n",User.blood,User.up_blood,User.speed,User.hui,now_weapon.now_bullet);
	fprintf(oppo,"%d %s %d %s %s %s %d %d\n",now_weapon.bspeed,now_weapon.bullet_out.c_str(),now_weapon.kill,now_weapon.name.c_str(),now_weapon.ot1.c_str(),now_weapon.ot2.c_str(),now_weapon.speed,now_weapon.up_bullet);
	system("cls");
	zbnum=0;
	ghnum=0;
	for(int i=1; i<=20; i++) zbdie[i]=0;
	for(int i=1; i<=20; i++) ghdie[i]=0;
l:
	last_blood=-1;
	last_bullet=-1;
	int tttkkktmp=MSrand()%mapnum+1;
//    int tttkkktmp=10;
	if(start==true) tttkkktmp=0;
	if(tttkkktmp==9) isboss=true,bossid=3;
	string kkksc03;
	if(tttkkktmp==0) kkksc03="0";
	else while(tttkkktmp) {
			kkksc03=char(tttkkktmp%10+'0')+kkksc03;
			tttkkktmp/=10;
		}
	gotoxy(32,0);
	Color(12);
	cout<<"          ";
	gotoxy(32,0);
	Color(12);
	cout<<"map:NO."<<kkksc03;
	kkksc03="c:\\Roomfrc\\map\\"+kkksc03+".txt";
	if(SHIXUE) {
		gotoxy(32,2);
	    cout<<"技能（被动）:嗜血";
	    gotoxy(32,3);
	    cout<<"冷却：无";
	}
	FILE* read_map = fopen(kkksc03.c_str(),"r");
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++) fscanf(read_map,"%d",&map1[i][j]);
	int monster;
	fscanf(read_map,"%d",&monster);
	for(int i=1; i<=monster; i++) {
		int x,y,lei;
		fscanf(read_map,"%d%d%d",&x,&y,&lei);
		Get_New_Bio(lei,x,y);
	}
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++) shi[i][j]=map1[i][j];
	gotoxy(0,0);
	show_blood();
	gotoxy(0,15);
	for(int i=0; i<15; i++) printf("==");
	for(int i=0; i<20; i++) {
		gotoxy(30,i);
		cout<<"|";
	}
	Color(4);
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++) {
			gotoxy(j*2,i);
			if(map1[i][j]==1) cout<<"█";
			else cout<<"  ";
		}
	User.x=14;
	User.y=14;
	gotoxy(User.y,User.x);
	Color(3);
	printf("♀");
	now_weapon.out();
	gotoxy(0,17);
	cout<<"      ";
	gotoxy(0,17);
	Color(12);
	cout<<"Room:"<<roofff;
	gotoxy(14,16);
	cout<<"             ";
	gotoxy(14,16);
	cout<<"weapons:"<<now_weapon.name;
	for(int i=1; i<=zbnum; i++) zombie[i].move();
	Timeh t,mt,bt,walkt,bllt,huit,bosst;
	bool sdcklm=false,woyebu=false,smoke=false;
	int alive1=MSrand()%15,alive2=MSrand()%15,moge=MSrand()%100+1,bossto=0;
	if(start) moge=101;
	start=false;
	HWND hwnd=GetForegroundWindow();
	while(shi[alive1][alive2]) alive1=rand()%15,alive2=rand()%15;
	while(1) {
		MouseFan();
		if(GetKeyState('M')<0) {
			ShowWindow(hwnd,SW_MINIMIZE);
			while(1) if(GetKeyState('O')<0) break;
		}
		if(GetKeyState('P')<0)  {
			Sleep(100);
			while(1) if(GetKeyState('O')<0) break;
		}
		if(walkt.Get_time()>=User.speed) {
			walk();
			walkt.replace();
		}
		if(!woyebu) GET_bullet(1,0);
		if(huit.Get_time()>=1000&&!all_die()) {
			User.blood+=User.hui;
			if(User.blood>User.up_blood*100/125) User.blood=User.up_blood*100/125;
			huit.replace();
		}
		if(t.Get_time()>=200) {
			t.replace();
			show_blood();
			if(all_die()) {
				if(moge<=20&&smoke==false) {
					gotoxy(alive2*2,alive1);
					Color(3);
					cout<<"◆";
					if(User.x==alive1&&User.y/2==alive2) {
						smoke=true;
						system("cls");
						gotoxy(0,0);
						cout<<"补给箱:"<<endl;
						cout<<"Aurora \n弹容量:40\n伤害：10\n射速: 0.125s\n换弹时间:1s";
						Button A1 = NewButton(16,8,3,4,"[确定]");
						Button A2 = NewButton(16,2,3,4,"[取消]");
						A1.out(),A2.out();
						while(1) {
							if(A1.Preserve()) {
								now_weapon.name="Aurora";
								now_weapon.ot1="【■〓¤====";
								now_weapon.ot2="//~|/'''";
								now_weapon.speed=125;
								now_weapon.up_bullet=40;
								now_weapon.now_bullet=40;
								now_weapon.bullet_out="·";
								now_weapon.kill=10;
								now_weapon.bspeed=1000;
								system("cls");
								now_weapon.out();
								for(int i=0; i<15; i++)
									for(int j=0; j<15; j++) {
										gotoxy(j*2,i);
										if(map1[i][j]==1) cout<<"█";
										else cout<<"  ";
									}
								gotoxy(0,15);
								for(int i=0; i<15; i++) printf("==");
								last_blood=0;
								last_bullet=0;
								gotoxy(0,17);
								cout<<"Room:"<<roofff;
								break;
							}
							if(A2.Preserve()) {
								system("cls");
								for(int i=0; i<15; i++)
									for(int j=0; j<15; j++) {
										gotoxy(j*2,i);
										if(map1[i][j]==1) cout<<"█";
										else cout<<"  ";
									}
								gotoxy(0,15);
								for(int i=0; i<15; i++) printf("==");
								last_blood=0;
								last_bullet=0;
								gotoxy(0,17);
								cout<<"Room:"<<roofff;
								break;
							}
						}
					}
				}
				gotoxy(13,0);
				Color(3);
				cout<<"#[]#";
				shi[0][6]=shi[0][8]=true;
				if(User.x==0&&User.y==14) next_room();
			}
			if(bossid==3&&bosst.Get_time()>=10&&isboss&&zombie[1].boos_jn()&&bossto<=30&&!all_die()) {
				zombie[1].Boss_mode(1);
				bossto++;
			}
			if(bossto>30) {
				bossto=0;
				zombie[1].jt.replace();
			}
			ifUserdie();
			ifzbdie();
		}
		if(GetKeyState('R')<0) bt.last_time=clock(),sdcklm=true,woyebu=true;
		if(bt.Get_time()>=now_weapon.bspeed&&sdcklm) now_weapon.now_bullet=now_weapon.up_bullet,sdcklm=false,woyebu=false;
		disfly();
		monster_move();
	}
}
void jn() {
	kkll:
	srand(time(0));
	system("mode con cols=60 lines=20");
	bool isboss=false;
	int bossid;
	string l = "c:\\Roomfrc\\us\\"+User.name+"\\continue.txt";
	FILE *oppo=fopen(l.c_str(),"w");
	fprintf(oppo,"%d\n",1);
	fprintf(oppo,"%d %d\n",roofff,jejeje);
	fprintf(oppo,"%d %d %d %d %d\n",User.blood,User.up_blood,User.speed,User.hui,now_weapon.now_bullet);
	fprintf(oppo,"%d %s %d %s %s %s %d %d\n",now_weapon.bspeed,now_weapon.bullet_out.c_str(),now_weapon.kill,now_weapon.name.c_str(),now_weapon.ot1.c_str(),now_weapon.ot2.c_str(),now_weapon.speed,now_weapon.up_bullet);
	system("cls");
	zbnum=0;
	ghnum=0;
	for(int i=1; i<=20; i++) zbdie[i]=0;
	for(int i=1; i<=20; i++) ghdie[i]=0;
l:
	last_blood=-1;
	last_bullet=-1;
	int tttkkktmp=rand()%mapnum+1;
//    int tttkkktmp=10;
	if(start==true) tttkkktmp=0;
	if(tttkkktmp==9) isboss=true,bossid=3;
	string kkksc03;
	if(tttkkktmp==0) kkksc03="0";
	else while(tttkkktmp) {
			kkksc03=char(tttkkktmp%10+'0')+kkksc03;
			tttkkktmp/=10;
		}
	gotoxy(32,0);
	Color(12);
	cout<<"          ";
	gotoxy(32,0);
	Color(12);
	cout<<"map:NO."<<kkksc03;
	kkksc03="c:\\Roomfrc\\map\\"+kkksc03+".txt";
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++) map1[i][j]=0;
	int monster;
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++) shi[i][j]=map1[i][j];
	gotoxy(0,0);
	show_blood();
	gotoxy(0,15);
	for(int i=0; i<15; i++) printf("==");
	for(int i=0; i<20; i++) {
		gotoxy(30,i);
		cout<<"|";
	}
	Color(4);
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++) {
			gotoxy(j*2,i);
			if(map1[i][j]==1) cout<<"█";
			else cout<<"  ";
		}
	User.x=14;
	User.y=14;
	gotoxy(User.y,User.x);
	Color(3);
	printf("♀");
	now_weapon.out();
	gotoxy(0,17);
	cout<<"      ";
	gotoxy(0,17);
	Color(12);
	cout<<"Room:"<<roofff;
	gotoxy(14,16);
	cout<<"             ";
	gotoxy(14,16);
	cout<<"weapons:"<<now_weapon.name;
	gotoxy(14,7);
	cout<<"[]";
	gotoxy(12,7);
	cout<<"++";
	gotoxy(16,7);
	cout<<"++";
	gotoxy(14,8);
	cout<<"++";
	gotoxy(14,6);
	cout<<"++";
	gotoxy(14,9);
	cout<<"==";
	for(int i=1; i<=zbnum; i++) zombie[i].move();
	Timeh t,mt,bt,walkt,bllt,huit,bosst;
	bool sdcklm=false,woyebu=false,smoke=false;
	int alive1=rand()%15,alive2=rand()%15,moge=rand()%100+1,bossto=0;
	if(start) moge=101;
	start=false;
	HWND hwnd=GetForegroundWindow();
	while(shi[alive1][alive2]) alive1=rand()%15,alive2=rand()%15;
	while(1) {
		if(User.y==14&&User.x==9) {
			User.x=10;
			gotoxy(User.y,User.x);
			cout<<"♀";
			system("cls");
			cout<<"技能：嗜血\n攻击伤害+（血量上限-当前血量）/血量上限%";
			Button A1 = NewButton(16,8,3,4,"[确定]");
			Button A2 = NewButton(16,2,3,4,"[取消]");
			A1.out(),A2.out();
			while(1) {
				if(A1.Preserve()) {
					system("cls");
					SHIXUE=true;
					goto kkll;
				}
				if(A2.Preserve()) goto kkll;
			}
		}
	if(GetKeyState('M')<0) {
		ShowWindow(hwnd,SW_MINIMIZE);
		while(1) if(GetKeyState('O')<0) break;
	}
	if(GetKeyState('P')<0)  {
		Sleep(100);
		while(1) if(GetKeyState('O')<0) break;
	}
	if(walkt.Get_time()>=User.speed) {
		walk();
		walkt.replace();
	}
	if(!woyebu) GET_bullet(1,0);
	if(huit.Get_time()>=1000) {
		User.blood+=User.hui;
		if(User.blood>User.up_blood) User.blood=User.up_blood;
		huit.replace();
	}
	if(t.Get_time()>=200) {
		t.replace();
		show_blood();
		if(all_die()) {
			gotoxy(13,0);
			Color(3);
			cout<<"#[]#";
			shi[0][6]=shi[0][8]=true;
			if(User.x==0&&User.y==14) next_room();
		}
		if(bossid==3&&bosst.Get_time()>=10&&isboss&&zombie[1].boos_jn()&&bossto<=30) {
			zombie[1].Boss_mode(1);
			bossto++;
		}
		if(bossto>30) {
			bossto=0;
			zombie[1].jt.replace();
		}
		ifUserdie();
		ifzbdie();
	}
	if(GetKeyState('R')<0) bt.last_time=clock(),sdcklm=true,woyebu=true;
	if(bt.Get_time()>=now_weapon.bspeed&&sdcklm) now_weapon.now_bullet=now_weapon.up_bullet,sdcklm=false,woyebu=false;
	disfly();
	monster_move();
}
} 

void mobai() {
	system("cls");
	last_blood=0;
	for(int i=0; i<15; i++)
		for(int j=0; j<15; j++) shi[i][j]=false;
	User.x=14;
	User.y=14;
kk11:
	gotoxy(User.y,User.x);
	Color(3);
	printf("♀");
	now_weapon.out();
	gotoxy(0,17);
	cout<<"      ";
	gotoxy(0,17);
	cout<<"Room:"<<roofff;
	gotoxy(14,16);
	cout<<"weapons:       ";
	gotoxy(14,16);
	cout<<now_weapon.name;
	gotoxy(14,7);
	cout<<"♀";
	gotoxy(12,7);
	cout<<"##";
	gotoxy(16,7);
	cout<<"##";
	gotoxy(14,8);
	cout<<"##";
	gotoxy(14,6);
	cout<<"##";
	gotoxy(14,9);
	cout<<"==";
	shi[7][7]=shi[6][7]=shi[8][7]=shi[7][8]=shi[7][6]=1;
	gotoxy(0,15);
	for(int i=0; i<15; i++) printf("==");
	Timeh t,mt,bt,walkt,ballet_t,bllt,huit;
	bool sdcklm=false,woyebu=false;
	while(1) {
		if(User.y==14&&User.x==9&&!lintoto) {
			User.x=10;
			system("cls");
			cout<<" 犇犇之神：lin_to_to\n ltt的祝福：速度+50%，\n生命恢复+5\n\n洛谷之力：生命值回复满\n\n注意，一局游戏只能膜拜\n一个神像";
			Button A1 = NewButton(16,8,3,4,"[确定]");
			Button A2 = NewButton(16,2,3,4,"[取消]");
			A1.out(),A2.out();
			while(1) {
				if(A1.Preserve()) {
					User.speed=75;
					User.blood=User.up_blood;
					User.hui+=5;
					lintoto=true;
					break;
				}
				if(A2.Preserve()) break;
			}
			system("cls");
			goto kk11;
		}
		if(huit.Get_time()>=1000) {
			User.blood+=User.hui;
			if(User.blood>User.up_blood) User.blood=User.up_blood;
			huit.replace();
		}
		if(walkt.Get_time()>=User.speed) {
			walk();
			walkt.replace();
		}
		if(!woyebu) GET_bullet(1,0);
		if(t.Get_time()>=200) {
			gotoxy(14,9);
			cout<<"==";
			t.replace();
			show_blood();
			if(all_die()) {
				gotoxy(13,0);
				cout<<"#[]#";
				shi[0][6]=shi[0][8]=true;
			}
			if(User.x==0&&User.y==14) next_room();
			ifUserdie();
			ifzbdie();
		}
		disfly();
		monster_move();
		if(GetKeyState('R')<0) bt.last_time=clock(),sdcklm=true,woyebu=true;
		if(bt.Get_time()>=now_weapon.bspeed&&sdcklm) now_weapon.now_bullet=now_weapon.up_bullet,sdcklm=false,woyebu=false;
	}
}
void next_room() {
	roofff++;
	int dalao=MSrand()%100+1;
	if(dalao<=10) jn();
	else if(dalao>10&&dalao<=20) mobai();
	else make_map();
}

int main() {
A:
	system("cls");
	SetScreen(SMASIZE);
	srand(time(0));
	hidden(0);
	system("cls");
	Color(15);
	Endl(4);
	hidden(1);
	FILE* uin= fopen("c:\\Roomfrc\\User.txt","r");
	fscanf(uin,"%d",&unum);
	for(int i=0; i<unum; i++) {
		char ch1[20],ch2[20];
		fscanf(uin,"%s%s",&ch1,&ch2);
		us[i] = ch1;
		pw[i] = ch2;
	}
	fclose(uin);
	Draw(4,' ');
	cout<<"+------------------+"<<endl;
	Draw(4,' ');
	cout<<"|UserName:         |"<<endl;
	Draw(4,' ');
	cout<<"|------------------|"<<endl;
	Draw(4,' ');
	cout<<"|PassWord:         |"<<endl;
	Draw(4,' ');
	cout<<"+------------------+"<<endl;
	Endl(3);
	printf("Room v1.3.1\n");
	printf("Made from Look_cat_box\n");
	Endl(2);
	printf("  Ps: if you don't have account, please fill in the 'New' in the user name to register a new account.");
	gotoxy(14,5);
	cin>>tmp1;
	if(tmp1 == "New"/*创建新账户*/) {
		system("cls");
		Endl(4);
		Draw(2,' ');
		cout<<"+-------------------------+"<<endl;
		Draw(2,' ');
		cout<<"|Registered name:         |"<<endl;
		Draw(2,' ');
		cout<<"|-------------------------|"<<endl;
		Draw(2,' ');
		cout<<"|Login password:          |"<<endl;
		Draw(2,' ');
		cout<<"+-------------------------+"<<endl;
		gotoxy(19,5);
		cin>>tmp1;
		gotoxy(18,7);
		cin>>tmp2;
		if(tmp1 == "New") {
			MessageBox(NULL,"Illegal user name","Error",MB_OK|MB_ICONEXCLAMATION);
			return 0;
		}
		string l = "md c:\\Roomfrc\\us\\"+tmp1;
		system(l.c_str());
		FILE* out=fopen("c:\\Roomfrc\\User.txt","w");
		fprintf(out,"%d\n",unum+1);
		for(int i=0; i<unum; i++) fprintf(out,"%s %s\n",us[i].c_str(),pw[i].c_str());
		fprintf(out,"%s %s\n",tmp1.c_str(),tmp2.c_str());
		fclose(out);
		say("\n    Welcome "+tmp1,100);
		hidden(0);
		jz();
		menu();
	} else {
		gotoxy(14,7);
		cin>>tmp2;
		for(int i=0; i<unum; i++) if(us[i] == tmp1 && pw[i] == tmp2) {
				User.name = tmp1;
				User.word = tmp2;
				say("\n    Welcome "+tmp1,100);
				hidden(0);
				string fafafattt = "c:\\Roomfrc\\us\\"+User.name+"\\archive.txt";
				FILE *lttth=fopen(fafafattt.c_str(),"r");
				fscanf(lttth,"%d",&User.money);
				jz();
				menu();
			}
		MessageBox(NULL,"Wrong username or password","Error",MB_OK|MB_ICONEXCLAMATION);
		goto A;
	}

	return 0;
}
/*备用代码*/
// 初始化IP和端口信息
/*
    SOCKADDR_IN addrSrv;

    addrSrv.sin_family = AF_INET;

    addrSrv.sin_port = htons(port);

    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
*/
/*
WSADATA wsaData;

    int port = 5099;//端口

	// 关闭套接字

    closesocket(sockClient);

    WSACleanup();
*/
