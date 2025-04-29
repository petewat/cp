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
const int mod=1e9+7,mxn=2e3+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int h[mxn+10];
int dead[mxn+10][mxn+10];
double slope(int a,int b,int ha,int hb){
    return (double)((ha-hb)*1.0/(a-b));
}
struct seg{
    pair<double,int> v[2*mxn+10];
    void init(){for(int i=0;i<=2*n;i++)v[i]={inf,-1};}
    void update(int pos,double val){
        v[pos+n]={val,pos};
        pos+=n;
        for(int i=pos;i>0;i>>=1)v[i>>1]=min(v[i],v[i^1]);
    }
    pair<double,int> qry(int l,int r){
        pair<double,int> ans={inf,-1};
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if(l&1)ans=min(ans,v[l++]);
            if(!(r&1))ans=min(ans,v[r--]);
        }
        return ans;
    }
}t[mxn+10];
struct seg2{
    pair<double,int> v[2*mxn+10];
    void init(){for(int i=0;i<=2*n;i++)v[i]={minf,-1};}
    void update(int pos,double val){
        v[pos+n]={val,pos};
        pos+=n;
        for(int i=pos;i>0;i>>=1)v[i>>1]=max(v[i],v[i^1]);
    }
    pair<double,int> qry(int l,int r){
        pair<double,int> ans={minf,-1};
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if(l&1)ans=max(ans,v[l++]);
            if(!(r&1))ans=max(ans,v[r--]);
        }
        return ans;
    }
}t2[mxn+10];
int add[mxn+10];
int ans=0;
void cal(int i){
    double mx=minf;
    for(int j=i+1;j<=n;j++){
        double a=slope(i,j,h[i],h[j]);
        if(a>=mx||a-mx>=0.0000001){
            ans++,mx=a;
            add[i]++;
            t[i].update(j,a);
            t2[i].update(j,a);
            dead[i][j]=0;
        }
        else {
            t[i].update(j,inf);
            t2[i].update(j,minf);
            dead[i][j]=1;
        }
    }
}
int32_t main(){
    fastio
    cin>>n;
    for(int i=1;i<=n;i++)cin>>h[i];
    int q;cin>>q;
    for(int i=1;i<=n;i++){
        t[i].init();
        t2[i].init();
        cal(i);
    }
    while(q--){
        int x,y;cin>>x>>y;
        h[x]+=y;
        for(int i=1;i<x;i++){
            double a=slope(i,x,h[i],h[x]);
            while(1){
                pair<double,int>b=t[i].qry(x+1,n);
                if(b.f>=a)break;
                dead[i][b.s]=1;
                t[i].update(b.s,inf);
                ans--;
                add[i]--;
            }
            if(!dead[i][x]){
                t[i].update(x,a);
                t2[i].update(x,a);
            }
            else if(x!=1){
                pair<double,int>b=t2[i].qry(1,x-1);
                if(b.f<=a){
                    add[i]++;
                    dead[i][x]=0;
                    t[i].update(x,a);
                    t2[i].update(x,a);
                    ans++;
                }
            }
        }
        ans-=add[x];
        add[x]=0;
        cal(x);
        cout<<ans<<'\n';
    }
}
/*
5 4 5

*/