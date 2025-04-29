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
const int mod=1e9+7,mxn=3e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
int vis[mxn+10];
struct flow{
    //ford fulkerson
    struct edge{int cap,flow,v;};
    vector<edge>E;
    vector<int>adj[mxn+10];
    void add(int u,int v,int cap){
        adj[u].pb(E.size()),E.pb((edge){cap,0,v});
        adj[v].pb(E.size()),E.pb((edge){0,0,u});
    }
    int dfs(int cur,int T,int F){
        if(cur==T)return F;
        if(vis[cur])return 0;
        vis[cur]=1;
        for(auto i:adj[cur]){
            edge &e=E[i];
            if(e.flow==e.cap)continue;
            int df=dfs(e.v,T,min(F,e.cap-e.flow));
            if(df){
                e.flow+=df;
                E[i^1].flow-=df;
                return df;
            }
        }
        return 0;
    }
    int maxflow(int S,int T){
        int ans=0;
        while(int df=dfs(S,T,inf)){
            for(int i=1;i<=n;i++)vis[i]=0;
            ans+=df;
        }
        return ans;
    }
    vector<int>path;
    void getans(int cur,int T){
        if(cur==T){
            cout<<path.size()+2<<'\n';
            cout<<1<<" ";
            for(auto i:path)cout<<i<<" ";
            cout<<T<<'\n';
            return;
        }
        path.pb(cur);
        for(auto i:adj[cur]){
            edge &x=E[i];
            if(x.flow<=0)continue;
            x.flow=0;
            getans(x.v,T);
            return;
        }
    }
    void solve(){
        for(auto i:adj[1]){
            edge &x=E[i];
            if(x.flow<=0)continue;
            x.flow=0;
            getans(x.v,n);
            path.clear();
        }
    }

}t;
int32_t main(){
	fastio
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        t.add(a,b,1);
    }
    cout<<t.maxflow(1,n)<<'\n';
    t.solve();
}