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
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int val[mxn+10][2];
int pref[mxn+10],suf[mxn+10];
int sz=0;
struct seg{
    int v[4*mxn+10],cnt[4*mxn+10];
    int lazy[4*mxn+10],sum[4*mxn+10],add[4*mxn+10];
    bitset<4*mxn+10>re;
    //lazy -> add coeff
    //add -> add value
    void init(){for(int i=0;i<=4*sz;i++)v[i]=0;}
    void push(int l,int r,int pos){
        v[pos]=(v[pos]+(sum[pos]*lazy[pos])%mod)%mod;
        v[pos]=(v[pos]+(cnt[pos]*add[pos])%mod)%mod;
        if(re[pos]){
            v[pos]=0,sum[pos]=0,cnt[pos]=0;
            if(l!=r)re[pos*2]=1,re[pos*2+1]=1;
        }
        if(l!=r){
            add[pos*2]+=add[pos];
            add[pos*2+1]+=add[pos];
            lazy[pos*2]+=lazy[pos];
            lazy[pos*2+1]+=lazy[pos];
        }
        lazy[pos]=0;
        add[pos]=0;
        re[pos]=0;
    }
    void updaterange(int l,int r,int ql,int qr,int pos){
        push(l,r,pos);
        if(l>qr||r<ql)return;
        if(l>=ql&&r<=qr){
            re[pos]=1;
            push(l,r,pos);
            return;
        }
        int mid=l+(r-l)/2;
        updaterange(l,mid,ql,qr,pos*2);
        update(mid+1,r,ql,qr,pos*2+1);
        v[pos]=(v[pos*2]+v[pos*2+1])%mod;
        sum[pos]=(sum[pos*2]+sum[pos*2+1])%mod;
        cnt[pos]=(cnt[pos*2]+cnt[pos*2+1])%mod;
    }
    void updaterange2(int l,int r,int ql,int qr,int val,int pos){
        push(l,r,pos);
        if(l>qr||r<ql)return;
        if(l>=ql&&r<=qr){
            add[pos]+=val;
            push(l,r,pos);
            return;
        }
        int mid=l+(r-l)/2;
        updaterange(l,mid,ql,qr,pos*2);
        update(mid+1,r,ql,qr,pos*2+1);
        v[pos]=(v[pos*2]+v[pos*2+1])%mod;
        sum[pos]=(sum[pos*2]+sum[pos*2+1])%mod;
        cnt[pos]=(cnt[pos*2]+cnt[pos*2+1])%mod;
    }
    void update(int l,int r,int qpos,int val,int pos){
        push(l,r,pos);
        if(l==r){
            sum[pos]=val;
            v[pos]=0;
            cnt[pos]=1;
            return;
        }
        int mid=l+(r-l)/2;
        if(qpos<=mid)update(l,mid,qpos,val,pos*2);
        else update(mid+1,r,qpos,val,pos*2+1);
        v[pos]=(v[pos*2]+v[pos*2+1])%mod;
        sum[pos]=(sum[pos*2]+sum[pos*2+1])%mod;
        cnt[pos]=(cnt[pos*2]+cnt[pos*2+1])%mod;
    }
    pii qry()
    void updateset(int l,int r){updaterange(0,sz,l,r,1);}
    void updatepos(int pos,int x){update(0,sz,pos,x,1);}
}t;
int32_t main(){
    fastio
    int n;cin>>n;
    vector<int>comp;
    for(int i=0;i<n;i++)cin>>val[i][0],comp.pb(val[i][0]);
    for(int i=0;i<n;i++)cin>>val[i][1],comp.pb(val[i][1]);
    sort(all(comp));
    comp.erase(unique(all(comp)),comp.end());
    int sum=0;
    for(int i=0;i<n;i++)val[i][0]=lb(all(comp),val[i][0])-comp.begin();
    for(int i=0;i<n;i++)val[i][1]=lb(all(comp),val[i][1])-comp.begin();
    sz=comp.size();
    cout<<sum;
}
/*
4
1 1 1 1
2 2 2 2
10
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
*/