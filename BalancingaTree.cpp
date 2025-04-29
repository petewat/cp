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
const int mod=1e9+7,mxn=2e5+5,inf=1e10,minf=-1e10,lg=30,base=191;
int n,B,mid;
vector<int>adj[mxn+10];
pii range[mxn+10],sub[mxn+01],rest[mxn+10];
int L[mxn+10],R[mxn+10];
pii comb(pii a,pii b){
    //get intersect
    if(a.s<b.f||b.s<a.f)return {-1,-1};
    if(a.s<0||b.s<0)return {-1,-1};
    return {max(a.f,b.f),min(a.s,b.s)};
}
void getsub(int cur){
    sub[cur]={L[cur]-mid,R[cur]+mid};
    for(auto i:adj[cur]){
        getsub(i);
        sub[cur]=comb(sub[cur],sub[i]);
    }
}
bool getrange(int cur){
    pii child={minf,inf};
    range[cur]={L[cur],R[cur]};
    for(auto i:adj[cur])child=comb(child,sub[i]);
    child=comb(range[cur],child);
    range[cur]=comb(child,rest[cur]);
    if(range[cur].s<0)return 0;
    for(auto i:adj[cur]){
        rest[i]=comb({range[cur].f-mid,range[cur].f+mid},rest[cur]);
        if(!getrange(i))return 0;
    }
    return 1;
}
bool check(){
    getsub(1);
    if(sub[1].s<0)return 0;
    rest[1]={minf,inf};
    if(!getrange(1))return 0;
    return 1;
}
int val[mxn+10];
void getans(int cur){
    pii child={minf,inf};
    for(auto i:adj[cur]){
        getans(i);
        child=comb(child,range[i]);
    }
    val[cur]=max(0LL,comb(range[cur],child).f);
    range[cur]=comb({val[cur]-mid,val[cur]+mid},child);
}
void solve(){
    cin>>n;
    for(int i=2;i<=n;i++){
        int x;cin>>x;
        adj[x].pb(i);
    }
    for(int i=1;i<=n;i++)cin>>L[i]>>R[i];
    int l=0,r=1e9,ans=inf;
    while(l<=r){
        mid=l+(r-l)/2;
        if(check())r=mid-1,ans=min(ans,mid);
        else l=mid+1;
    }
    cout<<ans<<'\n';
    if(B){
        mid=ans;
        check();
        getans(1);
        for(int i=1;i<=n;i++){
            cout<<val[i];
            if(i!=n)cout<<" ";
        }
        cout<<'\n';
    }
    for(int i=1;i<=n;i++)adj[i].clear();
}
int32_t main(){
    fastio
	int t;cin>>t>>B;
    while(t--)solve();
}
/*
*/