#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
#include<bitset>
#include <iomanip>  
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "library.h"
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define ppii pair<pii,int>
#define vi vector<int>
#define pb push_back
//#define p push
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
#pragma GCC optimize ("03,unroll-lopps")
const int mxn=1e3+10,inf=1e9;
deque<int>group[mxn+10];
int pos[mxn+10];
vector<int>q,realans;
vector<pii>adj[mxn+10];
bitset<mxn+10>vis;
void dfs(int cur,int p){
	if(group[pos[cur]][0]!=cur)reverse(all(group[pos[cur]]));
	for(auto j:group[pos[cur]]){
		if(!vis[j])realans.pb(j),vis[j]=true;
	}
	for(auto i:adj[cur]){
		if(i.f==p)continue;
		if(i.s<0)realans.pb(-i.s);
		dfs(i.f,cur);
	}
	if(adj[cur].size()!=1)return;
}
int keep,keep2;
void Solve(int n){
	int cnt=1;
	vector<pii>v;
	q.resize(n,0);
	group[0].pb(1);
	v.pb({1,1});
	for(int i=2;i<=n;i++){
		bool yes=false;
		fill(all(q),0);
		for(int j=0;j<=v.size()-1;j++)for(auto k:group[j])q[k-1]=1;
		q[i-1]=1;
		if(Query(q)-(v.size())==-1)yes=true;
		int l=0,r=v.size()-1,ans=inf,ans2=inf;
		while(l<=r){
			int mid=l+(r-l)/2;
			fill(all(q),0);
			for(int j=0;j<=mid;j++)for(auto k:group[j])q[k-1]=1;
			q[i-1]=1;
			int tmp=Query(q);
			if(tmp-(mid+1)<=0){
				r=mid-1;
				if(tmp-(mid+1)==0)ans=min(ans,mid);
			}
			else l=mid+1;
		}
		if(ans==inf){
			v.pb({i,i});
			group[cnt++].pb(i);
		}
		else{
			fill(all(q),0);
			q[i-1]=1;
			q[v[ans].f-1]=1;
			if(Query(q)==1){
				keep=v[ans].f;
				if(!yes)group[ans].push_front(i),v[ans].f=i;
			}
			else{
				keep=v[ans].s;
				if(!yes)group[ans].pb(i),v[ans].s=i;
			}
		}
		if(!yes)continue;
		l=ans,r=v.size()-1;
		while(l<=r){
			fill(all(q),0);
			int mid=l+(r-l)/2;
			q[i-1]=1;
			for(int j=0;j<=mid;j++)for(auto k:group[j])q[k-1]=1;
			if(Query(q)-(mid+1)==-1)r=mid-1,ans2=min(ans2,mid);
			else l=mid+1;
		}
		fill(all(q),0);
		q[i-1]=1;
		q[v[ans2].f-1]=1;
		if(Query(q)==1)keep2=v[ans2].f;
		else keep2=v[ans2].s;
		adj[keep].pb({keep2,-i});
		adj[keep2].pb({keep,-i});
	}
	for(int i=0;i<v.size();i++){
		if(v[i].f==v[i].s)continue;
		adj[v[i].f].pb({v[i].s,i});
		adj[v[i].s].pb({v[i].f,i});
	}
	for(int i=0;i<cnt;i++)for(auto j:group[i])pos[j]=i;
	int st=0;
	for(int i=1;i<=n;i++){
		if(adj[i].size()==1)st=i;
	}
	dfs(st,-1);
	Answer(realans);
}
