#include<bits/stdc++.h>
using namespace std;
int n,m,s,ta,tb,fa[500010],t[500010][24],sd[500010]; 
vector<int> vip[500010];
void gett() {
	for(int i=1; i<=n; i++) t[i][0]=fa[i];
	for(int i=1; i<=23; i++) 
		for(int j=1; j<=n; j++) t[j][i]=t[t[j][i-1]][i-1];
}
void bfs(int start) {
	queue<int> q;
	q.push(start);
	fa[start]=start,sd[start]=0;
	while(!q.empty()) {
		int now=q.front();
		for(int i=0; i<vip[now].size(); i++) {
			int then=vip[now][i];
			if(then==fa[now]) continue;
			fa[then]=now,sd[then]=sd[now]+1;
			q.push(then);
		}
		q.pop();
	}
}
int find_father(int no1,int no2) {
    if(sd[no1]>sd[no2]) swap(no1,no2);
    for(int i=22; i>=0; i--) if(sd[no1]<=sd[t[no2][i]]) no2=t[no2][i];
    if(no1==no2) return no1;
    for(int i=22; i>=0; i--) {
    	if(t[no1][i]!=t[no2][i]){
    		no1=t[no1][i];
    		no2=t[no2][i];
		}
	
    for(int i=1; i<n; i++) {
    	cin>>ta>>tb;
    	vip[ta].push_back(tb),vip[tb].push_back(ta);
	}
	bfs(s);
	gett(); 
	for(int i=1; i<=m; i++) { 
		int x1,x2;
		cin>>x1>>x2;
		cout<<find_father(x1,x2)<<endl;
	}
	return 0;
}

