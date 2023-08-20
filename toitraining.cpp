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
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define ppii pair<int,pii>
#define pll pair<ll,ll>
#define pb push_back
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
const int mxn=3*1e5,lg=20;
#define int long long
int n,q;
int val[mxn+10],jump[mxn+10][lg+1],h[mxn+10],down[mxn+10],dist[mxn+10],up[mxn+10];
int extra[mxn+10],all[mxn+10];
vector<pii>adj[mxn+10];
void solve(int cur,int p){
    down[cur]=val[cur];
    for(auto i:adj[cur]){
        if(i.f==p)continue;
        h[i.f]=h[cur]+1;
        jump[i.f][0]=cur;
        solve(i.f,cur);
        down[cur]+=max(0ll,down[i.f]-(2*i.s));
        extra[i.f]=max(0ll,down[i.f]-(2*i.s));
        all[cur]+=extra[i.f];
    }
}
void solve2(int cur,int p){
    for(auto i:adj[cur]){
        if(i.f==p)continue;
        dist[i.f]=dist[cur]+(down[cur]-max(0ll,down[i.f]-(2*i.s)))-i.s;
        up[i.f]=max(0ll,up[cur]+(down[cur]-max(0ll,down[i.f]-(2*i.s)))-2*i.s);
        solve2(i.f,cur);
    }
}
int b4a=0,b4b=0;
int lca(int a,int b){
    if(h[a]<h[b])swap(a,b);
    int k=h[a]-h[b];
    for(int i=0;i<=lg;i++)if(k&(1<<i))a=jump[a][i];
    if(a==b)return a;
    for(int i=lg;i>=0;i--){
        if(jump[a][i]!=jump[b][i]){
            a=jump[a][i];
            b=jump[b][i];
        }
    }
    b4a=a;
    b4b=b;
    return jump[a][0];
}
int32_t main(){
    fastio
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>val[i];
    for(int i=0;i<n-1;i++){
        int u,v,w;cin>>u>>v>>w;
        adj[v].pb({u,w});
        adj[u].pb({v,w});
    }
    solve(1,-1);
    solve2(1,-1);
    for(int i=1;i<=lg;i++)for(int j=1;j<=n;j++)jump[j][i]=jump[jump[j][i-1]][i-1];
    while(q--){
        int u,v;cin>>u>>v;
        int node=lca(u,v);
        if(node==u||node==v){
            if(node==v)swap(u,v);
            cout<<up[node]+down[v]+(dist[v]-dist[node])<<'\n';
        }
        else{
            int ans=down[u]+down[v]+up[node]+(dist[u]+dist[v])-(2*dist[node])-val[node]-all[node];
            cout<<ans<<'\n';
        }
    }   
    return 0;
}