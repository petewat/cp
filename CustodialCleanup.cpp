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
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
vector<int>adj[mxn+10];
int C[mxn+10],S[mxn+10],F[mxn+10];
int vis[mxn+10],have[mxn+10],cnt[mxn+10],vis2[mxn+10];
stack<int>st[mxn+10];
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>C[i];
	for(int i=1;i<=n;i++)cin>>S[i];
	for(int i=1;i<=n;i++)cin>>F[i];
	for(int i=0;i<m;i++){
		int a,b;cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	queue<int>q;
	have[S[1]]=1;
	q.push(1);
	while(!q.empty()){
		int cur=q.front();
		q.pop();
		if(vis[cur])continue;
		vis[cur]=1;
		while(!st[S[cur]].empty())q.push(st[S[cur]].top()),st[S[cur]].pop();
		have[S[cur]]=1;
		for(auto i:adj[cur])if(!vis[i]){
			if(have[C[i]])q.push(i);
			else st[C[i]].push(i);
		}
	}
	int yes=1;
	for(int i=1;i<=n;i++){
		if((!vis[i])&&(F[i]!=S[i]))yes=0;
	}
	for(int i=1;i<=n;i++){
		have[i]=0;
		while(!st[i].empty())st[i].pop();
	}
	if(yes){
		q.push(1);
		have[F[1]]=1;
		while(!q.empty()){
			int cur=q.front();
			q.pop();
			if(vis2[cur])continue;
			if(!vis[cur])continue;
			vis2[cur]=1;
			while(!st[F[cur]].empty())q.push(st[F[cur]].top()),st[F[cur]].pop();
			have[F[cur]]=1;
			for(auto i:adj[cur])if(!vis2[i]&&vis[i]){
				if(have[C[i]])q.push(i);
				else if(C[i]==F[i])q.push(i);
				else st[C[i]].push(i);
			}
		}
		for(int i=1;i<=n;i++)if(vis[i])yes&=vis2[i];
	}
	if(yes)cout<<"YES\n";
	else cout<<"NO\n";
	for(int i=1;i<=n;i++){
		vis[i]=vis2[i]=0;
		adj[i].clear(),have[i]=0;
		while(!st[i].empty())st[i].pop();
	}
}
int32_t main(){
    fastio
	int t;cin>>t;
	while(t--)solve();	
}
/*
*/