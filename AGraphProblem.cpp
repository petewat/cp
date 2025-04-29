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
#define double long double
const int mod=1e9+7,mxn=6e5+5,lg=30,inf=1e18,minf=-1e18;
int n,m;
pii e[mxn+10];
int T,pa[mxn+10],sz[mxn+10],L[mxn+10],R[mxn+10];
int find(int u){return (pa[u]==u)?u:pa[u]=find(pa[u]);}
int root=0;
void merge(int a,int b){
    a=find(a),b=find(b);
    T++;
    if(a==b)return;
    root=T;
    L[T]=a;
    R[T]=b;
    pa[T]=T;
    pa[a]=pa[b]=T;
    sz[T]=sz[a]+sz[b];
}
void add(int &x,int a){x=(x+a+mod)%mod;}
void mul(int &x,int a){x=(x*a)%mod;}
struct seg{
    int v[4*mxn+10],lazy[4*mxn+10],lazy2[4*mxn+10];
    void build(int l,int r,int pos){
        lazy2[pos]=1;
        if(l==r)return;
        int mid=l+(r-l)/2;
        build(l,mid,pos*2);
        build(mid+1,r,pos*2+1);
    }
    void push(int l,int r,int pos){
        mul(v[pos],lazy2[pos]);
        add(v[pos],lazy[pos]);
        if(l!=r){
            mul(lazy[pos*2],lazy2[pos]);
            mul(lazy[pos*2+1],lazy2[pos]);
            add(lazy[pos*2],lazy[pos]);
            add(lazy[pos*2+1],lazy[pos]);
            mul(lazy2[pos*2],lazy2[pos]);
            mul(lazy2[pos*2+1],lazy2[pos]);
        }
        lazy[pos]=0;
        lazy2[pos]=1;
    }
    void update(int l,int r,int pos,int ql,int qr,int val){
        push(l,r,pos);
        if(l>qr||r<ql)return;
        if(ql<=l&&r<=qr){
            add(lazy[pos],val);
            push(l,r,pos);
            return;
        }
        int mid=l+(r-l)/2;
        update(l,mid,pos*2,ql,qr,val);
        update(mid+1,r,pos*2+1,ql,qr,val);
    }
    void update2(int l,int r,int pos,int ql,int qr,int val){
        push(l,r,pos);
        if(l>qr||r<ql)return;
        if(ql<=l&&r<=qr){
            mul(lazy2[pos],val);
            push(l,r,pos);
            return;
        }
        int mid=l+(r-l)/2;
        update2(l,mid,pos*2,ql,qr,val);
        update2(mid+1,r,pos*2+1,ql,qr,val);
    }
    int qry(int l,int r,int pos,int qpos){
        push(l,r,pos);
        if(l==r)return v[pos];
        int mid=l+(r-l)/2;
        if(qpos<=mid)return qry(l,mid,pos*2,qpos);
        else return qry(mid+1,r,pos*2+1,qpos);
    }
}t;
int C=0;
int tin[mxn+10],tout[mxn+10],id[mxn+10],P[mxn+10];
void dfs(int cur){
    tin[cur]=++C;
    if(L[cur])dfs(L[cur]);
    if(R[cur])dfs(R[cur]);
    tout[cur]=C;
}
void calans(int cur){
    if(cur<=n)return;
    if(L[cur])calans(L[cur]);
    if(R[cur])calans(R[cur]);
    int la=t.qry(1,n+m,1,tin[e[cur-n].f]),ra=t.qry(1,n+m,1,tin[e[cur-n].s]);
    t.update2(1,n+m,1,tin[R[cur]],tout[R[cur]],P[sz[L[cur]]]);
    int k=(cur-n);
    mul(k,P[sz[L[cur]]-1]);
    add(la,k);
    t.update(1,n+m,1,tin[R[cur]],tout[R[cur]],la);
    t.update2(1,n+m,1,tin[L[cur]],tout[L[cur]],P[sz[R[cur]]]);
    k=cur-n;
    mul(k,P[sz[R[cur]]-1]);
    add(ra,k);
    t.update(1,n+m,1,tin[L[cur]],tout[L[cur]],ra);
}
int32_t main(){
    fastio
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>e[i].f>>e[i].s;
    P[0]=1;
    for(int i=1;i<=n;i++)sz[i]=1,pa[i]=i,P[i]=(10*P[i-1])%mod;
    T=n;
    for(int i=1;i<=m;i++)merge(e[i].f,e[i].s);
    t.build(1,n+m,1);
    dfs(root);
    calans(root);
    for(int i=1;i<=n;i++)cout<<t.qry(1,n+m,1,tin[i])<<'\n';
}