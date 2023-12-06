#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<limits.h>
#include <cassert>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric> //gcd(a,b)
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
vector<pii>e,adj[mxn+10];
int hvy[mxn+10],pos[mxn+10],h[mxn+10],up[mxn+10][lg+10],sz[mxn+10],hvypa[mxn+10];
int last[mxn+10],mx[mxn+10],pa[mxn+10];
bitset<mxn+10>on;
int n;
void dfs(int cur,int p){
    for(auto i:adj[cur]){
        if(i.f==p)continue;
        h[i.f]=h[cur]+1;
        up[i.f][0]=cur;
        dfs(i.f,cur);
        sz[cur]+=sz[i.f];
    }
    sz[cur]++;
}
int cnt=1;
void hld(int cur,int p,int phvy){
    pos[cur]=cnt++;
    hvypa[cur]=phvy;
    for(auto i:adj[cur])if(i.f!=p&&sz[hvy[cur]]<sz[i.f])hvy[cur]=i.f;
    if(hvy[cur])hld(hvy[cur],cur,phvy);
    for(auto i:adj[cur])if(i.f!=p&&i.f!=hvy[cur])hld(i.f,cur,i.f);
}
struct seg{
    bool v[2*mxn+10];
    void init(){for(int i=0;i<=2*mxn+5;i++)v[i]=false;}
    void update(int pos,bool val){
        pos+=n+1;
        v[pos]=val;
        for(;pos>0;pos>>=1)v[pos>>1]=(v[pos]&v[pos^1]);
    }
    bool qry(int l,int r){
        bool ans=true;
        for(l+=n+1,r+=n+1;l<=r;l>>=1,r>>=1){
            if(l&1)ans&=(v[l++]);
            if(!(r&1))ans&=(v[r--]);
        }
        return ans;
    }
}t;
struct fen{
    int fwk[mxn+10];
    void init(){for(int i=0;i<=mxn+5;i++)fwk[i]=0;}
    void update(int pos,int val){for(int i=pos;i<=n;i+=(i&-i))fwk[i]+=val;}
    int qry(int pos){
        int sum=0;
        for(int i=pos;i>0;i-=(i&-i))sum+=fwk[i];
        return sum;
    }
}f;

void upd(int st,int above,int val){
    int cur=st;
    while(hvypa[cur]!=hvypa[above]){
        f.update(pos[cur]+1,-val);
        f.update(pos[hvypa[cur]],val);
        cur=up[hvypa[cur]][0];
    }
    f.update(pos[cur]+1,-val);
    f.update(pos[above],val);
}
int check(int st,int m){
    bool ans=true;
    int cur=st,above=st;
    for(int i=0;i<=lg;i++)if(m&(1<<i))above=up[above][i];
    while(hvypa[cur]!=hvypa[above]){
        ans&=t.qry(pos[hvypa[cur]],pos[cur]);
        cur=up[hvypa[cur]][0];
    }
    ans&=t.qry(pos[above],pos[cur]);
    if(ans)return above;
    return 0;
}
int findpa(int cur){
    int l=0,r=h[cur],ans=minf;
    while(l<=r){
        int mid=(l+r)/2;
        int g=check(cur,mid);
        if(g){
            l=mid+1;
            if(ans==minf||h[ans]>h[g])ans=g;
        }
        else r=mid-1;
    }
    return (ans==minf?cur:ans);
}
int cmx=minf;
int find(int a){
    if(pa[a]==a)return pa[a];
    if(on[a]){
        if(pa[a]==0)pa[a]=up[a][0];
        pa[a]=find(pa[a]);
        mx[a]=max({mx[pa[a]],mx[a],mx[up[a][0]]});
    }
    else pa[a]=a;
    return pa[a];
}
void findans(int cur,int p){
    if(!on[cur])cmx=max(mx[cur],f.qry(pos[cur]));
    else cmx=max({cmx,mx[cur],f.qry(pos[cur])});
    mx[cur]=cmx;
    for(auto i:adj[cur])if(i.f!=p)findans(i.f,cur);
}
int32_t main(){
	fastio
    int q,m;cin>>n>>q>>m;
    for(int i=1;i<=n-1;i++){
        int a,b;cin>>a>>b;
        e.pb({a,b});
        adj[a].pb({b,i});
        adj[b].pb({a,i});
    }
    dfs(1,-1);
    hld(1,-1,1);
    f.init();
    t.init();
    for(int i=1;i<=lg;i++)up[1][i]=1;
    for(int j=1;j<=lg;j++)for(int i=2;i<=n;i++)up[i][j]=up[up[i][j-1]][j-1];
    f.update(1,1);
    while(q--){
        int a;cin>>a;
        a--;
        if(h[e[a].f]<h[e[a].s])a=e[a].s;
        else a=e[a].f;
        if(on[a]){
            int node=up[findpa(a)][0];
            last[a]=f.qry(pos[a]);
            mx[node]=max(mx[node],f.qry(pos[node]));
            mx[a]=max(mx[a],mx[node]);
            t.update(pos[a],false);
        }
        else{
            t.update(pos[a],true);
            int node=up[findpa(a)][0];
            int tmp=f.qry(pos[a])-last[a];
            mx[node]=max(mx[node],f.qry(pos[node]));
            upd(up[a][0],node,tmp);
            mx[node]=max(mx[node],mx[node]+(tmp));
        }
        on[a]=!on[a];
    }
    for(int i=1;i<=n;i++)mx[i]=max(mx[i],f.qry(pos[i]));
    for(int i=1;i<=m;i++){
        int a;cin>>a;
        cout<<mx[find(a)]<<'\n';
    }
	return 0;
}
