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
const int mod=998244353,mxn=1e6+5,inf=1e9,minf=-1e9,lg=30;
//#undef int
int k,m,n,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
vector<int>comp;
int sz=0;
struct seg{
    int v[2*mxn+10];
    void init(){for(int i=0;i<=2*sz;i++)v[i]=0;}
    vector<pii>keep;
    void update(int pos,int val){
        pos+=sz;
        v[pos]+=val;
        keep.pb({pos,val});
        for(int i=pos;i>0;i>>=1)v[i>>1]=v[i]+v[i^1];
    }
    int qry(int l,int r){
        int ans=0;
        for(l+=sz,r+=sz;l<=r;l>>=1,r>>=1){
            if(l&1)ans+=(v[l++]);
            if((!(r&1)))ans+=(v[r--]);
        }
        return ans;
    }
    void re(){
        for(auto i:keep){
            v[i.f]-=i.s;
            for(int j=i.f;j>0;j>>=1)v[j>>1]=v[j]+v[j^1];
        }
        keep.clear();
    }
}t;
int ans[mxn+10];
pair<pii,pii>val[mxn+10];
bool cmp(pair<pii,pii>a,pair<pii,pii>b){
    return a.s.f>b.s.f;
}
void cdq(int l,int r){
    if(l==r)return;
    int mid=l+(r-l)/2;
    cdq(l,mid);
    cdq(mid+1,r);
    vector<pair<pii,pii>>have;
    for(int i=l;i<=mid;i++)have.pb(val[i]);
    sort(all(have),cmp);
    int cur=r;
    for(auto i:have){
        while(cur>mid&&(comp[val[cur].f.s]-comp[val[cur].f.f])>=i.s.f){
            //update on R
            t.update(val[cur].f.s,1);
            cur--;
        }
        ans[i.s.s]+=t.qry(i.f.f,i.f.s-1);
    }
    t.re();
    //sort by size
    vector<pair<pii,pii>>ord;
    int c1=l,c2=mid+1;
    while(c1<=mid&&c2<=r){
        if((comp[val[c1].f.s]-comp[val[c1].f.f])<(comp[val[c2].f.s]-comp[val[c2].f.f]))ord.pb(val[c1++]);
        else ord.pb(val[c2++]);
    }
    while(c1<=mid)ord.pb(val[c1++]);
    while(c2<=r)ord.pb(val[c2++]);
    for(int i=0;i<ord.size();i++)val[i+l]=ord[i];
}
vector<pair<int,pii>>L[mxn+10],R[mxn+10];
int32_t main(){
	fastio
	int n;cin>>n;
    vector<pair<pii,pii>>v;
    vector<pair<pii,pii>>q;
    for(int i=1;i<=n;i++){
        int a,b,c;cin>>a>>b>>c;
        comp.pb(a);
        comp.pb(b);
        v.pb({{a,b},{c,i}});
        q.pb({{a,b},{c,i}});
    }
    sort(all(comp));
    comp.erase(unique(all(comp)),comp.end());
    sz=comp.size();
    for(auto &i:v){
        i.f.f=lb(all(comp),i.f.f)-comp.begin();
        i.f.s=lb(all(comp),i.f.s)-comp.begin();
        L[i.f.f].pb({i.f.s,i.s});
        R[i.f.s].pb({i.f.f,i.s});
    }
    for(int i=0;i<comp.size();i++){
        if(L[i].empty())continue;
        for(auto j:L[i]){
            t.update(j.f,1);
        }
        for(auto j:L[i]){
            ans[j.s.s]+=t.qry(lb(all(comp),comp[i]+j.s.f)-comp.begin(),comp.size()-1);
            ans[j.s.s]-=t.qry(j.f,comp.size()-1);
        }
    }
    t.re();
    for(int i=comp.size()-1;i>=0;i--){
        if(R[i].empty())continue;
        for(auto j:R[i])t.update(j.f,1);
        for(auto j:R[i]){
            ans[j.s.s]+=t.qry(0,ub(all(comp),comp[i]-j.s.f)-comp.begin()-1);
        }
    }
    t.re();
    sort(all(v));
    for(int i=0;i<n;i++)val[i]=v[i];
    cdq(0,n-1);
    for(int i=1;i<=n;i++)cout<<ans[i]-1<<'\n';
}
/*
*/