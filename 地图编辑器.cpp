#include<bits/stdc++.h>
#include<c++play.h>
using namespace std;
int mapnum;
void chuanjian()
{
	system("cls");
	cout<<"�������ͼ��15*15��������1Ϊǽ�ڣ�0Ϊ�յ�"<<endl;
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
	cout<<"���������(��һ��Ϊ������֮��ÿһ������������x���꣬y���꣬��������)"<<endl;
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
	cout<<"��ӭ����Room ��ͼ�༭��"<<endl;
	FILE* map_num_in= fopen("c:\\Roomfrc\\mapnum.txt","r");
	fscanf(map_num_in,"%d",&mapnum); 
	cout<<"���е�ͼ��"<<mapnum<<"��"<<endl;
	Button A1 = NewButton(3,0,3,4,"[������ͼ]");
	A1.out();
	while(1) {
		if(A1.Preserve()) chuanjian();
	}
	A1.out();
	return 0;
}

