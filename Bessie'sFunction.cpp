#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<cassert>
#include<unordered_map>
#include <queue>
#include <cstdint>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric>
#include<complex>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define s second
#define pii pair<int,int>
#define ppii pair<int,pii>
#define vi vector<int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-lopps")
#define int long long
#define double long double
using namespace std;
using cd = complex<double>;
double const PI=acos(-1);
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int k,m,n,q,d;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int v[mxn+10],c[mxn+10],vis[mxn+10],T=0;
int ishead[mxn+10];
vector<int>adj[mxn+10];
stack<int>st;
vector<int>head[mxn+10];
int on[mxn+10];
void getcycle(int cur){
	if(vis[cur]){
		while(st.top()!=cur){
			if(st.empty())assert(0);
			head[T].pb(st.top());
			if(ishead[st.top()])assert(0);
			ishead[st.top()]=1;
			st.pop();
		}
		ishead[cur]=1;
		head[T].pb(cur);
		T++;
		return;
	}
	vis[cur]=1;
	st.push(cur);
	on[cur]=1;
	for(auto i:adj[cur]){
		if(vis[i]&&on[i]==0)continue;
		getcycle(i);
	}
	if(!st.empty())st.pop();
	on[cur]=0;
}
int dp[mxn+10][2],vis2[mxn+10],sz2[mxn+10];
void solve(int cur){
	dp[cur][0]=0;
	dp[cur][1]=c[cur];
	if(ishead[cur]&&sz2[cur]==1)dp[cur][1]=0;
	for(auto j:adj[cur])if(!ishead[j]){
		solve(j);
		dp[cur][0]+=dp[j][1];
		dp[cur][1]+=min(dp[j][1],dp[j][0]);
	}
}
int dp2[mxn+10][2][2];
int32_t main(){
	fastio
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>v[i],adj[v[i]].pb(i);
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++)if(!vis[i]){
		getcycle(i);
	}
	for(int i=0;i<T;i++)for(auto j:head[i])sz2[j]=head[i].size();
	for(int i=1;i<=n;i++)if(ishead[i]){
		solve(i);
	}
	int ans=0;
	for(int i=0;i<T;i++){
		for(int k=0;k<2;k++)for(int g=0;g<2;g++)dp2[0][g][k]=inf;
		for(int k=0;k<2;k++)dp2[0][k][k]=dp[head[i][0]][k];
		for(int j=1;j<head[i].size();j++){
			for(int k=0;k<2;k++)for(int g=0;g<2;g++)dp2[j][g][k]=inf;
			for(int k=0;k<2;k++){
				dp2[j][k][0]=min(dp2[j][k][0],dp2[j-1][k][1]+dp[head[i][j]][0]);
				dp2[j][k][1]=min(dp2[j][k][1],min(dp2[j-1][k][0],dp2[j-1][k][1])+dp[head[i][j]][1]);
			}
		}
		int x=min({dp2[head[i].size()-1][1][0],dp2[head[i].size()-1][0][1],dp2[head[i].size()-1][1][1]});
		if(head[i].size()==1)x=min(x,dp2[head[i].size()-1][0][0]);
		ans+=x;
	}
	cout<<ans;
}
/*

*/