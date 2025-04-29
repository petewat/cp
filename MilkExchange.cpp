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
const int mod=1e9+7,mxn=1e6+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q;
void setIO(string name){	
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
int v[mxn+10],R[mxn+10],ans[mxn+10],Mn=inf,add[mxn+10];
pii range[mxn+10];
vector<int>adj[mxn+10];
int getD(int a,int b){return b-a;}
pii merge(pii a,pii b){
    if(a.f>b.s+1||b.f>a.s+1)assert(0);
    return {min(a.f,b.f),max(a.s,b.s)};
}
void update(int l,int r,int x){
    add[l]+=x;
    add[r+1]-=x;
    //for(int i=l;i<=n;i++)ans[i]+=min((i-l+1),(r-l+1))*x;
}
void solve(int cur){
    range[cur]={0,0};
    for(auto i:adj[cur]){
        solve(i);
        int diff=v[i]-v[cur],dist=getD(i,cur);
        if(diff<=0)assert(0);
        if(dist<0)assert(0);
        pii x={range[i].f+dist,range[i].s+dist};
        update(x.f,x.s,-diff);
        range[cur]=merge(range[cur],x);
    }
}
int32_t main(){
    fastio
    cin>>n;
    int sum=0;
    for(int i=1;i<=n;i++)cin>>v[i],sum+=v[i],Mn=min(Mn,v[i]);
    stack<int>st;
    for(int i=n+1;i<=2*n;i++)v[i]=v[i-n];
    vector<int>root;
    for(int i=2*n;i>=1;i--){
        while(!st.empty()&&v[st.top()]>=v[i])st.pop();
        if(!st.empty())R[i]=st.top(),adj[R[i]].pb(i);
        st.push(i);
    }
    for(int i=n+1;i<=2*n;i++)if(v[i]==Mn)solve(i);
    int ca=0,A=0;
    for(int i=1;i<=n;i++){
        ca+=add[i];
        A+=ca;
        cout<<sum+A<<'\n';
    }
}
/*
3 8 6 4 8 3 8 1 3 8 6 4 8 3 8 1

*/