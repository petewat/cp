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
const int mod=1e9+7,mxn=5e5+5,inf=1e18,minf=-1e18,lg=15,base=311;
//#undef int
int k,m,n,q,d;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
//https://www.codechef.com/viewsolution/1138493356
//original edge
vector<int>adj[mxn+10],radj[mxn+10];
//dom tree edge
vector<int>tree[mxn+10];
int ans=0;
struct domtree{
    int dom[mxn+10],sdom[mxn+10],tin[mxn+10],T=0;
    int pa[mxn+10],mn[mxn+10],up[mxn+10];
    vector<int>have[mxn+10];
    //the list of node that have sdom = x
    int find(int u,int x=0){
		//mn[u] node u where sdom(u) is the min "between" root and v
		//if x=0 meaning we call find(u) then return u;
		//else return the node below beacuse we need node "between"
        if(u==pa[u])return x?-1:u;
        int v=find(pa[u],x+1);
        if(v<0)return u;
        if(tin[sdom[mn[pa[u]]]]<tin[sdom[mn[u]]])mn[u]=mn[pa[u]];
        pa[u]=v;
        return x?v:mn[u];
    }
    void merge(int u,int v){pa[v]=u;}
    vector<pii>ord;
    void gettin(int cur){
        tin[cur]=++T;
        ord.pb({tin[cur],cur});
        for(auto i:adj[cur])if(tin[i]==inf){
            up[i]=cur;
            gettin(i);
        }
    }
    void getdomtree(int S){
        T=0;
        for(int i=0;i<=n;i++)tin[i]=inf,pa[i]=sdom[i]=mn[i]=i;
        gettin(S);
        sort(rall(ord));
        for(auto i:ord){
            for(auto j:radj[i.s]){
				int x=find(j);
				if(tin[sdom[x]]<tin[sdom[i.s]])sdom[i.s]=sdom[x];
			}
            if(i.s!=S)have[sdom[i.s]].pb(i.s);
            for(auto j:have[i.s]){
                int v=find(j);
                if(sdom[v]==sdom[j])dom[j]=sdom[j];
                else dom[j]=v;
            }
            if(i.s!=S)merge(up[i.s],i.s);
        }
        sort(all(ord));
        for(auto i:ord){
            if(i.s==S)continue;
            if(dom[i.s]!=sdom[i.s])dom[i.s]=dom[dom[i.s]];
            tree[i.s].pb(dom[i.s]);
            tree[dom[i.s]].pb(i.s);
        }
		/*
		idom(x) ={
		-sdom(x), if sdom(u)=sdom(w)
		-idom(u), otherwise
		}
		*/
    }
    void re(){
        for(int i=1;i<=n;i++)have[i].clear();
        T=0;
    }
}t;
int sz[mxn+10];
void dfs(int cur,int p){
	sz[cur]=1;
	for(auto i:tree[cur])if(i!=p){
		dfs(i,cur);
		if(cur==1)ans-=(sz[i]*(sz[i]-1))/2LL;
		sz[cur]+=sz[i];
	}
}
void solve(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;cin>>a>>b;
		adj[a].pb(b);
		radj[b].pb(a);
	}
	t.getdomtree(1);
	dfs(1,-1);
    ans+=(sz[1]*(sz[1]-1))/2;
	cout<<ans<<'\n';
}
int32_t main(){
	fastio
    solve();
}
/*

*/