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
//#define ll long long
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
const int mod=998244353,mxn=3e5+5,inf=1e18,minf=-1e18,lg=62;
int p[mxn+10],val[mxn+10];
vector<int>adj[mxn+10];
int ans=0,0,n,k;
int pa[mxn+10];
vector<int>have;
int hvy[mxn+10],hvyp[mxn+10],sz[mxn+10],tin[mxn+10],tout[mxn+10],T=0,id[mxn+10];
void getsz(int cur){sz[cur]=1;for(auto i:adj[cur])getsz(i),sz[cur]+=sz[i];}
void gethvy(int cur,int hp){
    tin[cur]=++T;
    id[tin[cur]]=cur;
    for(auto i:adj[cur])if(sz[i]>sz[hvy[cur]])hvy[cur]=i;
    if(hvy[cur])gethvy(hvy[cur],hp);
    for(auto i:adj[cur])if(i!=hvy[cur])gethvy(i,cur);
    tout[cur]=T;
}
struct seg{
    pii v[4*mxn+10],lazy[4*mxn+10];
    void init(int l=1,int r=n,int pos=1){
        v[pos].f=inf;
        if(l==r)return void(v[pos].s=id[l]);
        int mid=l+(r-l)/2;
        init(l,mid,pos*2);
        init(mid+1,r,pos*2+1);
    }
    void push(int l,int r,int pos){
        if(v[pos].f!=inf)v[pos].f+=lazy[pos];
        if(l!=r){
            lazy[pos*2]+=lazy[pos];
            lazy[pos*2+1]+=lazy[pos];
        }
        lazy[pos]=0;
    }
    void updateadd(int l,int r,int ql,int qr,int pos,int val){
        push(l,r,pos);
        if(l>qr||r<ql)return;
        if(l>=ql&&r<=qr){
            lazy[pos]+=val;
            push(l,r,pos);
            return;
        }
        int mid=l+(r-l)/2;
        updateadd(l,mid,ql,qr,pos*2,val);
        updateadd(mid+1,r,ql,qr,pos*2+1,val);
        v[pos]=min(v[pos*2],v[pos*2+1]);
    }
    void update(int l,int r,int qpos,int pos,int val){
        push(l,r,pos);
        if(l==r)return void(v[pos].f=val);
        int mid=l+(r-l)/2;
        if(qpos>mid)update(mid+1,r,qpos,pos*2+1,val);
        else update(l,mid,qpos,pos*2,val);
        v[pos]=min(v[pos*2],v[pos*2+1]);
    }
    pii q(int l,int r,int ql,int qr,int pos){
        if(l>qr||r<ql)return {inf,0};
        if(l>=ql&&r<=qr)return v[pos];
        int mid=l+(r-l)/2;
        return min(q(l,mid,ql,qr,pos*2),q(mid+1,r,ql,qr,pos*2+1));
    }
    void updaterange(int l,int r,int val){updateadd(1,n,l,r,1,val);}
    void updatepos(int x,int val){update(1,n,x,1,val);}
    pii qry(int l,int r){return q(1,n,l,r,1);}
}prof,dp;
struct seg2{
    pii v[2*mxn+10];
    void init(){for(int i=0;i<=2*n;i++)v[i]={minf,i-n};}
    void update(int pos,int val){
        pos+=n;
        v[pos].f=val;
        for(int i=pos;i>0;i>>=1)v[i>>1]=max(v[i],v[i^1]);
    }
    pii qry(){
        return ans[1];
    }
}t;
void getprof(int cur){
    profit[cur]+=val[cur];
    prof.updatepos(tin[cur],profit[cur]);
    if(-profit[cur]>ans+k)return;
    for(auto i:adj[cur]){
        profit[i]=profit[cur];
        getprof(i);
        if(dp[i]>0)dp[cur]+=dp[i];
    }
    dp[cur]+=val[cur];
    dp.updatepos(tin[cur],dp[cur]);
}
void updatedp(int x){
    int cur=x;
    while(hvyp[cur]){
        if(dp.qry(tin[hvyp[cur]],tin[cur])>=0){
            dp.updaterange(tin[hvyp[cur]],tin[cur],dp[x]);
            cur=p[hvyp[cur]];
        }
        else{
            int l=tin[hvyp[cur]],r=tin[cur],pos=-1;
            while(l<=r){
                int mid=l+(r-l)/2;
                if(dp.qry(mid,tin[cur])<0)l=mid+1,pos=max(pos,mid);
                else r=mid-1;
            }
            dp.updaterange(pos,tin[cur],dp[x]);
            dp[pos]=dp.qry(pos,pos).f;
            if(dp[pos])x=id[pos],cur=id[pos];
        }
    }
}
void alive(int x){
    profit[x]=prof.qry(1,n).f-val[x];
    getprof(x);
    updatedp(x);
}
void updateblocknode(){
    while(1){
        pii a=prof.qry(1,n);
        if(ans+k>-a.f)alive(a.s);
        else break;
        prof.updatepos(tin[a.s],inf);
    }
}
void kill(int cur){
    prof.updaterange(tin[cur],tout[cur],-val[cur]);
    for(auto i:adj[cur]){
        int g=dp.qry(tin[i],tin[i]).f;
        if(g>0)kill(i);
        else t.update(i,g);
    }
}
int getans(){
    pii x=t.qry();
    kill(x.s);
    t.update(x.s,minf);
    return x.f;
}
int32_t main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>val[i]>>p[i];
        adj[p[i]].pb(i);
    }
    prof.init(),dp.init();
    cout<<ans<<"\n";
}
/*
keep block node in segtree of profit
update profit of those block node
when the -profit<ans+k
then we can unblock the node and continue dfsing from that node
updating dp :
let the block node =x;
dfs calculate dp[i] in the subtree of x
for dp above we can see that dp[x] will only add to the dp[par] until the first par that dp[par]<0
we can then check if the dp[par]+dp[x]>0 if it does then we can continue update par of par the same way
we can see that dp[par] turning positive can only happen once

segtree need to be able to
add in range
set in pos
get min
*/