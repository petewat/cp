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
#include <iomanip>
#include<numeric>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
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
#pragma GCC optimize ("03,unroll-loops")
using namespace std;
#define int long long
const int mod=1e9+7,mxn=2e5+5,lg=30,inf=1e18,minf=-1e18;
// ->, <-, all node that follow in component||node of that component
int n,k;
int h[mxn+10],up[mxn+10][lg+5],g[mxn+10],gl[mxn+10];
struct dsu{
	int pa[mxn+10],head[mxn+10],sz[mxn+10];
	void init(){for(int i=1;i<=mxn;i++)pa[i]=i,sz[i]=1;}
	int find(int u){return pa[u]==u?u:pa[u]=find(pa[u]);}
	void merg(int a,int b){
		a=find(a),b=find(b);
		if(a==b)return;
		if(sz[a]>sz[b])swap(a,b);
		pa[b]=a;
		sz[a]+=sz[b];
		if(h[head[a]]>h[head[b]])head[a]=head[b];
	}

}d[2];

vector<int>adj[mxn+10],group[mxn+10];
void dfs(int cur,int p){
	for(auto i:adj[cur]){
		if(i==p)continue;
		h[i]=h[cur]+1;
		up[i][0]=cur;
		dfs(i,cur);
	}
}
int lca(int a,int b){
	if(h[a]<h[b])swap(a,b);
	int k=h[a]-h[b];
	for(int i=0;i<=lg;i++)if(k&(1<<i))a=up[a][i];
	if(a==b)return a;
	for(int i=lg;i>=0;i--)if(up[a][i]!=up[b][i])a=up[a][i],b=up[b][i];
	return up[a][0];
}
bool cmp(int a,int b){return h[gl[a]]>h[gl[b]];}
int32_t main(){
	fastio
	cin>>n>>k;
	for(int i=0;i<n-1;i++){
		int a,b;cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	d[0].init();
	d[1].init();
	dfs(1,-1);
	for(int i=1;i<=n;i++)cin>>g[i],group[g[i]].pb(i),d[0].head[i]=i;
	for(int i=1;i<=lg;i++)up[1][i]=1;
	for(int i=1;i<=lg;i++)for(int j=1;j<=n;j++)up[j][i]=up[up[j][i-1]][i-1];
	vector<int>v;
	for(int i=1;i<=k;i++){
		if(group[i].empty())continue;
		int node=group[i][0];
		for(int j=1;j<group[i].size();j++)node=lca(node,group[i][j]);
		gl[i]=node;
		d[1].head[i]=node;
		v.pb(i);
	}
	int ans=inf;
	sort(all(v),cmp);
	int c1=0;
	for(auto i:v){
		cout<<i<<"A\n";
		int cnt=0;
		for(auto j:group[i]){
			int cur=j;
			cur=d[0].find(cur);
			while(h[up[cur][0]]>=h[gl[i]]){
				if(cur==1)break;
				d[0].merg(cur,up[cur][0]);
				d[1].merg(g[cur],g[up[cur][0]]);
				cur=d[0].head[d[0].find(cur)];
				cnt++;
			}
		}
		if(d[1].head[d[1].find(gl[i])]==gl[i]){
			cout<<i<<"C----\n";
			cout<<d[1].sz[d[1].find(gl[i])]<<"G\n";
			ans=min(ans,d[1].sz[d[1].find(gl[i])]);
		}
		c1++;
	}
	cout<<ans-1;
	return 0;
}
