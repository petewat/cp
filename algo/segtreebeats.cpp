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
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
//https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
int v[mxn+10];
struct seg{
    int sum[4*mxn+10],lazy[4*mxn+10];
    int mx1[4*mxn+10],mx2[4*mxn+10],mxc[4*mxn+10],mn1[4*mxn+10],mn2[4*mxn+10],mnc[4*mxn+10];
    //min,max,add
    //chmin
    void apply1(int pos, int x,int l,int r){
        if(mx1[pos]<=x)return;
        //mx2[pos] <= x < mx1[pos] ->update only mx1[pos]
        sum[pos]-=mx1[pos]*mxc[pos];
        mx1[pos]=x;
        sum[pos]+=mx1[pos]*mxc[pos];
        if(l==r)mn1[pos]=x;
        else{
            //case mx1 intersects mn1,mn2
            if(x<=mn1[pos])mn1[pos]=x;
            else if(x<mn2[pos])mn2[pos]=x;
        }
    }
    void apply2(int pos, int x,int l,int r){
        if(mn1[pos]>=x)return;
        //mn1[pos] <= x < mn2[pos]
        sum[pos]-=mn1[pos]*mnc[pos];
        mn1[pos]=x;
        sum[pos]+=mn1[pos]*mnc[pos];
        if(l==r)mx1[pos]=x;
        else{
            if(x>=mx1[pos])mx1[pos]=x;
            else if(x>mx2[pos])mx2[pos]=x;
        }
    }
    void apply3(int pos,int x,int l,int r){
        sum[pos]+=(r-l+1)*x;
        mx1[pos]+=x;
        if(mx2[pos]!=minf)mx2[pos]+=x;
        mn1[pos]+=x;
        if(mn2[pos]!=inf)mn2[pos]+=x;
        lazy[pos]+=x;
    }
    void push(int pos,int l,int r){
        if(l!=r){
            int mid=l+(r-l)/2;
            apply3(pos<<1,lazy[pos],l,mid);
            apply3(pos<<1|1,lazy[pos],mid+1,r);

            apply1(pos<<1,mx1[pos],l,mid);
            apply1(pos<<1|1,mx1[pos],mid+1,r);
            
            apply2(pos<<1,mn1[pos],l,mid);
            apply2(pos<<1|1,mn1[pos],mid+1,r);
        }
        lazy[pos]=0;
    }
    void pull(int pos,int l,int r){
        sum[pos]=sum[pos<<1]+sum[pos<<1|1];

        if(mx1[pos<<1]==mx1[pos<<1|1]){
            mx1[pos]=mx1[pos<<1];
            mx2[pos]=max(mx2[pos<<1],mx2[pos<<1|1]);
            mxc[pos]=mxc[pos<<1]+mxc[pos<<1|1];
        }
        else{
            if(mx1[pos<<1]>mx1[pos<<1|1]){
                mx1[pos]=mx1[pos<<1];
                mx2[pos]=max(mx1[pos<<1|1],mx2[pos<<1]);
                mxc[pos]=mxc[pos<<1];
            }
            else{
                mx1[pos]=mx1[pos<<1|1];
                mx2[pos]=max(mx1[pos<<1],mx2[pos<<1|1]);
                mxc[pos]=mxc[pos<<1|1];
            }
        }

        if(mn1[pos<<1]==mn1[pos<<1|1]){
            mn1[pos]=mn1[pos<<1];
            mn2[pos]=min(mn2[pos<<1],mn2[pos<<1|1]);
            mnc[pos]=mnc[pos<<1]+mnc[pos<<1|1];
        }
        else{
            if(mn1[pos<<1]<mn1[pos<<1|1]){
                mn1[pos]=mn1[pos<<1];
                mn2[pos]=min(mn1[pos<<1|1],mn2[pos<<1]);
                mnc[pos]=mnc[pos<<1];
            }
            else{
                mn1[pos]=mn1[pos<<1|1];
                mn2[pos]=min(mn1[pos<<1],mn2[pos<<1|1]);
                mnc[pos]=mnc[pos<<1|1];
            }
        }
    }
    void build(int pos=1,int l=0,int r=n-1){
        if(l==r){
            lazy[pos]=0;
            sum[pos]=mx1[pos]=mn1[pos]=v[l];
            mx2[pos]=minf;
            mn2[pos]=inf;
            mnc[pos]=mxc[pos]=1;
            return;
        }
        int mid=l+(r-l)/2;
        build(pos<<1,l,mid);
        build(pos<<1|1,mid+1,r);
        pull(pos,l,r);
    }
    //chmin
    void update1(int ql,int qr,int x,int pos=1,int l=0,int r=n-1){
        if(l>qr||r<ql||mx1[pos]<=x)return;
        if(ql<=l&&r<=qr&&mx2[pos]<x)return void(apply1(pos,x,l,r));
        int mid=l+(r-l)/2;
        push(pos,l,r);
        update1(ql,qr,x,pos<<1,l,mid);
        update1(ql,qr,x,pos<<1|1,mid+1,r);
        pull(pos,l,r);
    }
    void update2(int ql,int qr,int x,int pos=1,int l=0,int r=n-1){
        if(l>qr||r<ql||mn1[pos]>=x)return;
        if(ql<=l&&r<=qr&&mn2[pos]>x)return void(apply2(pos,x,l,r));
        int mid=l+(r-l)/2;
        push(pos,l,r);
        update2(ql,qr,x,pos<<1,l,mid);
        update2(ql,qr,x,pos<<1|1,mid+1,r);
        pull(pos,l,r);
    }
    void update3(int ql,int qr,int x,int pos=1,int l=0,int r=n-1){
        if(l>qr||r<ql)return;
        if(ql<=l&&r<=qr)return void(apply3(pos,x,l,r));
        int mid=l+(r-l)/2;
        push(pos,l,r);
        update3(ql,qr,x,pos<<1,l,mid);
        update3(ql,qr,x,pos<<1|1,mid+1,r);
        pull(pos,l,r);
    }
    int qry(int ql,int qr,int pos=1,int l=0,int r=n-1){
        if(l>qr||r<ql)return 0;
        if(ql<=l&&r<=qr)return sum[pos];
        int mid=l+(r-l)/2;
        push(pos,l,r);
        return qry(ql,qr,pos<<1,l,mid)+qry(ql,qr,pos<<1|1,mid+1,r);
    }
}t;
int32_t main(){
    fastio
    cin>>n>>q;
    for(int i=0;i<n;i++)cin>>v[i];
    t.build();
    while(q--){
        int ty;cin>>ty;
        int l,r;cin>>l>>r;
        r--;
        if(ty==0){   
            int x;cin>>x;
            t.update1(l,r,x);
        }
        else if(ty==1){
            int x;cin>>x;
            t.update2(l,r,x);
        }
        else if(ty==2){
            int x;cin>>x;
            t.update3(l,r,x);
        }
        else cout<<t.qry(l,r)<<'\n';
    }
}
