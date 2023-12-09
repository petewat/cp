//fenwick bs, segtree finding number of over subtract (all pref sum cant be positive)
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
const int mod=1e9+7,mxn=3e5+5,lg=30,inf=1e18,minf=-1e18;
int n,m,q;
int a,b,c,d;
int findans[mxn+10],realans[mxn+10];
vector<pii>qry[mxn+10];
struct solve{
    int fwk[mxn+10];
    vector<pii>add[mxn+10],remove[mxn+10];
    void upd(int pos,int val){for(int i=pos;i<=q;i+=(i&-i))fwk[i]+=val;}
    int qry(int pos){
        int sum=0;
        for(int i=pos;i>0;i-=(i&-i))sum+=fwk[i];
        return sum;
    }

}f[2];
struct node{
    int sum,mxpref;
    node operator+(node a){
        node tmp;
        tmp.mxpref=max(mxpref,sum+a.mxpref);
        tmp.sum=sum+a.sum;
        return tmp;
    }
};
struct seg{
    node v[4*mxn+10];
    void update(int l,int r,int node,int pos,int val){
        if(l==r){
            v[node].mxpref=v[node].sum=val;
            return;
        }
        int mid=l+(r-l)/2;
        if(pos<=mid)update(l,mid,node<<1,pos,val);
        else update(mid+1,r,(node<<1)^1,pos,val);
        v[node]=v[node<<1]+v[(node<<1)^1];
    }
    node qry(int l,int r,int ql,int qr,int node){
        if(ql<=l&&r<=qr)return v[node];
        int mid=l+(r-l)/2;
        if(qr<=mid)return qry(l,mid,ql,qr,node<<1);
        if(ql>mid)return qry(mid+1,r,ql,qr,(node<<1)^1);
        return qry(l,mid,ql,qr,(node<<1))+qry(mid+1,r,ql,qr,(node<<1)^1);
    }
}t;
void update(int x){
    for(auto i:f[0].add[x])f[0].upd(i.f,i.s),t.update(1,q,1,i.f,-i.s);
    for(auto i:f[0].remove[x])f[0].upd(i.f,-i.s),t.update(1,q,1,i.f,0);
    for(auto i:f[1].add[x])f[1].upd(i.f,i.s),t.update(1,q,1,i.f,i.s);;
    for(auto i:f[1].remove[x])f[1].upd(i.f,-i.s),t.update(1,q,1,i.f,0);
}
int32_t main(){
	fastio
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++){
        int ty;cin>>ty;
        if(ty==1){
            cin>>a>>b>>c>>d;
            findans[i]=c;
            f[0].add[a].pb({i,d});
            f[0].remove[b+1].pb({i,d});
        }
        else if(ty==2){
            cin>>a>>b>>c;
            f[1].add[a].pb({i,c});
            f[1].remove[b+1].pb({i,c});
        }
        else{
            cin>>a>>b;
            qry[a].pb({i,b});
        }
    }
    int pos,sum;
    for(int i=1;i<=n;i++){
        update(i);
        for(auto j:qry[i]){
            int g=f[1].qry(j.f),k=t.qry(1,q,1,j.f,1).mxpref;
            k=max(k,0ll);
            pos=0;
            sum=0;
            for(int i=lg;i>=0;i--){
                if(pos+(1ll<<i)<=j.f&&sum+f[0].fwk[pos+(1ll<<i)]<g+j.s-k){
                    sum+=f[0].fwk[pos+(1<<i)];
                    pos+=(1<<i);
                }
            }
            pos++;
            realans[j.f]=(pos>j.f)?-1:findans[pos];
        }
    }
    for(int i=1;i<=q;i++)if(realans[i]!=0)cout<<((realans[i]==-1)?0:realans[i])<<'\n';
}
