#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<algorithm>
#include<limits.h>
#include<cmath>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define ppii pair<pii,int>
#define pb push_back
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
//#define int long long
#define mod 1000000007
#define int long long
const int mxn=1e5,lg=20;
vector<int>adj[mxn+10];
int h[mxn+10],up[mxn+10][lg+10],ans[mxn+10],add[mxn+10],tin[mxn+10];
int t=0;
void solve(int cur,int p){
    tin[cur]=t++;
    for(auto i:adj[cur]){
        if(i==p)continue;
        up[i][0]=cur;
        h[i]=h[cur]+1;
        solve(i,cur);
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
int caldist(int a,int b){
    int node=lca(a,b);
    return h[a]+h[b]-(2*h[node]);
}
bool isancestor(int a,int b){
    if(h[a]>h[b])return false;
    int k=h[b]-h[a];
    for(int i=0;i<=lg;i++)if(k&(1<<i))b=up[b][i];
    return a==b;
}
int push(int cur,int p){
    for(auto i:adj[cur]){
        if(i==p)continue;
        ans[cur]+=push(i,cur);
        add[cur]+=add[i];
    }
    //cout<<cur<<" "<<ans[cur]<<" "<<add[cur]<<'\n';
    return ans[cur]+add[cur];
}
int32_t main(){
    fastio
    int n,m;cin>>n>>m;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        adj[v].pb(u);
        adj[u].pb(v);
    }
    solve(1,-1);
    for(int i=1;i<=lg;i++)for(int j=1;j<=n;j++)up[j][i]=up[up[j][i-1]][i-1];
    while(m--){
        int a,b,c;cin>>a>>b>>c;
        int node=lca(a,b);
        int c1=lca(a,c),c2=lca(b,c);
        /*
        int g=b;
        if(h[b]<h[a])g=a;
        if((isancestor(g,c))){
            add[a]++;
            add[b]++;
            add[node]-=2;
            add[node]-=caldist(node,c);
            if(node!=a)ans[a]+=caldist(a,c);
            if(node!=b)ans[b]+=caldist(b,c);
            continue;
        }
        */
        //is node an ancestor of c1
        //if not == not in subtree
        int g;
        if(!isancestor(node,c1))c1=node;
        if(!isancestor(node,c2))c2=node;
        if(isancestor(a,c1))c1=a;
        if(isancestor(b,c2))c2=b;
        if(h[c1]>h[c2])g=c1;
        else g=c2;
        add[g]+=2;
        add[a]--;
        add[b]--;
        ans[node]-=caldist(node,c);
        ans[up[node][0]]-=caldist(node,c);
        ans[a]+=caldist(c,a);
        ans[b]+=caldist(c,b);
    }
    push(1,-1);
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}
