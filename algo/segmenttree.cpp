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
#include<complex>
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
using cd = complex<double>;
double const PI=acos(-1);
const int mod=1e9+7,mxn=3e5+5,inf=1e18,minf=-1e18,lg=27,Mxn=lg*mxn;
//#undef int
int k,m,n,q,d;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);	
	freopen((name+".out").c_str(),"w",stdout);	
}
//problem - https://oj.uz/problem/view/NOI20_progression
//keep segment tree for v[i]-v[i-1]
//update 2 type->(S,C,L,R) add/set S+(i-L)*C in range [L,R]
//qry find longest segment within [L,R] where v[i]-v[i-1]=k for any k
struct node{
    int Lval,Rval,ans,Lf,Rf,sz;
    node(int a=inf,int b=1):Lval(a),Rval(a),ans(b),Lf(b),Rf(b),sz(b){};
};
node operator+(node a,node b){
    node x;
    if(a.Rval==inf)return b;
    if(b.Rval==inf)return a;
    x.sz=a.sz+b.sz;
    x.ans=max(a.ans,b.ans);
    if(a.Rval==b.Lval)x.ans=max(x.ans,a.Rf+b.Lf);
    x.Lval=a.Lval;
    x.Rval=b.Rval;
    if(a.ans==a.sz&&a.Lval==b.Lval)x.Lf=a.ans+b.Lf;
    else x.Lf=a.Lf;
    if(b.ans==b.sz&&b.Rval==a.Rval)x.Rf=b.ans+a.Rf;
    else x.Rf=b.Rf;
    return x;
}
node dummy(inf,0);
struct seg{
    //keep v[i]-v[i-1]
    //support add/set in range
    int v[4*mxn+10],lazy[4*mxn+10],lazy2[4*mxn+10];
    node val[4*mxn+10];
    //the comb function has to be associative (a+b)+c=a+(b+c)
    int comb(int a,int b){return a+b;}
    void apply(int pos,int l,int r,int x){
        //put tag and apply to value
        lazy[pos]+=x;
        v[pos]+=(x*(r-l+1));
        val[pos].Lval+=x;
        val[pos].Rval+=x;
    }
    void apply2(int pos,int l,int r,int x){
        if(x==inf)return;
        lazy2[pos]=x;
        lazy[pos]=0;
        v[pos]=(x*(r-l+1));
        val[pos]=node(x,r-l+1);
    }
    void push(int pos,int l,int r){
        //push the current lazy tag down
        if(l!=r){
            int mid=l+(r-l)/2;
            //we assume the tag are in chronological order(the lower the older)
            apply2(pos*2,l,mid,lazy2[pos]);
            apply2(pos*2+1,mid+1,r,lazy2[pos]);
            apply(pos*2,l,mid,lazy[pos]);
            apply(pos*2+1,mid+1,r,lazy[pos]);

        }
        //reset
        lazy[pos]=0;
        lazy2[pos]=inf;
    }
    void pull(int pos,int l,int r){
        int mid=l+(r-l)/2;
        v[pos]=v[pos*2]+v[pos*2+1];
        val[pos]=val[pos*2]+val[pos*2+1];
    }
    void updateadd(int ql,int qr,int x,int pos=1,int l=1,int r=n){
        if(l>qr||r<ql||r<l)return;
        if(ql<=l&&r<=qr)return void(apply(pos,l,r,x));
        int mid=l+(r-l)/2;
        push(pos,l,r);
        updateadd(ql,qr,x,pos*2,l,mid);
        updateadd(ql,qr,x,pos*2+1,mid+1,r);
        pull(pos,l,r);
    }
    void updateset(int ql,int qr,int x,int pos=1,int l=1,int r=n){
        if(l>qr||r<ql||r<l)return;
        if(ql<=l&&r<=qr)return void(apply2(pos,l,r,x));
        int mid=l+(r-l)/2;
        push(pos,l,r);
        updateset(ql,qr,x,pos*2,l,mid);
        updateset(ql,qr,x,pos*2+1,mid+1,r);
        pull(pos,l,r);
    }
    int qrysum(int ql,int qr,int pos=1,int l=1,int r=n){
        if(l>qr||r<ql||r<l)return 0;
        if(ql<=l&&r<=qr)return v[pos];
        int mid=l+(r-l)/2;
        push(pos,l,r);
        pull(pos,l,r);
        return qrysum(ql,qr,pos*2,l,mid)+qrysum(ql,qr,pos*2+1,mid+1,r);
    }
    node qryans(int ql,int qr,int pos=1,int l=1,int r=n){
        if(l>qr||r<ql||r<l)return dummy;
        if(ql<=l&&r<=qr)return val[pos];
        int mid=l+(r-l)/2;
        push(pos,l,r);
        pull(pos,l,r);
        return qryans(ql,qr,pos*2,l,mid)+qryans(ql,qr,pos*2+1,mid+1,r);
    }
}t;
int v[mxn+10];
int32_t main(){
	fastio
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        t.updateset(i,i,v[i]-v[i-1]);
    }
    //13
    for(int i=0;i<m;i++){
        int T;cin>>T;
        if(T==1){
            int L,R,S,C;cin>>L>>R>>S>>C;
            t.updateadd(L+1,R,C);
            t.updateadd(L,L,S);
            t.updateadd(R+1,R+1,-(S+(R-L)*C));
        }
        else if(T==2){
            int L,R,S,C;cin>>L>>R>>S>>C;
            int x=t.qrysum(1,L-1),y=t.qrysum(1,R+1);
            t.updateset(L+1,R,C);
            t.updateset(L,L,S-x);
            t.updateset(R+1,R+1,y-(S+(R-L)*C));
        }
        else{
            int L,R;cin>>L>>R;
            cout<<t.qryans(L+1,R).ans+1<<'\n';
        }
    }
}
/*
1 847 851 -824104 -605011
2 632 830 958889 -100072
1 281 572 -706754 775961
2 996 1000 292058 561922
1 669 936 -882268 -272241
1 544 890 -178984 -763676
*/