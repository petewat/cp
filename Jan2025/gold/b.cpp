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
#define double long double
using namespace std;
const int mod=1e9+7,mxn=5e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
string S;
pii e[mxn+10];
vector<int>adj[mxn+10];
int pa[mxn+10],sz[mxn+10],ans[mxn+10],T=0,ca=0;
int find(int u){return (pa[u]==u)?u:pa[u]=find(pa[u]);}
int get(int x){return (x*(x-1))/2;}
void merge(int a,int b){
    a=find(a),b=find(b);
    if(a==b)return;
    pa[b]=a;
    ca-=(get(sz[a])+get(sz[b]));
    sz[a]+=sz[b];
    ca+=get(sz[a]);
}
int act(int x){
    x=find(x);
    ca-=get(sz[x]);
    sz[x]++;
    ca+=get(sz[x]);
}
int32_t main(){
    fastio
	cin>>n>>m;
    cin>>S;
    for(int i=1;i<=n;i++)pa[i]=i;
    for(int i=0;i<m;i++){
        cin>>e[i].f>>e[i].s;
        if(e[i].f>e[i].s)swap(e[i].f,e[i].s);
        if(S[e[i].f-1]=='1'&&S[e[i].s-1]=='1'){
            merge(e[i].f,e[i].s);
        }
        else if(S[e[i].f-1]=='1'){
            adj[e[i].s].pb(e[i].f);
        }
        else adj[e[i].f].pb(e[i].s);
        
    }
    for(int i=n;i>=1;i--){
        act(i);
        for(auto j:adj[i])merge(j,i);
        ans[i]=ca;
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<'\n';
}
/*
*/