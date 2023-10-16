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
#include<stack>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<ll,ll>
#define pppiiii pair<pii,pii>
#define ppii pair<ll,pii>
#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
const int mxn=1e6+1;
ll inf=1e9+10;
vector<pii>adj[mxn+10];
ll sz[mxn+10],n,k,mn[mxn+10];
ll ans=inf;
bitset<mxn+10>del;
vector<ll>in;
void dfs(int cur,int p){
    sz[cur]=1;
    for(auto i:adj[cur])if(i.f!=p&&(!del[i.f]))dfs(i.f,cur),sz[cur]+=sz[i.f];
}
int getcen(int cur,int p,int g){
	for(auto i:adj[cur]){
		if(i.f==p||del[i.f])continue;
		if(sz[i.f]*2>g)return getcen(i.f,cur,g);
	}
	return cur;
}
void solve(int cur,int p,ll d,ll di){
    if(di>k)return;
    if(mn[k-di]!=inf)ans=min(ans,mn[k-di]+d);
    for(auto i:adj[cur]){
        if(i.f==p||del[i.f])continue;
        solve(i.f,cur,d+1,di+i.s);
    }
}
void upd(int cur,int p,ll d,ll di){
    if(di>k)return;
    mn[di]=min(mn[di],d);
    in.pb(di);
    for(auto i:adj[cur]){
        if(i.f==p||del[i.f])continue;
        upd(i.f,cur,d+1,di+i.s);
    }
}
void decomp(int cur){
    dfs(cur,-1);
    int node=getcen(cur,-1,sz[cur]);
    in.clear();
    for(auto i:adj[node]){
        if(del[i.f])continue;
        solve(i.f,node,1,i.s);
        upd(i.f,node,1,i.s);
    }
    del[node]=true;
    for(auto i:in)mn[i]=inf;
    for(auto i:adj[node])if(!del[i.f])decomp(i.f);
}
int best_path(int N, int K, int H[][2], int L[]){
	n=N;
    k=K;
	for(int i=0;i<N-1;i++){
		adj[H[i][0]].pb({H[i][1],L[i]});
		adj[H[i][1]].pb({H[i][0],L[i]});
	}
    fill(mn,mn+mxn+1,inf);
    mn[0]=0;
    decomp(0);
    if(ans==inf)ans=-1;
    return ans;
}/*
int main(){
    cin>>n>>k;
    int h[n][2],l[n];
    for(int i=0;i<n-1;i++)cin>>h[i][0]>>h[i][1]>>l[i];
    cout<<best_path(n,k,h,l);
}*/
