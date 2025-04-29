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
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,base=109;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);	
}
vector<int>ord;
vector<pii>adj[mxn+10];
int vis[mxn+10];
void ts(int cur){
    if(vis[cur])return;
    vis[cur]=1;
    for(auto i:adj[cur])if(!vis[i.f]){
        ts(i.f);
    }
    ord.pb(cur);
}
int go[mxn+10][lg+5],L[mxn+10],pref[mxn+10],P[mxn+10];
pii ans[mxn+10];
int32_t main(){
    fastio
    cin>>n>>m;
    P[0]=1;
    for(int i=1;i<=n;i++)P[i]=(P[i-1]*base)%mod;
    for(int i=0;i<m;i++){
        int a,b,c;cin>>a>>b>>c;
        adj[a].pb({b,c});
    }
    for(int i=1;i<=n;i++)if(!vis[i])ts(i);
    auto get=[&](int x,int y){return (pref[x]-pref[y]+mod)%mod;};
    for(auto cur:ord){
        ans[cur]={0,0};
        for(auto j:adj[cur]){
            if(ans[j.f].f+1>ans[cur].f)ans[cur]={ans[j.f].f+1,ans[j.f].s+j.s},go[cur][0]=j.f,L[cur]=j.s;
            else if(ans[j.f].f+1==ans[cur].f){
                if(L[cur]>j.s)ans[cur]={ans[j.f].f+1,ans[j.f].s+j.s},go[cur][0]=j.f,L[cur]=j.s;
                else if(L[cur]==j.s){
                    int c1=go[cur][0],c2=j.f,a=c1,b=c2;
                    for(int k=lg;k>=0;k--)if(get(a,go[c1][k])==get(b,go[c2][k])){
                        c1=go[c1][k],c2=go[c2][k];
                    }
                    if(L[c2]<L[c1])ans[cur]={ans[j.f].f+1,ans[j.f].s+j.s},go[cur][0]=j.f,L[cur]=j.s;
                }
            }
        }
        pref[cur]=(pref[go[cur][0]]+(P[ans[cur].f]*L[cur])%mod)%mod;
        if(ans[cur].f==0)for(int i=0;i<=lg;i++)go[cur][i]=i;
        else for(int i=1;i<=lg;i++)go[cur][i]=go[go[cur][i-1]][i-1];
    }
    for(int i=1;i<=n;i++)cout<<ans[i].f<<" "<<ans[i].s<<'\n';
}
/*
top sort
starting from leaves
keep go[i][lg] to bin jump and pref[i]=pref hash value of L
when comparing 2 path we can bin jump and find the first road that differ and see which is better
*/