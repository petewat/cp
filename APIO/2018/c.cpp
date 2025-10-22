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
#include <cstdlib> 
#include <cstdint>
using namespace std;
#define ll long long
#define f first
//#define endl "\n"
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
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define int long long
#define double long double
const int mxn=2e5,inf=1e18,minf=-1e18;
vector<int>adj[mxn+10],adj2[mxn+10];
int tin[mxn+10],low[mxn+10],T=0,on[mxn+10],cnt=0,id[mxn+10],sz[mxn+10];
stack<int>st;
int ans=0,n,m,par,forest[mxn+10],idcnt=0;
vector<int>comp[mxn+10];
void tarjan(int cur,int p){
    tin[cur]=low[cur]=++T;
    st.push(cur);
    for(auto i:adj[cur]){
        if(i==p)continue;
        if(tin[i])low[cur]=min(low[cur],tin[i]);
        else{
            tarjan(i,cur);
            low[cur]=min(low[cur],low[i]);
            if(low[i]>=tin[cur]){
                adj2[cur].pb(++idcnt);
                while(adj2[idcnt].empty()||adj2[idcnt].back()!=i)adj2[idcnt].pb(st.top()),st.pop();
            }
        }
    }
}
int subsz[mxn+10];
void dfs(int cur,int p){
    subsz[cur]=(cur<=n);
    forest[cur]=par;
    for(auto i:adj2[cur])if(i!=p){
        dfs(i,cur);
        subsz[cur]+=subsz[i];
    }
}
int32_t main(){
    fastio
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    idcnt=n;
    for(int i=1;i<=n;i++)if(!tin[i]){
        tarjan(i,0);
        par=i;
        dfs(i,0);
        ans+=(subsz[i])*(subsz[i]-1)*(subsz[i]-2);
    }
    int x;
    for(int i=n+1;i<=idcnt;i++){
        /*
        choose any 2 diff node in the subtree j
        because i is block (all adjacent node are cut node)
        so (a,node,b) is not possible 
        */
        for(auto j:adj2[i]){
            x=subsz[j];
            ans-=(x)*(x-1)*(adj2[i].size());
        }
        x=subsz[forest[i]]-subsz[i];
        ans-=(x)*(x-1)*(adj2[i].size());
    }
    cout<<ans;
	return 0;
}