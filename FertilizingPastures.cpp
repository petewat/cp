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
const int mxn=2e5,inf=1e18+1,minf=-1e9,mod=1e9+7;
int n,t;
int cost[mxn+10],sum[mxn+10],T[mxn+10];
//cost of starting at time 0, sum of ai ,time to complete
int A[mxn+10];
vector<int>adj[mxn+10];
bool cmp(pii a,pii b){
    return (a.f*b.s)<(a.s*b.f);
}
bool cmp2(pair<pii,int> a,pair<pii,int> b){
    return (a.f.f*b.f.s)<(a.f.s*b.f.f);
}
void calDP(int cur){
    sum[cur]=A[cur];
    vector<pii>v;
    for(auto i:adj[cur]){
        calDP(i);
        T[cur]+=T[i]+2;
        sum[cur]+=sum[i];
        cost[cur]+=cost[i];
        v.pb({T[i]+2,sum[i]});
    }
    sort(all(v),cmp);
    int ct=1;
    for(auto i:v){
        cost[cur]+=(ct*i.s);
        ct+=i.f;
    }
}
int hvy[mxn+10];
void calhvy(int cur){
    for(auto i:adj[cur]){
        calhvy(i);
        hvy[cur]=max(hvy[cur],hvy[i]+1);
    }
}
int ans=-1,ct=0;
void solve(int cur,int curans,int ct){
    vector<pair<pii,int>>v;
    vector<int>sufsum(adj[cur].size());
    curans+=(ct*A[cur]);
    if(adj[cur].empty()){
        if(ct!=(n-1)*2-hvy[1])assert(0);
        if(ans==-1||ans>curans)ans=curans;
    }
    int x=0;
    for(auto i:adj[cur])v.pb({{T[i]+2,sum[i]},i}),curans+=cost[i];
    sort(all(v),cmp2);
    for(int i=v.size()-1;i>=0;i--){
        sufsum[i]=v[i].f.s;
        if(i!=v.size()-1)sufsum[i]+=sufsum[i+1];
    }
    ct++;
    int ctt=ct;
    for(auto i:v){
        curans+=(ct*i.f.s);
        ct+=i.f.f;
    }
    int c=0;
    for(auto i:v){
        if(hvy[i.s]+1==hvy[cur]){
            int g=(ctt*i.f.s)+cost[i.s];
            if(c+1<v.size())g+=(sufsum[c+1]*i.f.f);
            curans-=g;
            solve(i.s,curans,ct-i.f.f);
            curans+=g;
        }
        ctt+=i.f.f;
        c++;
    }
    //solve(hvy[cur].s,curans,ct);
}
int32_t main(){
	fastio
    cin>>n>>t;
    for(int i=2;i<=n;i++){
        int p;cin>>p>>A[i];
        adj[p].pb(i);
    }
    calDP(1);
    if(t==0){
        cout<<(n-1)*2<<" "<<cost[1];
    }
    else{
        calhvy(1);
        solve(1,0,0);
        cout<<(n-1)*2-hvy[1]<<" "<<ans;
    }
}
/*

*/