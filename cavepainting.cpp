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
#pragma GCC optimize ("03,unroll-loops")
#define int long long
const int mod=1e9+7,mxn=1001,lg=30,inf=1e18,minf=-1e18,Mxn=2e6,root=700;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}	 
char grid[mxn+10][mxn+10];
int n,m;
int pa[mxn+10][mxn+10],up[mxn+10][mxn+10],cnt=1;
int id[mxn+10][mxn+10],dp[mxn*mxn+10];
int ccnt=0,group=0,curmul=1;
int find(int x,int y){return (pa[x][y]==y)?y:pa[x][y]=find(x,pa[x][y]);}
void merg(int x,int y,int x2,int y2){
	int a=find(x,y),b=find(x2,y2);
	if(a==b)return;
	pa[x][a]=b;
}
bool valid(int nx,int ny){
	if(nx<1||ny<1||nx>n||ny>m)return false;
	if(grid[nx][ny]=='#')return false;
	return true;
}
bool use[mxn+10][mxn+10];
vector<int>adj[mxn*mxn+10];
void pull(int i){
	dp[i]=1;
	for(auto j:adj[i])dp[i]=(dp[i]*dp[j])%mod;
	dp[i]++;
}
int32_t main(){
	setIO("cave");
	fastio
	cin>>n>>m;
	int ans=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>grid[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(grid[i][j]=='.')pa[i][j]=j;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++)if(grid[i][j]=='.')if(valid(i,j+1))merg(i,j,i,j+1);
		for(int j=1;j<=m;j++)if(grid[i][j]=='.'){
			if(valid(i+1,j)){
				if(!up[i+1][find(i+1,j)])up[i+1][find(i+1,j)]=j;
				else merg(i,j,i,up[i+1][find(i+1,j)]);
			}
		}
	}
	for(int i=n;i>=1;i--)for(int j=1;j<=m;j++)if(find(i,j)==j&&grid[i][j]=='.')id[i][j]=cnt++;
	for(int i=n;i>=1;i--)for(int j=1;j<=m;j++)if(find(i,j)==j){
		if(up[i][j])adj[id[i-1][find(i-1,up[i][j])]].pb(id[i][j]);
		else adj[0].pb(id[i][j]);
	}
	for(int i=1;i<cnt;i++)pull(i);
	pull(0);
	cout<<(dp[0]-1+mod)%mod;
/*


*/
}