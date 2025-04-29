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
const int mod=1e9+7,mxn=1e5+5,inf=1e18,minf=-1e18,lg=15,base=311;
//#undef int
int k,m,n,q,d;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
//https://cses.fi/problemset/result/12227728/
struct dinic{
    struct edge{int v,flow,cap;};
    int lvl[mxn+10],at[mxn+10];
    vector<edge>E;
    vector<int>adj[mxn+10];
    int scaling=0,lim;
    //with or without scaling?
    void add(int u,int v,int cap,int rcap=0){
        //add edge and the corresponding residual edge
        adj[u].pb(E.size()),E.pb({v,0,cap});
        adj[v].pb(E.size()),E.pb({u,0,rcap});
    }
    bool bfs(int S,int T){
        //get leveled graph
        for(int i=0;i<=n;i++)lvl[i]=-1,at[i]=0;
        lvl[S]=0;
        queue<int>q;
        q.push(S);
        while(!q.empty()){
            int cur=q.front();
            q.pop();
            for(auto i:adj[cur]){
                edge x=E[i];
                if(lvl[x.v]<0&&x.flow<x.cap&&(!scaling||x.cap-x.flow>=lim)){
                    lvl[x.v]=lvl[cur]+1;
                    q.push(x.v);  
                }
            }
        }
        return lvl[T]>=0;
    }
    int dfs(int cur,int T,int F){
        //push flow
        if(cur==T)return F;
        for(at[cur];at[cur]<adj[cur].size();at[cur]++){
            edge& x=E[adj[cur][at[cur]]];
            if(lvl[x.v]!=lvl[cur]+1||x.flow==x.cap)continue;
            int df=dfs(x.v,T,min(F,x.cap-x.flow));
            if(df){
                x.flow+=df;
                E[adj[cur][at[cur]]^1].flow-=df;
                return df;
            }
        }
        return 0;
    }
    int maxflow(int S,int T){
        int ans=0;
        for(lim=((scaling)?(1LL<<30):1);lim>0;lim>>=1){
            while(bfs(S,T)){
                while(int df=dfs(S,T,inf))ans+=df;
            }
        }
        return ans;
    }

    //below isnt part of the template
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
    t.scaling=1;
    cout<<t.maxflow(1,n)<<'\n';
    t.solve();
}
/*

*/