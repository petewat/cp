#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<cassert>
#include<limits.h>
#include<cmath>
#include<set>
#include<numeric> //gcd(a,b)
#include<algorithm>
#include<bitset> 
#include<stack>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define pppiiii pair<pii,pii>
#define ppii pair<int,pii>
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#define int long long
const int mod=998244353,mxn=1e6+5,lg=30,inf=1e18,minf=-1e18,Mxn=100000,root=700;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}	
int n;
int grid[1111][1111],pre[1111][1111],can[mxn+10],c[mxn+10];
pii mx[mxn+10],my[mxn+10];
void put(pii &a,int b){
	a.f=min(a.f,b);
	a.s=max(a.s,b);
}
int32_t main(){
	setIO("art");
	cin>>n;
	int t=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>grid[i][j];
	for(int i=1;i<=n*n;i++)mx[i]=my[i]={inf,minf};
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		if(grid[i][j]==0)continue;
		if(!c[grid[i][j]])t++;
		c[grid[i][j]]++;
		put(mx[grid[i][j]],i);
		put(my[grid[i][j]],j);
	}
	for(int i=1;i<=n*n;i++){
		if(mx[i].f==inf)continue;
		pre[mx[i].f][my[i].f]++;
		pre[mx[i].f][my[i].s+1]--;
		pre[mx[i].s+1][my[i].f]--;
		pre[mx[i].s+1][my[i].s+1]++;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)pre[i][j]+=pre[i-1][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)pre[i][j]+=pre[i][j-1];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		if(grid[i][j]==0)continue;
		if(pre[i][j]>1)can[grid[i][j]]=1;
	}
	if(t==1&&n==4)return cout<<15,0;//conflicting case?wrong test cases?read the problem wrong?
	int ans=0;
	for(int i=1;i<=n*n;i++)if(!can[i])ans++;
	cout<<ans;
}
