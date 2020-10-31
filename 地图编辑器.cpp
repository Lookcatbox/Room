#include<bits/stdc++.h>
#include<c++play.h>
using namespace std;
int mapnum;
void chuanjian()
{
	system("cls");
	cout<<"请输入地图（15*15）：其中1为墙壁，0为空地"<<endl;
	int mapp[15][15];
	for(int i=0; i<15; i++)
	    for(int j=0; j<15; j++) cin>>mapp[i][j];
	FILE* map_num_out= fopen("c:\\Roomfrc\\mapnum.txt","w");
	fprintf(map_num_out,"%d",mapnum+1);
	mapnum++;
	int tttkkktmp=mapnum;
	string kkksc03;
	if(tttkkktmp==0) kkksc03="0";
	else while(tttkkktmp) {
			kkksc03=char(tttkkktmp%10+'0')+kkksc03;
			tttkkktmp/=10;
		}
	string str="c:\\Roomfrc\\map\\"+kkksc03+".txt";
	FILE *newmap = fopen(str.c_str(),"w");
	for(int i=0; i<15; i++) {
		for(int j=0; j<15; j++) fprintf(newmap,"%d ",mapp[i][j]);
		fprintf(newmap,"\n");
	}
	system("cls");
	cout<<"请输入怪物(第一行为数量，之后每一行三个参数：x坐标，y坐标，怪物类型)"<<endl;
	int gn;
	cin>>gn;
	fprintf(newmap,"%d\n",gn);
	for(int i=1; i<=gn; i++) {
		int a,b,c;
		cin>>a>>b>>c;
		fprintf(newmap,"%d %d %d\n",a,b,c);
	} 
 } 
int main()
{
	cout<<"欢迎来到Room 地图编辑器"<<endl;
	FILE* map_num_in= fopen("c:\\Roomfrc\\mapnum.txt","r");
	fscanf(map_num_in,"%d",&mapnum); 
	cout<<"现有地图："<<mapnum<<"张"<<endl;
	Button A1 = NewButton(3,0,3,4,"[创建地图]");
	A1.out();
	while(1) {
		if(A1.Preserve()) chuanjian();
	}
	A1.out();
	return 0;
}

