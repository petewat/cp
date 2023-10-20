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
#define ppii pair<pii,pii>
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
#define int long long
const int mod=9901,mxn=2*1e5+5,inf=1e18,lg=25,minf=-1e18;

void setIO(string name) {		
    ios_base::sync_with_stdio(0); cin.tie(0);		
    freopen((name+".in").c_str(),"r",stdin);		
    freopen((name+".out").c_str(),"w",stdout);	
}
vector<int>adj[mxn+10];
int he[mxn+10],sz[mxn+10],hvy[mxn+10],up[mxn+10][lg+5],top[mxn+10],id[mxn+10];
int t=1;
int fwk[mxn+10],n,m;
void update(int pos,int val){for(int i=pos;i<=n;i+=(i&-i))fwk[i]+=val;}
int q(int pos){
    int ans=0;
    for(int i=pos;i>0;i-=(i&-i))ans+=fwk[i];
    return ans;
}
void dfs(int cur,int p){
    sz[cur]=1;
    for(auto i:adj[cur]){
        if(i==p)continue;
        he[i]=he[cur]+1;
        up[i][0]=cur;
        dfs(i,cur);
        sz[cur]+=sz[i];
        if(hvy[cur]==-1||sz[hvy[cur]]<sz[i])hvy[cur]=i;
    }
}
void hld(int cur,int p,int h){
    top[cur]=h,id[cur]=t++;
    if(hvy[cur]!=-1)hld(hvy[cur],cur,h);
    for(auto i:adj[cur]){
        if(i==hvy[cur]||i==p)continue;
        hld(i,cur,i);
    }
}
int lca(int a,int b){
    if(he[a]<he[b])swap(a,b);
    int k=he[a]-he[b];
    for(int i=0;i<=lg;i++)if(k&(1<<i))a=up[a][i];
    if(a==b)return a;
    for(int i=lg;i>=0;i--){
        if(up[a][i]!=up[b][i]){
            a=up[a][i];
            b=up[b][i];
        }
    }
    return up[a][0];
}
void upd(int a,int b){
    int cnt=0;
    while(top[a]!=top[b]){
        update(id[top[a]],1);
        update(id[a]+1,-1);
        a=up[top[a]][0];
        cnt++;
    }
    update(id[b],1);
    update(id[a]+1,-1);
}
int qry(int a,int b){
    int sum=0;
    while(top[a]!=top[b]){
        sum+=q(id[a]);
        a=up[top[a]][0];
    }
    sum+=q(id[a]);
    return sum;
}
int32_t main(){
    fastio
    cin>>n>>m;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    fill(hvy,hvy+n+1,-1);
    dfs(1,-1);
    hld(1,-1,1);
    for(int j=1;j<=lg;j++)for(int i=1;i<=n;i++)up[i][j]=up[up[i][j-1]][j-1];
    while(m--){
        char a;cin>>a;
        int u,v;cin>>u>>v;
        int node=lca(u,v);
        if(a=='P'){
            upd(u,node);
            upd(v,node);
            update(id[node],-2);
            update(id[node]+1,2);
        }
        else {
            if(he[u]<he[v])swap(u,v);
            cout<<q(id[u])<<'\n';
        }
    }
}
